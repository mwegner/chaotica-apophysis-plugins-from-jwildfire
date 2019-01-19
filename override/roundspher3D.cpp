/*
Apophysis Plugin

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
/*
    3D Mod of a 2D plugin  
	This code supports 3D operations in 
	Apophysis 2.08 3D hack
	modified by Larry Berlin   September 2009
	http://apophysisrevealed.com/
	http://aporev.deviantart.com/
*/

// Must define this structure before we include apoplugin.h
typedef struct
{            
} Variables;

#include "apoplugin.h"


// Set the name of this plugin
APO_PLUGIN("roundspher3D");

// Define the Variables
APO_VARIABLES(
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
// Multiplication is faster than division, so divide in precalc, multiply in calc.

return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double inZ, otherZ, tempTZ, tempPZ, d, e;
	inZ = FTz;
	otherZ = FPz;
	double f = sqrt(sqr(FTx)+sqr(FTy));
	double a = atan2(FTy,FTx);
	
	if(inZ == 0.0)
	{
	    tempTZ = cos(f);
	}
	else
	{
	    tempTZ = FTz;
	}
	if(otherZ == 0.0)
	{
	    tempPZ = cos(f);
	}
	else
	{
	    tempPZ = FPz;
	}
	d = sqr(FTx)+sqr(FTy)+sqr(tempTZ);	
    e = 1/d+sqr(M_2_PI);
    
    FPx += VVAR * (VVAR/d*FTx/e);
    FPy += VVAR * (VVAR/d*FTy/e);
	FPz = tempPZ + VVAR * (VVAR/d*tempTZ/e);

return TRUE;
}

