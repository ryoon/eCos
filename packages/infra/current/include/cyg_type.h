#ifndef CYGONCE_INFRA_CYG_TYPE_H
#define CYGONCE_INFRA_CYG_TYPE_H

//==========================================================================
//
//	cyg_type.h
//
//	Standard types, and some useful coding macros.
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
// by Cygnus are Copyright (C) 1998 Cygnus Solutions.  All Rights Reserved.
// -------------------------------------------
//
//####COPYRIGHTEND####
//==========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):   nickg from an original by hmt
// Contributors:  nickg
// Date:        1997-09-08
// Purpose:     share unambiguously sized types.
// Description:	we typedef [cyg_][u]int8,16,32 &c for general use.
// Usage:       #include "cyg/infra/cyg_type.h"
//		...
//		cyg_int32 my_32bit_integer;
//		
//####DESCRIPTIONEND####
//

#include <pkgconf/infra.h>    // Configuration header for the infra package
#include <stddef.h>           // Definition of NULL from the compiler

// -------------------------------------------------------------------------
// Some useful macros. These are defined here by default.

// externC is used in mixed C/C++ headers to force C linkage on an external
// definition. It avoids having to put all sorts of ifdefs in.

#ifdef __cplusplus
# define externC extern "C"
#else
# define externC extern
#endif


// -------------------------------------------------------------------------
// The header <basetype.h> defines the base types used here. It is
// supplied either by the target architecture HAL, or by the host
// porting kit. They are all defined as macros, and only those that
// make choices other than the defaults given below need be defined.

#define CYG_LSBFIRST 1234
#define CYG_MSBFIRST 4321

#include <cyg/hal/basetype.h>

#if (CYG_BYTEORDER != CYG_LSBFIRST) && (CYG_BYTEORDER != CYG_MSBFIRST)
# error You must define CYG_BYTEORDER to equal CYG_LSBFIRST or CYG_MSBFIRST
#endif


#ifndef cyg_halint8
# define cyg_halint8 char
#endif
#ifndef cyg_halint16
# define cyg_halint16 short
#endif
#ifndef cyg_halint32
# define cyg_halint32 int
#endif
#ifndef cyg_halint64
# define cyg_halint64 long long
#endif

#ifndef cyg_halcount8
# define cyg_halcount8 int
#endif
#ifndef cyg_halcount16
# define cyg_halcount16 int
#endif
#ifndef cyg_halcount32
# define cyg_halcount32 int
#endif
#ifndef cyg_halcount64
# define cyg_halcount64 long long
#endif

#ifndef cyg_halbool
# ifdef __cplusplus
#  define cyg_halbool bool
# else
#  define cyg_halbool int
# endif
#endif

#ifndef cyg_halatomic
# define cyg_halatomic cyg_halint8
#endif

// -------------------------------------------------------------------------
// The obvious few that compilers may define for you.
// But in case they don't:

#ifndef NULL
# define NULL 0
#endif

#ifndef __cplusplus

typedef cyg_halbool bool;

# ifndef false
#  define false 0
# endif

# ifndef true
#  define true (!false)
# endif

#endif

// -------------------------------------------------------------------------
// Allow creation of procedure-like macros that are a single statement,
// and must be followed by a semi-colon

#define CYG_MACRO_START do {
#define CYG_MACRO_END   } while (0)

#define CYG_EMPTY_STATEMENT CYG_MACRO_START CYG_MACRO_END

#define CYG_UNUSED_PARAM( _type_, _name_ ) CYG_MACRO_START \
  _type_ tmp1 = _name_; \
  _name_ = tmp1; \
CYG_MACRO_END

// -------------------------------------------------------------------------
// Define basic types for using integers in memory and structures;
// depends on compiler defaults and CPU type.

typedef unsigned cyg_halint8    cyg_uint8  ;
typedef   signed cyg_halint8    cyg_int8   ;

typedef unsigned cyg_halint16   cyg_uint16 ;
typedef   signed cyg_halint16   cyg_int16  ;

