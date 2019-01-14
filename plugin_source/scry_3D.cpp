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
	modified by Larry Berlin   August 2009
	http://apophysisrevealed.com
*/

// Must define this structure before we include apoplugin.h
typedef struct
{
	double VVAR_inv;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("scry_3D");

// Define the Variables
APO_VARIABLES(
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
	VAR(VVAR_inv) = 1.0 / (VVAR + EPS);
    return TRUE; // Always return TRUE.
}

int PluginVarCalc(Variation* vp)
{
	double t = sqr(FTx) + sqr(FTy); 
    double smooth, Footzee, Foopzee, kikr, r, u, s;	
	smooth = 0.0;
    kikr = cos(sqrt(t));
	Footzee = FTz;
	Foopzee = FPz;
	if(Foopzee==0.0)
	{
	    Foopzee = kikr;  // 
	}
	if(Footzee==0.0)
	{ 
	    Footzee = kikr;  // 
    }
	 
    s = sqrt(t)+ sqr(Footzee);
	if(VAR(VVAR_inv)<0.0)
	{
	    r = -1.0 / (sqrt(t) * (t + fabs(VAR(VVAR_inv)))); 
	    u = -1.0 / (sqrt(s) * (s + fabs(VAR(VVAR_inv)))); 
	}
	else
	{
	    r = 1.0 / (sqrt(t) * (t + VAR(VVAR_inv))); 
	    u = 1.0 / (sqrt(s) * (s + VAR(VVAR_inv))); 
	}
	FPx += VVAR*FTx*r;
	FPy += VVAR*FTy*r;
	if(fabs(VVAR)<=1.0)
	{
	    smooth = 1.0 - VVAR;
	}
	else
	{
	    smooth = 0.0;
	}
	FPz = FPz*smooth+VVAR*(Foopzee+Footzee*u);	

    return TRUE;
}

