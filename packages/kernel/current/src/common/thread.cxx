//==========================================================================
//
//      common/thread.cxx
//
//      Thread class implementations
//
//==========================================================================
//####COPYRIGHTBEGIN####
//
// -------------------------------------------
// The contents of this file are subject to the Cygnus eCos Public License
// Version 1.0 (the "License"); you may not use this file except in
// compliance with the License.  You may obtain a copy of the License at
// http://sourceware.cygnus.com/ecos
// 
// Software distributed under the License is distributed on an "AS IS"
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See the
// License for the specific language governing rights and limitations under
// the License.
// 
// The Original Code is eCos - Embedded Cygnus Operating System, released
// September 30, 1998.
// 
// The Initial Developer of the Original Code is Cygnus.  Portions created
// by Cygnus are Copyright (C) 1998,1999 Cygnus Solutions.  All Rights Reserved.
// -------------------------------------------
//
//####COPYRIGHTEND####
//==========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):   nickg
// Contributors:        nickg
// Date:        1997-09-15
// Purpose:     Thread class implementation
// Description: This file contains the definitions of the thread class
//              member functions that are common to all thread implementations.
//
//####DESCRIPTIONEND####
//
//==========================================================================

#include <pkgconf/kernel.h>             // kernel configuration file

#include <cyg/hal/hal_arch.h>           // HAL_REORDER_BARRIER &
                                        // CYGNUM_HAL_STACK_SIZE_TYPICAL

#include <cyg/kernel/ktypes.h>          // base kernel types
#include <cyg/infra/cyg_trac.h>         // tracing macros
#include <cyg/infra/cyg_ass.h>          // assertion macros
#include <cyg/kernel/instrmnt.h>        // instrumentation

#include <cyg/kernel/thread.hxx>        // our header

#include <cyg/kernel/intr.hxx>          // Interrupt support

#include <cyg/kernel/thread.inl>        // thread inlines
#include <cyg/kernel/sched.inl>         // scheduler inlines
#include <cyg/kernel/clock.inl>         // clock inlines

// =========================================================================
// Cyg_HardwareThread members

// -------------------------------------------------------------------------
// Thread entry point.
// This is inserted as the PC value in all initial thread contexts.
// It does some housekeeping and then calls the real entry point.

void
Cyg_HardwareThread::thread_entry( Cyg_Thread *thread )
{
    CYG_REPORT_FUNCTION();

    Cyg_Scheduler::scheduler.need_reschedule = false; // finished rescheduling
    Cyg_Scheduler::scheduler.current_thread = thread; // restore current thread pointer

    CYG_INSTRUMENT_THREAD(ENTER,thread,0);
    
#ifdef CYGSEM_KERNEL_SCHED_TIMESLICE
    // Reset the timeslice counter so that this thread gets a full
    // quantum. 
    Cyg_Scheduler::reset_timeslice_count();
#endif
    
    // Zero the lock
    HAL_REORDER_BARRIER ();            // Prevent the compiler from moving
    Cyg_Scheduler::sched_lock = 0;     // the assignment into the code above.
    HAL_REORDER_BARRIER();

    // Call entry point in a loop.
    
    for(;;)
    {
        thread->entry_point(thread->entry_data);
        thread->exit();
    }
}

// =========================================================================
// Cyg_Thread members

// -------------------------------------------------------------------------
// Statics and thread list functions

#ifdef CYGVAR_KERNEL_THREADS_LIST

// List of all extant threads
Cyg_Thread *Cyg_Thread::thread_list = 0;

inline void
Cyg_Thread::add_to_list( void )
{
    // Add thread to housekeeping list
    Cyg_Scheduler::lock();

    if( thread_list == 0 )
        list_next = this;
    else {
        Cyg_Thread *prev = thread_list;
        do {
            if ( this == prev )
                break; // found it already!
            prev = prev->list_next;
        } while ( prev != thread_list );
        if ( this != prev ) {
            // insert it in the list:
            list_next = thread_list->list_next;
            thread_list->list_next = this;
        }
    }
    thread_list = this;

    Cyg_Scheduler::unlock();
}

