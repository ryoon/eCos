//===========================================================================
//
//      s_modf.c
//
//      Part of the standard mathematical function library
//
//===========================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####                                            
// -------------------------------------------                              
// This file is part of eCos, the Embedded Configurable Operating System.   
// Copyright (C) 1998, 1999, 2000, 2001, 2002 Free Software Foundation, Inc.
//
// eCos is free software; you can redistribute it and/or modify it under    
// the terms of the GNU General Public License as published by the Free     
// Software Foundation; either version 2 or (at your option) any later      
// version.                                                                 
//
// eCos is distributed in the hope that it will be useful, but WITHOUT      
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or    
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    
// for more details.                                                        
//
// You should have received a copy of the GNU General Public License        
// along with eCos; if not, write to the Free Software Foundation, Inc.,    
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.            
//
// As a special exception, if other files instantiate templates or use      
// macros or inline functions from this file, or you compile this file      
// and link it with other works to produce a work based on this file,       
// this file does not by itself cause the resulting work to be covered by   
// the GNU General Public License. However the source code for this file    
// must still be made available in accordance with section (3) of the GNU   
// General Public License v2.                                               
//
// This exception does not invalidate any other reasons why a work based    
// on this file might be covered by the GNU General Public License.         
// -------------------------------------------                              
// ####ECOSGPLCOPYRIGHTEND####                                              
//===========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):   jlarmour
// Contributors:  jlarmour
// Date:        1998-02-13
// Purpose:     
// Description: 
// Usage:       
//
//####DESCRIPTIONEND####
//
//===========================================================================

// CONFIGURATION

#include <pkgconf/libm.h>   // Configuration header

// Include the Math library?
#ifdef CYGPKG_LIBM     

// Derived from code with the following copyright


/* @(#)s_modf.c 1.3 95/01/18 */
/*
 * ====================================================
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 *
 * Developed at SunSoft, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this
 * software is freely granted, provided that this notice 
 * is preserved.
 * ====================================================
 */

/*
 * modf(double x, double *iptr) 
 * return fraction part of x, and return x's integral part in *iptr.
 * Method:
 *      Bit twiddling.
 *
 * Exception:
 *      No exception.
 */

#include "mathincl/fdlibm.h"

static const double one = 1.0;

        double modf(double x, double *iptr)
{
        int i0,i1,j0;
        unsigned i;
        i0 =  CYG_LIBM_HI(x);           /* high x */
        i1 =  CYG_LIBM_LO(x);           /* low  x */
        j0 = ((i0>>20)&0x7ff)-0x3ff;    /* exponent of x */
        if(j0<20) {                     /* integer part in high x */
            if(j0<0) {                  /* |x|<1 */
                CYG_LIBM_HIp(iptr) = i0&0x80000000;
                CYG_LIBM_LOp(iptr) = 0;         /* *iptr = +-0 */
                return x;
            } else {
                i = (0x000fffff)>>j0;
                if(((i0&i)|i1)==0) {            /* x is integral */
                    *iptr = x;
                    CYG_LIBM_HI(x) &= 0x80000000;
                    CYG_LIBM_LO(x)  = 0;        /* return +-0 */
                    return x;
                } else {
                    CYG_LIBM_HIp(iptr) = i0&(~i);
                    CYG_LIBM_LOp(iptr) = 0;
                    return x - *iptr;
                }
            }
        } else if (j0>51) {             /* no fraction part */
            *iptr = x*one;
            CYG_LIBM_HI(x) &= 0x80000000;
            CYG_LIBM_LO(x)  = 0;        /* return +-0 */
            return x;
        } else {                        /* fraction part in low x */
            i = ((unsigned)(0xffffffff))>>(j0-20);
            if((i1&i)==0) {             /* x is integral */
                *iptr = x;
                CYG_LIBM_HI(x) &= 0x80000000;
                CYG_LIBM_LO(x)  = 0;    /* return +-0 */
                return x;
            } else {
                CYG_LIBM_HIp(iptr) = i0;
                CYG_LIBM_LOp(iptr) = i1&(~i);
                return x - *iptr;
            }
        }
}

#endif // ifdef CYGPKG_LIBM     

// EOF s_modf.c
