#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: cannabiscurve_wf

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CannabisCurveWFFunc.java

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

typedef struct
{
    double freq;
    double weight;
    double sym;
    double scale;

} Variables;

#define APO_VARIABLE_PREFIX "auger_"
#include "plugin.h"

APO_PLUGIN("auger");
APO_VARIABLES(
	VAR_REAL(freq, 1.0),
	VAR_REAL(weight, 0.5),
	VAR_REAL(sym, 0.1),
	VAR_REAL(scale, 0.9),
);

int PluginVarPrepare(Variation* vp)
{
    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // Auger, by Xyrus02
    double s = sin(VAR(freq) * FTx);
    double t = sin(VAR(freq) * FTy);
    double dy = FTy + VAR(weight) * (VAR(scale) * s * 0.5 + fabs(FTy) * s);
    double dx = FTx + VAR(weight) * (VAR(scale) * t * 0.5 + fabs(FTx) * t);

    FPx += VVAR * (FTx + VAR(sym) * (dx - FTx));
    FPy += VVAR * dy;
    FPz += VVAR * FTz;
   
    return TRUE;
}