inline void
Cyg_Thread::remove_from_list( void )
{
    // remove thread from housekeeping list
    Cyg_Scheduler::lock();

    Cyg_Thread *prev = thread_list;

    do {
        if( prev->list_next == this ) {
            prev->list_next = list_next;
            if( thread_list == this )
                thread_list = list_next;
            break;
        }
        prev = prev->list_next;
    } while ( prev != thread_list );
    
    Cyg_Scheduler::unlock();
}

#endif

static cyg_uint16 next_unique_id = 1;

// -------------------------------------------------------------------------
// Magic new operator to allow the thread constructor to be
// recalled.

inline void *
operator new(size_t size, Cyg_Thread *ptr)
{ return (void *)ptr; };

// Constructor

Cyg_Thread::Cyg_Thread(
        CYG_ADDRWORD            sched_info,     // Scheduling parameter(s)
        cyg_thread_entry        *entry,         // entry point function
        CYG_ADDRWORD            entry_data,     // entry data
        char                    *name_arg,      // thread name cookie
        CYG_ADDRESS             stack_base,     // stack base, NULL = allocate
        cyg_ucount32            stack_size      // stack size, 0 = use default
        )
:   Cyg_HardwareThread(entry, entry_data, stack_size, stack_base),
    Cyg_SchedThread(this, sched_info)
#ifdef CYGFUN_KERNEL_THREADS_TIMER
    ,timer(this)
#endif
{
    CYG_REPORT_FUNCTION();

    // Start the thread in suspended state.
    state               = SUSPENDED;
    suspend_count       = 1;

    // Initialize sleep_reason which is used by kill, release
    sleep_reason        = NONE;
    wake_reason         = NONE;

    // Assign a 16 bit id to the thread.
    unique_id           = next_unique_id++;

#ifdef CYGVAR_KERNEL_THREADS_DATA
    // Zero all per-thread data entries.
    for( int i = 0; i < CYGNUM_KERNEL_THREADS_DATA_MAX; i++ )
        thread_data[i] = 0;
#endif
#ifdef CYGVAR_KERNEL_THREADS_NAME
    name = name_arg;
#endif
#ifdef CYGVAR_KERNEL_THREADS_LIST
    // Add thread to housekeeping list
    add_to_list();
#endif    
    
    Cyg_Scheduler::scheduler.register_thread(this);
    
    init_context(this);

    CYG_REPORT_RETURN();
}


// -------------------------------------------------------------------------
// Re-initialize this thread.
// We do this by re-invoking the constructor with the original
// arguments, which are still available in the object.

void
Cyg_Thread::reinitialize()
{
    CYG_REPORT_FUNCTION();

    CYG_ASSERTCLASS( this, "Bad thread");
    CYG_ASSERT( this != Cyg_Scheduler::get_current_thread(),
                "Attempt to reinitialize current thread");
    CYG_ASSERT( get_current_queue() == NULL , "Thread is still on a queue");

#ifdef CYGFUN_KERNEL_THREADS_TIMER
    // Clear the timeout. It is irrelevant whether there was
    // actually a timeout pending.
    timer.disable();
#endif

    // Ensure the scheduler has let go of us.
    Cyg_Scheduler::scheduler.deregister_thread(this);

    cyg_priority pri = get_priority();
#ifdef CYGVAR_KERNEL_THREADS_NAME
    char * name_arg = name;
#else
    char * name_arg = NULL;
#endif
    
    new(this) Cyg_Thread( pri,
                          entry_point, entry_data,
                          name_arg,
                          stack_base, stack_size );
    // the constructor re-registers the thread with the scheduler.

    CYG_ASSERTCLASS( this, "Thread corrupted by reinitialize");    

    CYG_REPORT_RETURN();
}

// -------------------------------------------------------------------------
// Destructor.

Cyg_Thread::~Cyg_Thread()
{
    CYG_REPORT_FUNCTION();

    Cyg_Scheduler::scheduler.deregister_thread(this);

#ifdef CYGVAR_KERNEL_THREADS_LIST
    // Remove thread from housekeeping list.
    remove_from_list();
#endif 
    
    CYG_REPORT_RETURN();
}

// -------------------------------------------------------------------------
// Thread consistency checker.

#ifdef CYGDBG_USE_ASSERTS

