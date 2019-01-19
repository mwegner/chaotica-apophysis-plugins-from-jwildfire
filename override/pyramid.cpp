/*
    Apophysis Plugin: pyramid

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PyramidFunc.java

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
   
} Variables;

#include "plugin.h"

APO_PLUGIN("pyramid");
APO_VARIABLES(

);

int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
	 // pyramid by Zueuk (transcribed into jwf by Dark)
    double x = FTx;
    x = x * x * x;
    double y = FTy;
    y = y * y * y;
    double z = FTz;
    z = fabs(z * z * z);

    double r = VVAR / (fabs(x) + fabs(y) + z + 0.000000001);

    FPx += x * r;
    FPy += y * r;
    FPz += z * r;

    return TRUE;
}
