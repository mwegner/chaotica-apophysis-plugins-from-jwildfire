#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: apocarpet_js

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ApocarpetFunc.java

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

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "apocarpet_js_"
#include "plugin.h"

APO_PLUGIN("apocarpet_js");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // Apolonian Carpet Reference:
    //	http://paulbourke.net/fractals/kissingcircles/roger17.c

    double x = 0, y = 0;

    double r = 1.0 / (1.0 + sqrt(2.0));

    double denom = FTx * FTx + FTy * FTy;

    int weight = (int) (6.0 * GOODRAND_01());

    switch (weight) {
      case 0:
        x = 2.0 * FTx * FTy / denom;
        y = (FTx * FTx - FTy * FTy) / denom;
        break;
      case 1:
        x = FTx * r - r;
        y = FTy * r - r;
        break;
      case 2:
        x = FTx * r + r;
        y = FTy * r + r;
        break;
      case 3:
        x = FTx * r + r;
        y = FTy * r - r;
        break;
      case 4:
        x = FTx * r - r;
        y = FTy * r + r;
        break;
      case 5:
        x = (FTx * FTx - FTy * FTy) / denom;
        y = 2.0 * FTx * FTy / denom;
        break;
    }

    FPx += x * VVAR;
    FPy += y * VVAR;
    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }

    //			    TC = fmod(fabs( (sqr(FPx) + sqr(FPy ))), 1.0);


    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.base.mathlib.MathLib;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class ApocarpetFunc extends SimpleVariationFunc {
// 
//   /**
//    * Roger Bagula Function
//    *
//    * @author Jesus Sosa
//    * @date November 4, 2017
//    * based on a work of:
//    * http://paulbourke.net/fractals/kissingcircles/roger17.c
//    */
// 
//   private static final long serialVersionUID = 1L;
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // Apolonian Carpet Reference:
//     //	http://paulbourke.net/fractals/kissingcircles/roger17.c
// 
//     double x = 0, y = 0;
// 
//     double r = 1.0 / (1.0 + MathLib.sqrt(2.0));
// 
//     double denom = pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y;
// 
//     int weight = (int) (6.0 * pContext.random());
// 
//     switch (weight) {
//       case 0:
//         x = 2.0 * pAffineTP.x * pAffineTP.y / denom;
//         y = (pAffineTP.x * pAffineTP.x - pAffineTP.y * pAffineTP.y) / denom;
//         break;
//       case 1:
//         x = pAffineTP.x * r - r;
//         y = pAffineTP.y * r - r;
//         break;
//       case 2:
//         x = pAffineTP.x * r + r;
//         y = pAffineTP.y * r + r;
//         break;
//       case 3:
//         x = pAffineTP.x * r + r;
//         y = pAffineTP.y * r - r;
//         break;
//       case 4:
//         x = pAffineTP.x * r - r;
//         y = pAffineTP.y * r + r;
//         break;
//       case 5:
//         x = (pAffineTP.x * pAffineTP.x - pAffineTP.y * pAffineTP.y) / denom;
//         y = 2.0 * pAffineTP.x * pAffineTP.y / denom;
//         break;
//     }
// 
//     pVarTP.x += x * pAmount;
//     pVarTP.y += y * pAmount;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
// 
//     //			    pVarTP.color = fmod(fabs( (sqr(pVarTP.x) + sqr(pVarTP.y ))), 1.0);
//   }
// 
//   public String getName() {
//     return "apocarpet_js";
//   }
// }
