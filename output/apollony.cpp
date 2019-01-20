#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: apollony

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ApollonyFunc.java

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

#define APO_VARIABLE_PREFIX "apollony_"
#include "plugin.h"

APO_PLUGIN("apollony");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
//               Apollony IFS Reference:
//				 http://paulbourke.net/fractals/apollony/apollony.c

    double x, y, a0, b0, f1x, f1y;
    double r = sqrt(3.0);

    a0 = 3.0 * (1.0 + r - FTx) / (pow(1.0 + r - FTx, 2.0) + FTy * FTy) - (1.0 + r) / (2.0 + r);
    b0 = 3.0 * FTy / (pow(1.0 + r - FTx, 2.0) + FTy * FTy);
    f1x = a0 / (a0 * a0 + b0 * b0);
    f1y = -b0 / (a0 * a0 + b0 * b0);

    int w = (int) (4.0 * GOODRAND_01());

    if ((w % 3) == 0) {
      x = a0;
      y = b0;
    } else if ((w % 3) == 1) {
      x = -f1x / 2.0 - f1y * r / 2.0;
      y = f1x * r / 2.0 - f1y / 2.0;
    } else {
      x = -f1x / 2.0 + f1y * r / 2.0;
      y = -f1x * r / 2.0 - f1y / 2.0;
    }

    FPx += x * VVAR;
    FPy += y * VVAR;

    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }


    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// 
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class ApollonyFunc extends SimpleVariationFunc {
// 
// 
//   /**
//    * Apollony IFS
//    *
//    * @author Jesus Sosa
//    * @date January 22, 2018
//    * based on a work of:
//    * http://paulbourke.net/fractals/apollony/apollony.c
//    */
// 
// 
//   private static final long serialVersionUID = 1L;
// 
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// //               Apollony IFS Reference:
// //				 http://paulbourke.net/fractals/apollony/apollony.c
// 
//     double x, y, a0, b0, f1x, f1y;
//     double r = Math.sqrt(3.0);
// 
//     a0 = 3.0 * (1.0 + r - pAffineTP.x) / (Math.pow(1.0 + r - pAffineTP.x, 2.0) + pAffineTP.y * pAffineTP.y) - (1.0 + r) / (2.0 + r);
//     b0 = 3.0 * pAffineTP.y / (Math.pow(1.0 + r - pAffineTP.x, 2.0) + pAffineTP.y * pAffineTP.y);
//     f1x = a0 / (a0 * a0 + b0 * b0);
//     f1y = -b0 / (a0 * a0 + b0 * b0);
// 
//     int w = (int) (4.0 * Math.random());
// 
//     if ((w % 3) == 0) {
//       x = a0;
//       y = b0;
//     } else if ((w % 3) == 1) {
//       x = -f1x / 2.0 - f1y * r / 2.0;
//       y = f1x * r / 2.0 - f1y / 2.0;
//     } else {
//       x = -f1x / 2.0 + f1y * r / 2.0;
//       y = -f1x * r / 2.0 - f1y / 2.0;
//     }
// 
//     pVarTP.x += x * pAmount;
//     pVarTP.y += y * pAmount;
// 
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   public String getName() {
//     return "apollony";
//   }
// }
