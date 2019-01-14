/*
    Apophysis Plugin: squircular

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/SquircularFunc.java

    Automatically converted by @mwegner

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



#include "datahelpers.h"



typedef struct
{

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "squircular_"
#include "plugin.h"

APO_PLUGIN("squircular");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{


    double u = FTx;
    double v = FTy;
    double r = u * u + v * v;
    double rs = sqrt(r);
    double xs = u > 0 ? 1.0 : -1.0;

    r = sqrt(VVAR * VVAR * r - 4 * u * u * v * v);
    r = sqrt(1 + u * u / (v * v) - rs / (VVAR * v * v) * r);
    r = r / sqrt(2);

    FPx += xs * r;
    FPy += v / u * r;

    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }


    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class SquircularFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// 
// 
//     double u = pAffineTP.x;
//     double v = pAffineTP.y;
//     double r = u * u + v * v;
//     double rs = Math.sqrt(r);
//     double xs = u > 0 ? 1.0 : -1.0;
// 
//     r = Math.sqrt(pAmount * pAmount * r - 4 * u * u * v * v);
//     r = Math.sqrt(1 + u * u / (v * v) - rs / (pAmount * v * v) * r);
//     r = r / Math.sqrt(2);
// 
//     pVarTP.x += xs * r;
//     pVarTP.y += v / u * r;
// 
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "squircular";
//   }
// 
// 
// }
// 
