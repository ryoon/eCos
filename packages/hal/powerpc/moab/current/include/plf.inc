#ifndef CYGONCE_HAL_PLF_INC
#define CYGONCE_HAL_PLF_INC
##=============================================================================
##
##	plf.inc
##
##	PPC40x family assembler header file
##
##=============================================================================
## ####ECOSGPLCOPYRIGHTBEGIN####                                            
## -------------------------------------------                              
## This file is part of eCos, the Embedded Configurable Operating System.   
## Copyright (C) 1998, 1999, 2000, 2001, 2002, 2003 Free Software Foundation, Inc.
##
## eCos is free software; you can redistribute it and/or modify it under    
## the terms of the GNU General Public License as published by the Free     
## Software Foundation; either version 2 or (at your option) any later      
## version.                                                                 
##
## eCos is distributed in the hope that it will be useful, but WITHOUT      
## ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or    
## FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License    
## for more details.                                                        
##
## You should have received a copy of the GNU General Public License        
## along with eCos; if not, write to the Free Software Foundation, Inc.,    
## 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.            
##
## As a special exception, if other files instantiate templates or use      
## macros or inline functions from this file, or you compile this file      
## and link it with other works to produce a work based on this file,       
## this file does not by itself cause the resulting work to be covered by   
## the GNU General Public License. However the source code for this file    
## must still be made available in accordance with section (3) of the GNU   
## General Public License v2.                                               
##
## This exception does not invalidate any other reasons why a work based    
## on this file might be covered by the GNU General Public License.         
## -------------------------------------------                              
## ####ECOSGPLCOPYRIGHTEND####                                              
##=============================================================================
#######DESCRIPTIONBEGIN####
##
## Author(s): 	jskov
## Contributors:jskov, gthomas
## Date:	2000-08-27
## Purpose:	PPC40x family definitions.
## Description:	This file contains various definitions and macros that are
##              useful for writing assembly code for the PPC40x CPU family.
## Usage:
##		#include <cyg/hal/plf.inc>
##		...
##		
##
######DESCRIPTIONEND####
##
##=============================================================================

#ifdef CYG_HAL_STARTUP_ROMRAM
        .macro hal_reserved_vector_00000
        b   _start
        .endm
#define CYG_HAL_RESERVED_VECTOR_00000
#endif

#endif // CYGONCE_HAL_PLF_INC
