#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin

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
    double popcorn2_3D_x;
    double popcorn2_3D_y;
	double popcorn2_3D_z;
    double popcorn2_3D_c;
	double combYZ;
	double combXZ;
	double combXY;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("popcorn2_3D");

// Define the Variables
APO_VARIABLES(
    VAR_REAL(popcorn2_3D_x, 0.1),
    VAR_REAL(popcorn2_3D_y, 0.1),
	VAR_REAL(popcorn2_3D_z, 0.1),
    VAR_REAL(popcorn2_3D_c, 3.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(combYZ) = atan2(FTy,FTz);
	VAR(combXZ) = atan2(FTx,FTz);
	VAR(combXY) = atan(sqrt((FTx*FTx)+(FTy*FTy)));
	
	// Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double inZ, otherZ, tempTZ, tempPZ, tmpVV;
	inZ = FTz;
	otherZ = FPz;
	
	if(fabs(VVAR <=1.0))
	{
	    tmpVV = fabs(VVAR)*VVAR;    //sqr(VVAR) value retaining sign
	}
	else
	{
	    tmpVV = VVAR;
	}
	if(otherZ == 0.0)
	{	
		tempPZ = tmpVV*sin(tan(VAR(popcorn2_3D_c)))*atan2(FTy,FTx); 		
	}
	else
	{
	    tempPZ = FPz;
	}
	if(inZ == 0.0)
	{
		tempTZ = tmpVV*sin(tan(VAR(popcorn2_3D_c)))*atan2(FTy,FTx);
	}
	else
	{
	    tempTZ = FTz;
	}
	
	FPx += VVAR * 0.5 * (FTx + VAR(popcorn2_3D_x) * sin(tan(VAR(popcorn2_3D_c)*FTy)));
	FPy += VVAR * 0.5 * (FTy + VAR(popcorn2_3D_y) * sin(tan(VAR(popcorn2_3D_c)*FTx))); 
	FPz = tempPZ+tmpVV*(VAR(popcorn2_3D_z)*sin(tan(VAR(popcorn2_3D_c)))*tempTZ); 
		
	/*
	    Original code:	
    FPx += VVAR * (FTx + VAR(popcorn2_x) * sin(tan(VAR(popcorn2_c)*FTy)));
    FPy += VVAR * (FTy + VAR(popcorn2_y) * sin(tan(VAR(popcorn2_c)*FTx)));
	*/

    return TRUE;
}








