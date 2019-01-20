#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: invtree_js

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/InvTreeFunc.java

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

} Variables;

#define APO_VARIABLE_PREFIX "invtree_js_"
#include "plugin.h"

APO_PLUGIN("invtree_js");
APO_VARIABLES(


);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    //               Inverse Tree IFS Reference:
    //				 http://paulbourke.net/fractals/trifraction2/

    double x, y;

    if (GOODRAND_01() < 0.333) {
      x = FTx / 2.0;
      y = FTy / 2.0;
    } else if (GOODRAND_01() < 0.666) {
      x = 1.0 / (FTx + 1);
      y = FTy / (FTy + 1.0);
    } else {
      x = FTx / (FTx + 1);
      y = 1.0 / (FTy + 1.0);
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
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class InvTreeFunc extends SimpleVariationFunc {
// 
//   /**
//    * Inverse Tree IFS
//    *
//    * @author Jesus Sosa
//    * @date November 4, 2017
//    * based on a work of:
//    * http://paulbourke.net/fractals/trifraction2/
//    */
// 
//   private static final long serialVersionUID = 1L;
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     //               Inverse Tree IFS Reference:
//     //				 http://paulbourke.net/fractals/trifraction2/
// 
//     double x, y;
// 
//     if (pContext.random() < 0.333) {
//       x = pAffineTP.x / 2.0;
//       y = pAffineTP.y / 2.0;
//     } else if (pContext.random() < 0.666) {
//       x = 1.0 / (pAffineTP.x + 1);
//       y = pAffineTP.y / (pAffineTP.y + 1.0);
//     } else {
//       x = pAffineTP.x / (pAffineTP.x + 1);
//       y = 1.0 / (pAffineTP.y + 1.0);
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
//     return "invtree_js";
//   }
// 
// }
