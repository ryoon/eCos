/* $NetBSD: cpow.c,v 1.1 2013/08/25 14:38:58 vae Exp $ */

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
        <<cpow>>, <<cpowf>>---complex power

INDEX
        cpow
INDEX
        cpowf

ANSI_SYNOPSIS
       #include <complex.h>
       double complex cpow(double complex <[x]>, double complex <[y]>);
       float complex cpowf(float complex <[x]>, float complex <[y]>);


DESCRIPTION
        @ifnottex
        The cpow functions compute the complex power function x^y 
        power, with a branch cut for the first parameter along the 
        negative real axis.
        @end ifnottex
        @tex
        The cpow functions compute the complex power function $x^y$ 
        power, with a branch cut for the first parameter along the 
        negative real axis.
        @end tex

        <<cpowf>> is identical to <<cpow>>, except that it performs
        its calculations on <<floats complex>>.

RETURNS
        The cpow functions return the complex power function value.

PORTABILITY
        <<cpow>> and <<cpowf>> are ISO C99

QUICKREF
        <<cpow>> and <<cpowf>> are ISO C99

*/


#include <complex.h>
#include <math.h>

double complex
cpow(double complex a, double complex z)
{
	double complex w;
	double x, y, r, theta, absa, arga;

	x = creal(z);
	y = cimag(z);
	absa = cabs(a);
	if (absa == 0.0) {
		return (0.0 + 0.0 * I);
	}
	arga = carg(a);
	r = pow(absa, x);
	theta = x * arga;
	if (y != 0.0) {
		r = r * exp(-y * arga);
		theta = theta + y * log(absa);
	}
	w = r * cos(theta) + (r * sin(theta)) * I;
	return w;
}