bool
Cyg_Thread::check_this( cyg_assert_class_zeal zeal) const
{
//    CYG_REPORT_FUNCTION();

    // check that we have a non-NULL pointer first
    if( this == NULL ) return false;
    
    switch( zeal )
    {
    case cyg_system_test:
    case cyg_extreme:
    case cyg_thorough:
        if( (state & SUSPENDED) && (suspend_count == 0) ) return false;
    case cyg_quick:
        // Check that the stackpointer is within its limits.
        // Note: This does not check the current stackpointer value
        // of the executing thread.
        if( (stack_ptr > (stack_base + stack_size)) ||
            (stack_ptr < stack_base) ) return false;
    case cyg_trivial:
    case cyg_none:
    default:
        break;
    };

    return true;
}

#endif

// -------------------------------------------------------------------------
// Put the thread to sleep.
// This can only be called by the current thread on itself, hence
// it is a static function.

void
Cyg_Thread::sleep()
{
    CYG_REPORT_FUNCTION();

    Cyg_Thread *current = Cyg_Scheduler::get_current_thread();

    CYG_ASSERTCLASS( current, "Bad current thread" );
    
    CYG_INSTRUMENT_THREAD(SLEEP,current,0);
    
    // Prevent preemption
    Cyg_Scheduler::lock();

    // If running, remove from run qs
    if ( current->state == RUNNING )
        Cyg_Scheduler::scheduler.rem_thread(current);

    // Set the state
    current->state |= SLEEPING;

    // Unlock the scheduler and switch threads
    Cyg_Scheduler::unlock();

    CYG_REPORT_RETURN();
}

// -------------------------------------------------------------------------
// Awaken the thread from sleep.

void
Cyg_Thread::wake()
{
    CYG_REPORT_FUNCTION();

    CYG_INSTRUMENT_THREAD(WAKE,this,Cyg_Scheduler::current_thread);
    
    // Prevent preemption
    Cyg_Scheduler::lock();

    if( 0 != (state & SLEEPSET) )
    {
        // Set the state
        state &= ~SLEEPSET;

        // remove from any queue we were on
        remove();

        // If the thread is now runnable, return it to run queue
        if( state == RUNNING )
            Cyg_Scheduler::scheduler.add_thread(this);

    }
    
    // Unlock the scheduler and maybe switch threads
    Cyg_Scheduler::unlock();

    CYG_REPORT_RETURN();
}

// -------------------------------------------------------------------------
// Put the thread to sleep, with wakeup count.
// This can only be called by the current thread on itself, hence
// it is a static function.

void
Cyg_Thread::counted_sleep()
{
    CYG_REPORT_FUNCTION();

    Cyg_Thread *current = Cyg_Scheduler::get_current_thread();

    CYG_ASSERTCLASS( current, "Bad current thread" );
    
    CYG_INSTRUMENT_THREAD(SLEEP,current,0);
    
    // Prevent preemption
    Cyg_Scheduler::lock();

    if ( 0 == current->wakeup_count ) {
        set_sleep_reason( Cyg_Thread::WAIT );
        current->sleep();               // prepare to sleep
        current->state |= COUNTSLEEP;   // Set the state
    }
    else
        // there is a queued wakeup, do not sleep
        current->wakeup_count--;

    // Unlock the scheduler and switch threads
    Cyg_Scheduler::unlock();

    // and deal with anything we must do when we return
    switch( current->wake_reason ) {
    case DESTRUCT:
    case EXIT:            
        current->exit();
        break;
        
    default:
        break;
    }

    CYG_REPORT_RETURN();
}

// -------------------------------------------------------------------------
// Put the thread to sleep for a delay, with wakeup count.
// This can only be called by the current thread on itself, hence
// it is a static function.

