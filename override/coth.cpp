/*
    Apophysis Plugin: cothhh

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CothFunc.java

    This program is free software; you can redistribute it ahnd/or modify
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

APO_PLUGIN("coth");
APO_VARIABLES(

);

int PluginVarPrepare(Variation* vp)
{
    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
	/* complex vars by cothe */
    /* exp log sin cos tan sec csc cot sinh cosh tanh sech csch coth */
    //Hyperbolic Cotangent COTH
    double cothsin = sin(2.0 * FTy);
    double cothcos = cos(2.0 * FTy);
    double cothsinh = sinh(2.0 * FTx);
    double cothcosh = cosh(2.0 * FTx);
    double d = (cothcosh - cothcos);
    if (d == 0.0)
      return TRUE;
    double cothden = 1.0 / d;
    FPx += VVAR * cothden * cothsinh;
    FPy += VVAR * cothden * cothsin;
    FPz += VVAR * FTz;

    return TRUE;
}
