/*
    Apophysis Plugin
    
    Copyright (C) 2007-2013 Michael Faber

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
	double target_even;
	double target_odd;
	double target_size;
	double t_size_2;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("target");

// Define the Variables
APO_VARIABLES(
	VAR_REAL_CYCLE(target_even, 0.0, M_2PI, 0.0),
	VAR_REAL_CYCLE(target_odd, 0.0, M_2PI, 0.0),
	VAR_REAL_RANGE(target_size, EPS, DBL_MAX, 1.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
	VAR(t_size_2) = 0.5 * VAR(target_size);
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
	double a = atan2(FTy, FTx);
	double r = sqrt( sqr(FTx) + sqr(FTy));
	double s, c;
	double t = log(r);
	if ( t < 0.0)
		t -= VAR(t_size_2);
	
	t = fmod (fabs(t), VAR(target_size));
	
	if (  t < VAR(t_size_2))
		a += VAR(target_even);
	else
		a += VAR(target_odd);
	
	fsincos( a, &s, &c);
	

	FPx += r * c;
	FPy += r * s;


    return TRUE;
}
