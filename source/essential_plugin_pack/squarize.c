/*
    Apophysis Plugin

    Copyright (C) 2007-2012 Joel Faber
    Copyright (C) 2007-2012 Michael Faber

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

// Must define this structure before we include apoplugin.h
typedef struct
{
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("squarize");

// Define the Variables
APO_VARIABLES(
    
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{

    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    
    double s = sqrt(sqr(FTx) + sqr(FTy));
    double a = atan2(FTy, FTx);
    if ( a < 0.0)
       a += M_2PI;
    double p = 4.0 * s * a * M_1_PI;
    
    if( p <= 1.0 * s )
    {
        FPx += VVAR * s;
        FPy += VVAR * p;
    }
    else if( p <= 3.0 * s)
    {
        FPx += VVAR * ( 2.0 * s - p);
        FPy += VVAR * (s);
    }
    else if( p <= 5.0 * s)
    {
        FPx -= VVAR * (s);
        FPy += VVAR * ( 4.0 * s - p);
    }
    else if( p <= 7.0 * s)
    {
        FPx -= VVAR * (6.0 * s - p);
        FPy -= VVAR * (s);
    }
    else
    {
        FPx += VVAR * (s);
        FPy -= VVAR * ( 8.0 * s - p);
    }

	return TRUE;
}
