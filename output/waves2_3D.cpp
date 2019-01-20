#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin
    Copyright (C) 2008 Joel Faber

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
    This 3D modification written by
	Larry Berlin
	September 2009
	http://apophysisrevealed.com
*/

// Must define this structure before we include apoplugin.h
typedef struct
{
    double waves2_3D_freq;
    double waves2_3D_scale;
	double avgxy;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("waves2_3D");

// Define the Variables
APO_VARIABLES(
    VAR_REAL(waves2_3D_freq, 2.0),
    VAR_REAL(waves2_3D_scale, 1.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(avgxy) = (FTx + FTy)/2.0;
	return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    FPx += VVAR * (FTx + VAR(waves2_3D_scale) * sin(FTy * VAR(waves2_3D_freq)));
    FPy += VVAR * (FTy + VAR(waves2_3D_scale) * sin(FTx * VAR(waves2_3D_freq)));
    FPz += VVAR * (FTz + VAR(waves2_3D_scale) * sin(VAR(avgxy) * VAR(waves2_3D_freq)));  //Averages the XY to get Z
	              //  Cool results, very successful 3D effect
    return TRUE;
}