#ifdef CYGFUN_KERNEL_THREADS_TIMER
void
Cyg_Thread::counted_sleep( cyg_tick_count delay )
{
    CYG_REPORT_FUNCTION();

    Cyg_Thread *current = Cyg_Scheduler::get_current_thread();

    CYG_ASSERTCLASS( current, "Bad current thread" );
    
    CYG_INSTRUMENT_THREAD(SLEEP,current,0);
    
    // Prevent preemption
    Cyg_Scheduler::lock();

    if ( 0 == current->wakeup_count ) {

        // Set the timer (once outside any waiting loop.)
        set_timer( Cyg_Clock::real_time_clock->current_value()+delay,
                         Cyg_Thread::TIMEOUT  );

        // If the timeout is in the past, the wake reason will have been
        // set to something other than NONE already.
    
        if( current->get_wake_reason() == Cyg_Thread::NONE )
        {
            set_sleep_reason( Cyg_Thread::TIMEOUT );
            current->sleep();               // prepare to sleep
            current->state |= COUNTSLEEP;   // Set the state

            CYG_ASSERT( Cyg_Scheduler::get_sched_lock() == 1,
                    "Called with non-zero scheduler lock");
        
            Cyg_Scheduler::unlock();
            Cyg_Scheduler::lock();
    
            // clear the timer; if it actually fired, no worries.
            clear_timer();
        }
    }
    else
        // there is a queued wakeup, do not sleep
        current->wakeup_count--;

    // Unlock the scheduler and switch threads
    Cyg_Scheduler::unlock();

    // and deal with anything we must do when we return
    switch( current->wake_reason ) {
    case DESTRUCT:
    case EXIT:            
        current->exit();
        break;
        
    default:
        break;
    }

    CYG_REPORT_RETURN();
}
#endif

// -------------------------------------------------------------------------
// Awaken the thread from sleep.

void
Cyg_Thread::counted_wake()
{
    CYG_REPORT_FUNCTION();

    CYG_INSTRUMENT_THREAD(WAKE,this,Cyg_Scheduler::current_thread);
    
    // Prevent preemption
    Cyg_Scheduler::lock();

    if ( 0 == (state & COUNTSLEEP) )    // already awake, or waiting:
        wakeup_count++;                 // not in a counted sleep anyway.
    else {
        sleep_reason = NONE;
        wake_reason = DONE;
        wake();                         // and awaken the thread
    }

#ifdef CYGNUM_KERNEL_MAX_COUNTED_WAKE_COUNT_ASSERT
    CYG_ASSERT( CYGNUM_KERNEL_MAX_COUNTED_WAKE_COUNT_ASSERT > wakeup_count,
                "wakeup_count overflow" );
#endif

    // Unlock the scheduler and maybe switch threads
    Cyg_Scheduler::unlock();

    CYG_REPORT_RETURN();
}

// -------------------------------------------------------------------------
// Cancel wakeups for this thread and return how many were pending
cyg_uint32
Cyg_Thread::cancel_counted_wake()
{
    CYG_REPORT_FUNCTION();

    CYG_INSTRUMENT_THREAD(WAKE,this,Cyg_Scheduler::current_thread);
    
    // Prevent preemption
    Cyg_Scheduler::lock();

    cyg_uint32 result = wakeup_count;
    wakeup_count = 0;

    // Unlock the scheduler
    Cyg_Scheduler::unlock();

    CYG_REPORT_RETVAL( result );
    return result;
}

// -------------------------------------------------------------------------
// Suspend thread. Increment suspend count and deschedule thread
// if still running.

void
Cyg_Thread::suspend()
{
    CYG_REPORT_FUNCTION();

    CYG_INSTRUMENT_THREAD(SUSPEND,this,Cyg_Scheduler::current_thread);
    
    // Prevent preemption
    Cyg_Scheduler::lock();

    suspend_count++;
    
#ifdef CYGNUM_KERNEL_MAX_SUSPEND_COUNT_ASSERT
    CYG_ASSERT( CYGNUM_KERNEL_MAX_SUSPEND_COUNT_ASSERT > suspend_count,
                "suspend_count overflow" );
#endif

    // If running, remove from run qs
    if( state == RUNNING )
        Cyg_Scheduler::scheduler.rem_thread(this);

    // Set the state
    state |= SUSPENDED;
    
    // Unlock the scheduler and maybe switch threads
    Cyg_Scheduler::unlock();

    CYG_REPORT_RETURN();
}

// -------------------------------------------------------------------------
// Resume thread. Decrement suspend count and reschedule if it
// is zero.

void
Cyg_Thread::resume()
{
    CYG_REPORT_FUNCTION();

    CYG_INSTRUMENT_THREAD(RESUME,this,Cyg_Scheduler::current_thread);
            
    // Prevent preemption
    Cyg_Scheduler::lock();

    // If we are about to zero the count, clear the state bit and
    // reschedule the thread if possible.
    
    if( suspend_count == 1 )
    {
        suspend_count = 0;

        CYG_ASSERT( (state & SUSPENDED) != 0, "SUSPENDED bit not set" );
        
        // Set the state
        state &= ~SUSPENDED;

        // Return thread to scheduler if runnable
        if( state == RUNNING )
            Cyg_Scheduler::scheduler.add_thread(this);
    }
    else
        if( suspend_count > 0 )
            suspend_count--;
    // else ignore attempt to resume

    // Unlock the scheduler and maybe switch threads
    Cyg_Scheduler::unlock();
    CYG_REPORT_RETURN();
}

