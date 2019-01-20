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
    int filled;

} Variables;

#define APO_VARIABLE_PREFIX "cannabiscurve_wf_"
#include "plugin.h"

APO_PLUGIN("cannabiscurve_wf");
APO_VARIABLES(
	VAR_INTEGER(filled, 1),
);

int PluginVarPrepare(Variation* vp)
{
    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double a = atan2(FTx, FTy);

    // cannabis curve (http://mathworld.wolfram.com/CannabisCurve.html)
    double r = (1 + 9.0 / 10.0 * cos(8.0 * a)) * (1 + 1.0 / 10.0 * cos(24.0 * a)) * (9.0 / 10.0 + 1.0 / 10.0 * cos(200.0 * a)) * (1.0 + sin(a));
    a += M_PI / 2.0;

    if (VAR(filled) == 1) {
        r *= random01();
    }

    double nx = sin(a) * r;
    double ny = cos(a) * r;

    FPx += VVAR * nx;
    FPy += VVAR * ny;
    FPz += VVAR * FTz;
   
    return TRUE;
}
