/*
    Apophysis Plugin: macmillan

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/MacMillanFunc.java

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
    double a;
    double b;
    double N;
    double startx;
    double starty;

	// not exposed
	double xa, x, y;

} Variables;

#define APO_VARIABLE_PREFIX "macmillan_"
#include "plugin.h"

APO_PLUGIN("macmillan");
APO_VARIABLES(
	VAR_REAL(a, 1.60),
    VAR_REAL(b, 0.40),
    VAR_REAL(N, 1),
    VAR_REAL(startx, 0.1),
    VAR_REAL(starty, 0.1),      
);

int PluginVarPrepare(Variation* vp)
{
	VAR(xa) = VAR(startx);
    VAR(x) = VAR(startx);
    VAR(y) = VAR(starty);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
	VAR(x) = VAR(y);
    VAR(y) = -VAR(xa) + 2 * VAR(a) * ( VAR(y) / (1 + VAR(y) * VAR(y) )) + VAR(b) * VAR(y);
    VAR(xa) = VAR(x);
    VAR(x) = VAR(y);
    VAR(y) = -VAR(xa) + 2 * VAR(a) * ( VAR(y) / (1 + VAR(y) * VAR(y) )) + VAR(b) * VAR(y);

    FPx += VVAR * VAR(x);
    FPy += VVAR * VAR(y);

    TC = fmod(fabs(0.5 * ( (FPx + FPy ) + 1.0)), 1.0);
    VAR(xa) = VAR(x);

    return TRUE;
}
