/*
    Apophysis Plugin: threepoint_js

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ThreePointIFSFunc.java

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

#define APO_VARIABLE_PREFIX "threepoint_js_"
#include "plugin.h"

APO_PLUGIN("threepoint_js");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
//               based on a work of Roger Bagula:
//				 https://plus.google.com/110803890168343196795/posts/9P2gTkrmQFr

    double x, y;

    if (GOODRAND_01() < 0.333) {
      x = FTx / 2.0 - FTy / 2.0 + 0.5;
      y = -FTx / 2.0 - FTy / 2.0 + 0.5;
    } else if (GOODRAND_01() < 0.666) {
      x = FTy;
      y = FTx;
    } else {
      x = -FTy / 2.0 + 0.5;
      y = -FTx / 2.0 + 0.5;
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
// public class ThreePointIFSFunc extends SimpleVariationFunc {
// 
// 
//   /**
//    * Three Point Pivot/Overlap IFS Triangle
//    *
//    * @author Jesus Sosa
//    * @date November 4, 2017
//    * based on a work of Roger Bagula:
//    * https://plus.google.com/110803890168343196795/posts/9P2gTkrmQFr
//    */
// 
// 
//   private static final long serialVersionUID = 1L;
// 
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// //               based on a work of Roger Bagula:
// //				 https://plus.google.com/110803890168343196795/posts/9P2gTkrmQFr
// 
//     double x, y;
// 
//     if (Math.random() < 0.333) {
//       x = pAffineTP.x / 2.0 - pAffineTP.y / 2.0 + 0.5;
//       y = -pAffineTP.x / 2.0 - pAffineTP.y / 2.0 + 0.5;
//     } else if (Math.random() < 0.666) {
//       x = pAffineTP.y;
//       y = pAffineTP.x;
//     } else {
//       x = -pAffineTP.y / 2.0 + 0.5;
//       y = -pAffineTP.x / 2.0 + 0.5;
//     }
// 
//     pVarTP.x += x * pAmount;
//     pVarTP.y += y * pAmount;
// 
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
// 
//   }
// 
//   public String getName() {
//     return "threepoint_js";
//   }
// }
