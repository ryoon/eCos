//===========================================================================
//
//      infconst.c
//
//      Infinity constant
//
//===========================================================================
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
//===========================================================================
//#####DESCRIPTIONBEGIN####
//
// Author(s):   jlarmour@cygnus.co.uk
// Contributors:  jlarmour@cygnus.co.uk
// Date:        1998-02-13
// Purpose:     
// Description: Defines a constant cyg_libm_infinity so that we can define
//              HUGE_VAL
// Usage:       
//
//####DESCRIPTIONEND####
//
//===========================================================================

// CONFIGURATION

#include <pkgconf/libm.h>   // Configuration header

// Include the Math library?
#ifdef CYGPKG_LIBM     

// INCLUDES

#include <cyg/infra/cyg_type.h>    // Common type definitions and support
                                   // including endian-ness
#include <math.h>                  // Main header for math library
#include <sys/ieeefp.h>            // Cyg_libm_ieee_double_shape_type


// GLOBALS

#if (CYG_BYTEORDER == CYG_MSBFIRST) // Big endian

const Cyg_libm_ieee_double_shape_type cyg_libm_infinity = { {0x7ff00000, 0} };

#else  // Little endian

const Cyg_libm_ieee_double_shape_type cyg_libm_infinity = { {0, 0x7ff00000} };

#endif

#endif // ifdef CYGPKG_LIBM

// EOF infconst.c
