#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: hadamard_js

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/HadamardFunc.java

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

} Variables;

#define APO_VARIABLE_PREFIX "hadamard_js_"
#include "plugin.h"

APO_PLUGIN("hadamard_js");
APO_VARIABLES(

);


int PluginVarPrepare(Variation* vp)
{
    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class HadamardFunc extends SimpleVariationFunc {
// 
//   /**
//    * Hadamard IFS
//    *
//    * @author Jesus Sosa
//    * @date November 4, 2017
//    * based on a work of:
//    * http://paulbourke.net/fractals/pascaltriangle/roger9.c
//    */
// 
//   private static final long serialVersionUID = 1L;
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     //               Hadamard IFS Reference:
//     //				 http://paulbourke.net/fractals/pascaltriangle/roger18.c
// 
//     double x, y;
// 
//     if (pContext.random() < 0.333) {
//       x = pAffineTP.x / 2.0;
//       y = pAffineTP.y / 2.0;
//     } else if (pContext.random() < 0.666) {
//       x = pAffineTP.y / 2.0;
//       y = -pAffineTP.x / 2.0 - 0.5;
//     } else {
//       x = -pAffineTP.y / 2.0 - 0.5;
//       y = pAffineTP.x / 2.0;
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
//     return "hadamard_js";
//   }
// }
