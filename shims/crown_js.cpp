/*
    Apophysis Plugin: crown_js

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CrownFunc.java

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
	double _a = 5;
	double _b; // Math.log(2) / Math.log(3)

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "crown_js_"
#include "plugin.h"

APO_PLUGIN("crown_js");
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
// import org.jwildfire.base.mathlib.Complex;
// import org.jwildfire.base.mathlib.MathLib;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class CrownFunc extends VariationFunc {
// 
//   /**
//    * Roger Bagula Function
//    *
//    * @author Jesus Sosa
//    * @date November 4, 2017
//    * based on a work of:
//    * http://paulbourke.net/fractals/crown/
//    */
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_A = "a";
//   private static final String PARAM_B = "b";
// 
//   private static final String[] paramNames = {PARAM_A, PARAM_B};
// 
//   double a = 5, b = Math.log(2) / Math.log(3);
// 
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
// 
//   }
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // Roger Bagula  Reference:
//     //	http://paulbourke.net/fractals/crown/
// 
//     double x, y, z;
// 
//     double t = (-M_PI + 2.0 * M_PI * pContext.random());
// 
//     Complex wt = new Complex(0.0, 0.0);
// 
//     for (int k = 1; k < 15; k++) {
//       double denom = MathLib.pow(a, b * k);
//       double th = MathLib.pow(a, (double) k) * MathLib.pow(-1.0, (double) k) * t;
//       wt.Add(new Complex(sin(th) / denom, cos(th) / denom));
//     }
//     x = wt.re;
//     y = wt.im;
//     z = MathLib.pow(wt.Mag2(), 2);
// 
//     pVarTP.x += x * pAmount;
//     pVarTP.y += y * pAmount;
//     pVarTP.z += z * pAmount;
// 
//     pVarTP.color = fmod(fabs((sqr(pVarTP.x) + sqr(pVarTP.y))), 1.0);
//   }
// 
//   public String getName() {
//     return "crown_js";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   public Object[] getParameterValues() {
//     return new Object[]{a, b};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_A)) {
//       a = pValue;
// 
//     } else if (pName.equalsIgnoreCase(PARAM_B)) {
//       b = pValue;
// 
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// }
