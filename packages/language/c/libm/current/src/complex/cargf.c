/* $NetBSD: cargf.c,v 1.1 2013/08/25 14:38:57 vae Exp $ */

/*
 * Written by Matthias Drochner <drochner@NetBSD.org>.
 * Public domain.
 *
 * imported and modified include for newlib 2010/10/03 
 * Marco Atzeri <marco_atzeri@yahoo.it>
 */

#include <complex.h>
#include <math.h>

float
cargf(float complex z)
{

	return atan2f( cimagf(z), crealf(z) );
}
