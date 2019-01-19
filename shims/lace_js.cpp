/*
    Apophysis Plugin: lace_js

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/LaceFunc.java

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

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "lace_js_"
#include "plugin.h"

APO_PLUGIN("lace_js");
APO_VARIABLES(

    { "WARNING_this_plugin_does_nothing", INTEGER, OFFSET(___warning), 0, 1, 0 },
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
// import org.jwildfire.base.mathlib.MathLib;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.cos;
// import static org.jwildfire.base.mathlib.MathLib.sin;
// 
// public class LaceFunc extends SimpleVariationFunc {
// 
//   /**
//    * Lace variation
//    *
//    * @author Jesus Sosa
//    * @date November 4, 2017
//    * based on a work of:
//    * http://paulbourke.net/fractals/lace/lace.c
//    */
// 
//   private static final long serialVersionUID = 1L;
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // Lace variation Reference:
//     //	http://paulbourke.net/fractals/lace/lace.c
// 
//     double x = 0.5, y = 0.75;
// 
//     double w = 0.0;
//     double r = 2.0;
// 
//     double r0 = MathLib.sqrt(pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y);
//     double weight = pContext.random();
// 
//     if (weight > 0.75) {
//       w = MathLib.atan2(pAffineTP.y, pAffineTP.x - 1.0);
//       y = -r0 * cos(w) / r + 1.0;
//       x = -r0 * sin(w) / r;
//     } else if (weight > 0.50) {
//       w = MathLib.atan2(pAffineTP.y - MathLib.sqrt(3.0) / 2.0, pAffineTP.x + 0.5);
//       y = -r0 * cos(w) / r - 0.5;
//       x = -r0 * sin(w) / r + MathLib.sqrt(3.0) / 2.0;
//     } else if (weight > 0.25) {
//       w = MathLib.atan2(pAffineTP.y + MathLib.sqrt(3.0) / 2.0, pAffineTP.x + 0.5);
//       y = -r0 * cos(w) / r - 0.5;
//       x = -r0 * sin(w) / r - MathLib.sqrt(3.0) / 2.0;
//     } else {
//       w = MathLib.atan2(pAffineTP.y, pAffineTP.x);
//       y = -r0 * cos(w) / r;
//       x = -r0 * sin(w) / r;
//     }
// 
//     pVarTP.x += x * pAmount;
//     pVarTP.y += y * pAmount;
// 
//     //	    pVarTP.color = fmod(fabs( (sqr(pVarTP.x) + sqr(pVarTP.y ))), 1.0);
//   }
// 
//   public String getName() {
//     return "lace_js";
//   }
// }
