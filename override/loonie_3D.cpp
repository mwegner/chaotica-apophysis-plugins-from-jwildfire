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
    3D mod by
	Larry Berlin,   September 2009
	http://apophysisrevealed.com
*/

// Must define this structure before we include apoplugin.h
typedef struct
{
	double sqrvvar;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("loonie_3D");

// Define the Variables
APO_VARIABLES(
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
	VAR(sqrvvar) = VVAR * VVAR;

    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double rmod = random01() * 0.5 + 0.125;
	double efTez = FTz;
	double kikr;
	kikr = atan2(FTy,FTx);
	
	if (efTez==0.0)
	{
	    efTez = kikr;
	}
	
	double r2 = sqr(FTx) + sqr(FTy) + sqr(efTez);    // added the z element

	if (r2 < VAR(sqrvvar))
	{
		double r = VVAR * sqrt(VAR(sqrvvar) / r2 - 1.0);
		FPx += r * FTx;
		FPy += r * FTy;
		FPz += r * efTez * 0.5;             
	}
	else
	{
		FPx += VVAR * FTx;
		FPy += VVAR * FTy;
		FPz += VVAR * efTez * 0.5;
	}

    return TRUE;
}
