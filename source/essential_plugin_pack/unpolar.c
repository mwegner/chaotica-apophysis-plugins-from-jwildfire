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

// Must define this structure before we include apoplugin.h
typedef struct
{
	double unpolar_vvar;
	double unpolar_vvar_2;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("unpolar");


// Define the Variables
APO_VARIABLES(
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
	VAR(unpolar_vvar) = VVAR / M_PI;
	VAR(unpolar_vvar_2) = VAR(unpolar_vvar) * 0.5;
    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double r = exp(FTy);
    double c, s;
    fsincos(FTx, &s, &c);
    
	FPy += VAR(unpolar_vvar_2) * r * c;
	FPx += VAR(unpolar_vvar_2) * r * s;

    return TRUE;
}