// -------------------------------------------------------------------------
// Forced Resume thread.  Zero suspend count and reschedule...

void
Cyg_Thread::force_resume()
{
    CYG_REPORT_FUNCTION();

    CYG_INSTRUMENT_THREAD(RESUME,this,Cyg_Scheduler::current_thread);
            
    // Prevent preemption
    Cyg_Scheduler::lock();

    // If we are about to zero the count, clear the state bit and
    // reschedule the thread if possible.
    
    if ( 0 < suspend_count ) {
        suspend_count = 0;

        CYG_ASSERT( (state & SUSPENDED) != 0, "SUSPENDED bit not set" );
        
        // Set the state
        state &= ~SUSPENDED;

        // Return thread to scheduler if runnable
        if( state == RUNNING )
            Cyg_Scheduler::scheduler.add_thread(this);
    }

    // Unlock the scheduler and maybe switch threads
    Cyg_Scheduler::unlock();
    CYG_REPORT_RETURN();
}

// -------------------------------------------------------------------------
// Force thread to wake up from a sleep with a wake_reason of
// BREAK. It is the responsibility of the woken thread to detect
// the release() and do the right thing.

void
Cyg_Thread::release()
{
    CYG_REPORT_FUNCTION();
    // Prevent preemption
    Cyg_Scheduler::lock();

    // If the thread is in any of the sleep states, set the
    // wake reason and wake it up.

    switch( sleep_reason )
    {

    case NONE:
        // The thread is not sleeping for any reason, do nothing.
        // drop through...
        
    case DESTRUCT:
    case BREAK:
    case EXIT:
    case DONE:
        // Do nothing in any of these cases. They are here to
        // keep the compiler happy.
        
        Cyg_Scheduler::unlock();
        CYG_REPORT_RETURN();
        return;

    case WAIT:
        // The thread was waiting for some sync object to do
        // something.
        // drop through...
        
    case TIMEOUT:
        // The thread was waiting on a sync object with a timeout.
        // drop through...
        
    case DELAY:
        // The thread was simply delaying, unless it has been
        // woken up for some other reason, wake it now.
        sleep_reason = NONE;
        wake_reason = BREAK;
        break;
    }

    wake();
    
    // Allow preemption
    Cyg_Scheduler::unlock();

    CYG_REPORT_RETURN();
}

// -------------------------------------------------------------------------
// Exit thread. This puts the thread into EXITED state.

void
Cyg_Thread::exit()
{
    // The thread should never return from this function.

    Cyg_Thread *self = Cyg_Thread::self();

    Cyg_Scheduler::lock();

    // clear the timer; if there was none, no worries.
    clear_timer();

    self->state = EXITED;

    Cyg_Scheduler::scheduler.rem_thread(self);

    // Un-nest any scheduler locks we have until we
    // suspend.
    for( ;; ) Cyg_Scheduler::unlock();
}

// -------------------------------------------------------------------------
// Kill thread. Force the thread into EXITED state externally, or
// make it wake up and call exit().

void
Cyg_Thread::kill()
{
    CYG_REPORT_FUNCTION();
    // If this is called by the current thread on itself,
    // just call exit(), which is what he should have done
    // in the first place.
    if( this == Cyg_Scheduler::get_current_thread() )
        exit();

    // Prevent preemption
    Cyg_Scheduler::lock();

    // We are killing someone else. Find out what state he is
    // in and force him to wakeup and call exit().

    force_resume();                     // this is necessary for when
                                        // he is asleep AND suspended.
#ifdef CYGFUN_KERNEL_THREADS_TIMER
    timer.disable();                    // and make sure the timer
                                        // does not persist.
#endif

    if ( EXIT != wake_reason ) switch( sleep_reason ) {
        // Only do any of this if the thread is not in pending death already:

    case NONE:
        // The thread is not sleeping for any reason, it must be
        // on a run queue.
        // We can safely deschedule and set its state.
        if( state == RUNNING ) Cyg_Scheduler::scheduler.rem_thread(this);
        state = EXITED;
        break;
        
    case DESTRUCT:
    case BREAK:
    case EXIT:
    case DONE:
        // Do nothing in any of these cases. They are here to
        // keep the compiler happy.
        
        Cyg_Scheduler::unlock();
        CYG_REPORT_RETURN();
        return;

    case WAIT:
        // The thread was waiting for some sync object to do
        // something.
        // drop through...
        
    case TIMEOUT:
        // The thread was waiting on a sync object with a timeout.
        // drop through...
        
    case DELAY:
        // The thread was simply delaying, unless it has been
        // woken up for some other reason, wake it now.
        sleep_reason = NONE;
        wake_reason = EXIT;
        break;
    }

    wake();

    // Allow preemption
    Cyg_Scheduler::unlock();
    CYG_REPORT_RETURN();
}

