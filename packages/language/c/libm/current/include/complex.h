#ifndef	CYGONCE_COMPLEX_H
#define	CYGONCE_COMPLEX_H

//===========================================================================
//
//      complex.h
//
//      Standard complex number functions conforming to ANSI and other standards
//
//===========================================================================
// ####ECOSGPLCOPYRIGHTBEGIN####                                            
// -------------------------------------------                              
// This file is part of eCos, the Embedded Configurable Operating System.   
// Copyright (C) 2013 Free Software Foundation, Inc.
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
// Author(s):   ilijak
// Based on:    see below
// Contributors:
// Date:        2013-06-05
// Purpose:
// Description: Standard complex number mathematical functions.
//
// Usage:       #include <complex.h>
//
//####DESCRIPTIONEND####
//
//===========================================================================

// This file was derived from a file with following copyright

/* $NetBSD: complex.h,v 1.1 2013/08/25 14:38:57 vae Exp $ */

/*
 * Written by Matthias Drochner.
 * Public domain.
 */

#ifndef _COMPLEX_H
#define _COMPLEX_H
#endif

#define complex _Complex
#define _Complex_I (1.0fi)
#define I _Complex_I

// 7.3.5 Trigonometric functions
// 7.3.5.1 The cacos functions
double complex cacos(double complex);
float complex cacosf(float complex);

// 7.3.5.2 The casin functions
double complex casin(double complex);
float complex casinf(float complex);

// 7.3.5.1 The catan functions
double complex catan(double complex);
float complex catanf(float complex);

// 7.3.5.1 The ccos functions
double complex ccos(double complex);
float complex ccosf(float complex);

// 7.3.5.1 The csin functions
double complex csin(double complex);
float complex csinf(float complex);

// 7.3.5.1 The ctan functions
double complex ctan(double complex);
float complex ctanf(float complex);

// 7.3.6 Hyperbolic functions
// 7.3.6.1 The cacosh functions
double complex cacosh(double complex);
float complex cacoshf(float complex);

// 7.3.6.2 The casinh functions
double complex casinh(double complex);
float complex casinhf(float complex);

// 7.3.6.3 The catanh functions
double complex catanh(double complex);
float complex catanhf(float complex);

// 7.3.6.4 The ccosh functions
double complex ccosh(double complex);
float complex ccoshf(float complex);

// 7.3.6.5 The csinh functions
double complex csinh(double complex);
float complex csinhf(float complex);

// 7.3.6.6 The ctanh functions
double complex ctanh(double complex);
float complex ctanhf(float complex);

// 7.3.7 Exponential and logarithmic functions
// 7.3.7.1 The cexp functions
double complex cexp(double complex);
float complex cexpf(float complex);

// 7.3.7.2 The clog functions
double complex clog(double complex);
float complex clogf(float complex);

// 7.3.9 Manipulation functions
// 7.3.9.2 The cimag functions
double cimag(double complex);
float cimagf(float complex);
//long double cimagl(long double complex);

// 7.3.9.3 The conj functions
double complex conj(double complex);
float complex conjf(float complex);
//long double complex conjl(long double complex);

// 7.3.9.4 The cproj functions
double complex cproj(double complex);
float complex cprojf(float complex);
//long double complex cprojl(long double complex);

// 7.3.9.5 The creal functions
double creal(double complex);
float crealf(float complex);
//long double creall(long double complex);

// 7.3.9.1 The carg functions
#ifdef CYGSEM_LIBM_IEEE_API_INLINE
CYGBLD_FORCE_INLINE double
carg(double complex z)
{
	return atan2( cimag(z) , creal(z) );
}

CYGBLD_FORCE_INLINE float
cargf(float complex z)
{
	return atan2f( cimagf(z) , crealf(z) );
}
#else
double carg(double complex);
float cargf(float complex);
#endif

// 7.3.8 Power and absolute-value functions
// 7.3.8.1 The cabs functions
#ifdef CYGSEM_LIBM_IEEE_API_INLINE
CYGBLD_FORCE_INLINE double
cabs(double complex z)
{
	return hypot( creal(z) , cimag(z) );
}

CYGBLD_FORCE_INLINE float
cabsf(float complex z)
{
	return hypotf( crealf(z) , cimagf(z) );
}
#else
double cabs(double complex) ;
float cabsf(float complex) ;
#endif

// 7.3.8.2 The cpow functions
double complex cpow(double complex, double complex);
float complex cpowf(float complex, float complex);

// 7.3.8.3 The csqrt functions
double complex csqrt(double complex);
float complex csqrtf(float complex);

#endif //CYGONCE_COMPLEX_H

// End of complex.h
