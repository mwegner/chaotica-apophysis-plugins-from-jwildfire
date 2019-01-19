/*
    Apophysis Plugin: woggle_js

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/WoggleFunc.java

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
	int _m = 2;
	double _a[25];
	double _b[25];

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "woggle_js_"
#include "plugin.h"

APO_PLUGIN("woggle_js");
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
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class WoggleFunc extends VariationFunc {
// 
//   /**
//    * Woogle
//    *
//    * @author Jesus Sosa
//    * @date November 4, 2017
//    * based on a work of:
//    * http://paulbourke.net/fractals/woggle/roger14.c
//    */
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_M = "m";
// 
//   int m = 2;
//   private static final String[] paramNames = {PARAM_M};
// 
//   double[] a = new double[25];
//   double[] b = new double[25];
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     //       Woggle Reference:
//     //		 http://paulbourke.net/fractals/woggle/roger14.c
// 
//     double x, y;
// 
//     double r = MathLib.sqrt(1.25) * MathLib.sqrt((double) m);
//     int c = (int) ((double) m * pContext.random());
//     double ra = 1.0 / (MathLib.sqrt(3.0) * MathLib.sqrt(pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y));
// 
//     if (c % 2 == 0) {
//       x = -pAffineTP.x / r + ra * pAffineTP.y / r + a[c];
//       y = -ra * pAffineTP.x / r - pAffineTP.y / r + b[c];
//     } else {
//       x = pAffineTP.x / r + ra * pAffineTP.y / r + a[c];
//       y = -ra * pAffineTP.x / r + pAffineTP.y / r + b[c];
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
//     return "woggle_js";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   public Object[] getParameterValues() {
//     return new Object[]{m};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_M)) {
//       m = (int) pValue;
//       if (m < 2)
//         m = 2;
//       if (m > 12)
//         m = 12;
// 
//       for (int i = 0; i < m; i++) {
//         a[i] = cos(2 * M_PI * (double) i / (double) m);
//         b[i] = sin(2 * M_PI * (double) i / (double) m);
//       }
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// }