// -------------------------------------------------------------------------
// Set thread priority

#ifdef CYGIMP_THREAD_PRIORITY

void
Cyg_Thread::set_priority( cyg_priority new_priority )
{
    CYG_REPORT_FUNCTION();

//    CYG_ASSERT( new_priority >=  CYG_THREAD_MAX_PRIORITY, "Priority out of range");
//    CYG_ASSERT( new_priority <=  CYG_THREAD_MIN_PRIORITY, "Priority out of range");
    
    CYG_INSTRUMENT_THREAD(PRIORITY,this,priority);
        
    // Prevent preemption
    Cyg_Scheduler::lock();

    Cyg_ThreadQueue *queue = NULL;
    
    // If running, remove from run qs
    if( state == RUNNING )
        Cyg_Scheduler::scheduler.rem_thread(this);
    else if( state & SLEEPING )
    {
        // Remove thread from current queue.
        queue = get_current_queue();
        // if indeed we are on a queue
        if ( NULL != queue ) {
            CYG_CHECK_DATA_PTR(queue, "Bad queue pointer");        
            remove();
        }
    }

    Cyg_Scheduler::scheduler.deregister_thread(this);
    
#if CYG_SCHED_UNIQUE_PRIORITIES

    // Check that there are no other threads at this priority.
    // If so, leave is as it is.

    CYG_ASSERT( Cyg_Scheduler::scheduler.unique(new_priority), "Priority not unique");
    
    if( Cyg_Scheduler::scheduler.unique(new_priority) )
        priority = new_priority;

#else // !CYG_SCHED_UNIQUE_PRIORITIES

#ifdef CYGSEM_KERNEL_SYNCH_MUTEX_PRIORITY_INHERITANCE_SIMPLE

    // When we have priority inheritance, we must update the original
    // priority and not the inherited one.  If the new priority is
    // better than the current inherited one, then use that
    // immediately. We remain in inherited state to avoid problems
    // with multiple mutex inheritances.
    
    if( priority_inherited )
    {
        original_priority = new_priority;
        if( priority > new_priority ) priority = new_priority;
    }
    else priority = new_priority;
    
#else    

    priority = new_priority;

#endif
    
#endif // CYG_SCHED_UNIQUE_PRIORITIES

    Cyg_Scheduler::scheduler.register_thread(this);
    
    // Return thread to scheduler if runnable
    if( state == RUNNING )
        Cyg_Scheduler::scheduler.add_thread(this);
    else if ( state & SLEEPING )
    {
        // return to current queue
        // if indeed we are on a queue
        if ( NULL != queue ) {
            CYG_CHECK_DATA_PTR(queue, "Bad queue pointer");
            queue->enqueue(this);
        }
    }

    // If the current thread is being reprioritized, set the
    // reschedule flag to ensure that it gets rescheduled if
    // necessary. (Strictly we only need to do this if the new
    // priority is less than that of some other runnable thread, in
    // practice checking that is as expensive as what the scheduler
    // will do anyway).
    
    if( this == Cyg_Scheduler::get_current_thread() )
        Cyg_Scheduler::need_reschedule = true;
    
    // Unlock the scheduler and maybe switch threads
    Cyg_Scheduler::unlock();
    CYG_REPORT_RETURN();
}

#endif


// -------------------------------------------------------------------------
// Thread delay function

