/*
    Apophysis Plugin

    Copyright (C) 2007-2011 Joel Faber
    Copyright (C) 2007-2011 Michael Faber

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
    double eclipse_shift;
    double eclipse_x;
    double eclipse_y;

} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("eclipse");

// Define the Variables
APO_VARIABLES(
    VAR_REAL_CYCLE(eclipse_shift, -2.0, 2.0, 0.0)
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
    double c_2;
	double x;
	
	
	if(fabs(FTy) <= VVAR)
	{
        c_2 = sqrt( sqr(VVAR) - sqr(FTy));

    	if ( fabs(FTx)  <= c_2)
    	{
            x = FTx + VAR(eclipse_shift) * VVAR;
            if ( fabs(x) >= c_2)
            {
                FPx -= VVAR * FTx;
            }
            else
            {
                FPx += VVAR * x;
            }
        }
        else
        {
            FPx += VVAR * FTx;
        }
        FPy += VVAR * FTy;
    }
    else
    {
        FPx += VVAR * FTx;
        FPy += VVAR * FTy;
    }

    return TRUE;
}
