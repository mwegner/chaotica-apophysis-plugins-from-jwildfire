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
	double polar2_vvar;
	double polar2_vvar_2;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("polar2");


// Define the Variables
APO_VARIABLES(
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
	VAR(polar2_vvar) = VVAR / M_PI;
	VAR(polar2_vvar_2) = VAR(polar2_vvar) * 0.5;
    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
	FPy += VAR(polar2_vvar_2) * log(FTx*FTx + FTy*FTy);
	FPx += VAR(polar2_vvar) * atan2(FTx, FTy);

    return TRUE;
}