void
Cyg_Thread::delay( cyg_tick_count delay)
{
    CYG_REPORT_FUNCTION();

#ifdef CYGFUN_KERNEL_THREADS_TIMER

    CYG_INSTRUMENT_THREAD(DELAY,this,delay);

    // Prevent preemption
    Cyg_Scheduler::lock();
    
    sleep();

    set_timer( Cyg_Clock::real_time_clock->current_value()+delay, DELAY );

    // Unlock the scheduler and maybe switch threads
    Cyg_Scheduler::unlock();

    // Clear the timeout. It is irrelevant whether the alarm has
    // actually gone off or not.
    clear_timer();

    // and deal with anything else we must do when we return
    switch( wake_reason ) {
    case DESTRUCT:
    case EXIT:            
        exit();
        break;
        
    default:
        break;
    }
#endif
    CYG_REPORT_RETURN();
}

// -------------------------------------------------------------------------
//

#ifdef CYGPKG_KERNEL_EXCEPTIONS

void
Cyg_Thread::deliver_exception(
    cyg_code            exception_number,       // exception being raised
    CYG_ADDRWORD        exception_info          // exception specific info
    )
{
    if( this == Cyg_Scheduler::get_current_thread() )
    {
        // Delivering to current thread, probably as a result
        // of a real hardware exception. Simply invoke the appropriate
        // handler.

        exception_control.deliver_exception( exception_number, exception_info );
    }
#ifdef CYGIMP_EXCEPTION_ASYNC    
    else
    {
        // Delivering to another thread, probably as a result of one thread
        // invoking this function on another thread. Adjust the other thread's
        // state to make it execute the exception routine when it next runs.

        // At present there is an unresolved problem here. We do not know what
        // state the destination thread is in. It may not be a suitable point at
        // which to invoke an exception routine. In most cases the exception
        // routine will be run in the scheduler thread switch code, where the world is
        // in an inconsistent state. We really need to run the routine at the
        // end of unlock_inner(). However this would add extra code to the scheduler,
        // and require a way of storing pending exceptions. So for now this option is
        // disabled and not yet implemented, it may never be.
        
    }
#endif    
}

#endif

// -------------------------------------------------------------------------
// Per-thread data support

#ifdef CYGVAR_KERNEL_THREADS_DATA

// Set the data map bits for each free slot in the data array.
cyg_ucount32 Cyg_Thread::thread_data_map = (~CYGNUM_KERNEL_THREADS_DATA_ALL) &
                                           ((1<<CYGNUM_KERNEL_THREADS_DATA_MAX)-1);

cyg_ucount32
Cyg_Thread::new_data_index()
{
    Cyg_Scheduler::lock();

    cyg_ucount32 index;

    CYG_ASSERT( thread_data_map != 0 , "No more thread data indexes");
    
    // find ls set bit
    HAL_LSBIT_INDEX( index, thread_data_map );

    // clear the bit
    thread_data_map &= ~(1<<index);
    
    Cyg_Scheduler::unlock();

    return index;
}

void Cyg_Thread::free_data_index( cyg_ucount32 index )
{
    Cyg_Scheduler::lock();

    thread_data_map |= (1<<index);
    
    Cyg_Scheduler::unlock();    
}


#endif

// =========================================================================
// Cyg_ThreadTimer member functions

// -------------------------------------------------------------------------
// Timer alarm function. Inspect the sleep_reason and if necessary wake
// up the thread with an appropriate wake_reason.

#ifdef CYGFUN_KERNEL_THREADS_TIMER

void
Cyg_ThreadTimer::alarm(
    Cyg_Alarm           *alarm,
    CYG_ADDRWORD        data
)
{
    CYG_REPORT_FUNCTION();

    Cyg_ThreadTimer *self = (Cyg_ThreadTimer *)data;
    Cyg_Thread *thread = self->thread;
    
    CYG_INSTRUMENT_THREAD(ALARM, 0, 0);
    
    Cyg_Scheduler::lock();

    Cyg_Thread::cyg_reason sleep_reason = thread->get_sleep_reason();
    
    switch( sleep_reason ) {
        
    case Cyg_Thread::DESTRUCT:
    case Cyg_Thread::BREAK:
    case Cyg_Thread::EXIT:
    case Cyg_Thread::NONE:
    case Cyg_Thread::WAIT:
    case Cyg_Thread::DONE:
        // Do nothing in any of these cases. Most are here to
        // keep the compiler happy.
        Cyg_Scheduler::unlock();
        CYG_REPORT_RETURN();
        return;

    case Cyg_Thread::DELAY:
        // The thread was simply delaying, unless it has been
        // woken up for some other reason, wake it now.
        thread->set_wake_reason(Cyg_Thread::DONE);
        break;

    case Cyg_Thread::TIMEOUT:
        // The thread has timed out, set the wake reason to
        // TIMEOUT and restart.
        thread->set_wake_reason(Cyg_Thread::TIMEOUT);
        break;
    }

    thread->wake();

    Cyg_Scheduler::unlock();
    CYG_REPORT_RETURN();
}

