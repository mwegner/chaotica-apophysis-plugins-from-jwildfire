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
	double v;

} Variables;

#define APO_VARIABLE_PREFIX "spherical3D_"
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("spherical3D");

// Define the Variables
APO_VARIABLES(
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
	double T, r;
	
    T = sqr(FTx) + sqr(FTy) + sqr(FTz) + EPS;
    r = VVAR / T;

	FPx += FTx * r;
	FPy += FTy * r;
	FPz += FTz * r;

    return TRUE;
}
