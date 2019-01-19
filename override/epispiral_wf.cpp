/*
    Apophysis Plugin: epispiral_wf

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/EpispiralWFFunc.java

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
    double waves;
} Variables;

#define APO_VARIABLE_PREFIX "epispiral_wf_"
#include "plugin.h"

APO_PLUGIN("epispiral_wf");
APO_VARIABLES(
	VAR_REAL(waves, 4.0),
);

int PluginVarPrepare(Variation* vp)
{
    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
	double a = atan2(FTx, FTy);
    double r = sqrt(FTx * FTx + FTy * FTy);
    double d = cos(VAR(waves) * a);
    if (d == 0) {
      return TRUE;
    }
    r = 0.5 / d;
    double nx = sin(a) * r;
    double ny = cos(a) * r;

    FPx += VVAR * nx;
    FPy += VVAR * ny;
    FPz += VVAR * FTz;
   
    return TRUE;
}