#endif

// =========================================================================
// The Idle thread
// The idle thread is implemented as a single instance of the
// Cyg_IdleThread class. This is so that it can be initialized before
// main in a static constructor.

// -------------------------------------------------------------------------
// Data definitions

// stack
#ifdef CYGNUM_HAL_STACK_SIZE_MINIMUM
# ifdef CYGNUM_KERNEL_THREADS_IDLE_STACK_SIZE
#  if CYGNUM_KERNEL_THREADS_IDLE_STACK_SIZE < CYGNUM_HAL_STACK_SIZE_MINIMUM

// then override the configured stack size
#   undef CYGNUM_KERNEL_THREADS_IDLE_STACK_SIZE
#   define CYGNUM_KERNEL_THREADS_IDLE_STACK_SIZE CYGNUM_HAL_STACK_SIZE_MINIMUM

#  endif // CYGNUM_KERNEL_THREADS_IDLE_STACK_SIZE < CYGNUM_HAL_STACK_SIZE_MINIMUM
# endif // CYGNUM_KERNEL_THREADS_IDLE_STACK_SIZE
#endif // CYGNUM_HAL_STACK_SIZE_MINIMUM

static char idle_thread_stack[CYGNUM_KERNEL_THREADS_IDLE_STACK_SIZE];

// Loop counter for debugging/housekeeping
cyg_uint32 idle_thread_loops = 1;

// -------------------------------------------------------------------------
// Idle thread code.

void
idle_thread_main( CYG_ADDRESS data )
{
    CYG_REPORT_FUNCTION();

    for(;;)
    {
        idle_thread_loops++;

        HAL_IDLE_THREAD_ACTION(idle_thread_loops);

#if 0
        // For testing, it is useful to be able to fake
        // clock interrupts in the idle thread.
        
        Cyg_Clock::real_time_clock->tick();
#endif
#ifdef CYGIMP_IDLE_THREAD_YIELD
        // In single priority and non-preemptive systems,
        // the idle thread should yield repeatedly to
        // other threads.
        Cyg_Thread::yield();
#endif
    }
}

// -------------------------------------------------------------------------
// Idle thread class

class Cyg_IdleThread : public Cyg_Thread
{
public:
    Cyg_IdleThread(
        cyg_thread_entry        *entry,           // entry point function
        CYG_ADDRWORD            entry_data,       // entry data
        cyg_ucount32            stack_size = 0,   // stack size, 0 = use default
        CYG_ADDRESS             stack_base = 0    // stack base, NULL = allocate
        );
        
};

// -------------------------------------------------------------------------
// Idle threads constructor

Cyg_IdleThread::Cyg_IdleThread(
    cyg_thread_entry        *entry,           // entry point function
    CYG_ADDRWORD            entry_data,       // entry data
    cyg_ucount32            stack_size,       // stack size, 0 = use default
    CYG_ADDRESS             stack_base        // stack base, NULL = allocate
    )
    : Cyg_Thread( CYG_THREAD_MIN_PRIORITY,
                  entry,
                  entry_data,
                  "Idle Thread",
                  stack_base,
                  stack_size)
{
    CYG_REPORT_FUNCTION();

    resume();
    CYG_REPORT_RETURN();
}

// -------------------------------------------------------------------------
// Instantiate the idle thread

Cyg_IdleThread idle_thread CYG_INIT_PRIORITY( IDLE_THREAD ) =
Cyg_IdleThread( idle_thread_main,
                0,
                CYGNUM_KERNEL_THREADS_IDLE_STACK_SIZE,
                CYG_ADDRESS(idle_thread_stack)
    ); 


// -------------------------------------------------------------------------
// EOF common/thread.cxx
