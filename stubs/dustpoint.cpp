#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: dustpoint

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/DustPointFunc.java

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

#define APO_VARIABLE_PREFIX "dustpoint_"
#include "plugin.h"

APO_PLUGIN("dustpoint");
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
// 
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class DustPointFunc extends SimpleVariationFunc {
// 
// 
//   /**
//    * Three Point Pivot/Overlap IFS Triangle
//    *
//    * @author Jesus Sosa
//    * @date November 4, 2017
//    * based on a work of Roger Bagula:
//    * http://paulbourke.net/fractals/ifs_curved/roger5.c
//    */
// 
// 
//   private static final long serialVersionUID = 1L;
// 
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// //               based on a work of Roger Bagula:
// //				 http://paulbourke.net/fractals/ifs_curved/roger5.c
// 
//     double x, y, p, r;
// 
//     p = (pContext.random() < 0.5) ? 1 : -1;
//     r = Math.sqrt(pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y);
// 
//     double w = pContext.random();
//     if (w < 0.50) {
//       x = pAffineTP.x / r - 1;
//       y = p * pAffineTP.y / r;
//     } else if (w < 0.75) {
//       x = pAffineTP.x / 3.0;
//       y = pAffineTP.y / 3.0;
//     } else {
//       x = pAffineTP.x / 3.0 + 2.0 / 3.0;
//       y = pAffineTP.y / 3.0;
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
//     return "dustpoint";
//   }
// }
