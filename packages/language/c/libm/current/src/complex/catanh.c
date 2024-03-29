/* $NetBSD: catanh.c,v 1.1 2013/08/25 14:38:58 vae Exp $ */

/*-
 * Copyright (c) 2007 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software written by Stephen L. Moshier.
 * It is redistributed by the NetBSD Foundation by permission of the author.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * imported and modified include for newlib 2010/10/03 
 * Marco Atzeri <marco_atzeri@yahoo.it>
 */

/*
FUNCTION
        <<catanh>>, <<catanhf>>---complex arc hyperbolic tangent

INDEX
        catanh
INDEX
        catanhf

ANSI_SYNOPSIS
       #include <complex.h>
       double complex catanh(double complex <[z]>);
       float complex catanhf(float complex <[z]>);


DESCRIPTION
        These functions compute the complex arc hyperbolic tan of <[z]>,
        with branch cuts outside the interval [-1, +1] along the
        real axis.

        <<catanhf>> is identical to <<catanh>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        @ifnottex
        These functions return the complex arc hyperbolic tangent value,
        in the range of a strip mathematically unbounded along the
        real axis and in the interval [-i*p/2, +i*p/2] along the
        imaginary axis.
        @end ifnottex
        @tex
        These functions return the complex arc hyperbolic tangent value,
        in the range of a strip mathematically unbounded along the
        real axis and in the interval [$-i\pi/2$, $+i\pi/2$] along the
        imaginary axis.
        @end tex

PORTABILITY
        <<catanh>> and <<catanhf>> are ISO C99

QUICKREF
        <<catanh>> and <<catanhf>> are ISO C99

*/


#include <complex.h>

double complex
catanh(double complex z)
{
	double complex w;

	w = -1.0 * I * catan(z * I);
	return w;
}