typedef unsigned cyg_halint32   cyg_uint32 ;
typedef   signed cyg_halint32   cyg_int32  ;

typedef unsigned cyg_halint64   cyg_uint64 ;
typedef   signed cyg_halint64   cyg_int64  ;

typedef  cyg_halbool            cyg_bool   ;

// -------------------------------------------------------------------------
// Define types for using integers in registers for looping and the like;
// depends on CPU type, choose what it is most comfortable with, with at
// least the range required.

typedef unsigned cyg_halcount8  cyg_ucount8  ;
typedef   signed cyg_halcount8  cyg_count8   ;

typedef unsigned cyg_halcount16 cyg_ucount16 ;
typedef   signed cyg_halcount16 cyg_count16  ;

typedef unsigned cyg_halcount32 cyg_ucount32 ;
typedef   signed cyg_halcount32 cyg_count32  ;

typedef unsigned cyg_halcount64 cyg_ucount64 ;
typedef   signed cyg_halcount64 cyg_count64  ;

// -------------------------------------------------------------------------
// Define a type to be used for atomic accesses. This type is guaranteed
// to be read or written in a single uninterruptible operation. This type
// is at least a single byte.

typedef volatile unsigned cyg_halatomic  cyg_atomic;
typedef volatile unsigned cyg_halatomic  CYG_ATOMIC;

// -------------------------------------------------------------------------
// Define types for access plain, on-the-metal memory or devices.

typedef cyg_uint32  CYG_WORD;
typedef cyg_uint8   CYG_BYTE;
typedef cyg_uint16  CYG_WORD16;
typedef cyg_uint32  CYG_WORD32;
typedef cyg_uint64  CYG_WORD64;
typedef cyg_uint32  CYG_ADDRESS;
typedef CYG_ADDRESS CYG_ADDRWORD;

// -------------------------------------------------------------------------
// Constructor ordering macros.  These are added as annotations to all
// static objects to order the constuctors appropriately.

#if defined(__cplusplus) && defined(CYG_KERNEL_USE_INIT_PRIORITY)

#define CYG_INIT_PRIORITY( _pri_ ) \
    __attribute__((init_priority (CYG_INIT_##_pri_)))
    
#else

#define CYG_INIT_PRIORITY( _pri_ )

#endif

#define CYG_INIT_BEFORE( _pri_ ) (CYG_INIT_##_pri_-100)
#define CYG_INIT_AFTER( _pri_ ) (CYG_INIT_##_pri_+100)

#define CYG_INIT_HAL                    10000
#define CYG_INIT_SCHEDULER              11000
#define CYG_INIT_INTERRUPTS             12000
#define CYG_INIT_CLOCK                  13000
#define CYG_INIT_IDLE_THREAD            14000
#define CYG_INIT_THREADS                15000
#define CYG_INIT_KERNEL                 40000
#define CYG_INIT_LIBC                   50000
#define CYG_INIT_APPLICATION            65000
#define CYG_INIT_DEFAULT                65535

// -------------------------------------------------------------------------
// Define a compiler-specific rune for saying a function doesn't return

#ifdef __GNUC__
# define CYGBLD_NORET __attribute__((noreturn))
#else
# define CYGBLD_NORET
#endif

#ifdef __GNUC__
# define CYGBLD_ATTRIB_WEAK __attribute__ ((weak))
#else
    // This intentionally gives an error only if we actually try to
    // use it.  #error would give an error if we simple can't.
# define CYGBLD_ATTRIB_WEAK !!!-- Attribute weak not defined --!!!
#endif

// -------------------------------------------------------------------------
// Label name macro. Some toolsets generate labels with initial
// underscores and others don't. This macro should be used on labels
// that are defined in assembly code or linker scripts so that we can
// do the right thing.

#ifndef CYG_LABEL_NAME

#define CYG_LABEL_NAME(_name_) _name_

#endif

// -------------------------------------------------------------------------
#endif // CYGONCE_INFRA_CYG_TYPE_H multiple inclusion protection
// EOF cyg_type.h
