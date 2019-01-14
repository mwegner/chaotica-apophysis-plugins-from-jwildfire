/*
    Apophysis Plugin: svensson_js

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/SvenssonFunc.java

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
	double _a = 1.4;
	double _b = 1.56;
	double _c = 1.4;
	double _d = -6.56;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "svensson_js_"
#include "plugin.h"

APO_PLUGIN("svensson_js");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
   VAR(_a) = 1.4;
   VAR(_b) = 1.56;
   VAR(_c) = 1.4;
   VAR(_d) = -6.56;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // Reference:
    //				  http://paulbourke.net/fractals/peterdejong/
    //				  xn+1 = VAR(_d)*sin(VAR(_a) xn) - sin(VAR(_b) xn)
    //				  yn+1 = VAR(_c)*cos(VAR(_a) xn) + cos(VAR(_b) yn)

    double x = VAR(_d) * sin(VAR(_a) * FTx) - sin(VAR(_b) * FTy);
    double y = VAR(_c) * cos(VAR(_a) * FTx) + cos(VAR(_b) * FTy);

    FPx = x * VVAR;
    FPy = y * VVAR;
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
// import static org.jwildfire.base.mathlib.MathLib.cos;
// import static org.jwildfire.base.mathlib.MathLib.sin;
// 
// public class SvenssonFunc extends VariationFunc {
// 
//   /**
//    * Jhonny Svensson Attractor
//    *
//    * @author Jesus Sosa
//    * @date November 4, 2017
//    * based on a work of:
//    * http://paulbourke.net/fractals/peterdejong/
//    */
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_A = "a";
//   private static final String PARAM_B = "b";
//   private static final String PARAM_C = "c";
//   private static final String PARAM_D = "d";
// 
//   private static final String[] paramNames = {PARAM_A, PARAM_B, PARAM_C, PARAM_D};
// 
//   double a = 1.4;
//   double b = 1.56;
//   double c = 1.4;
//   double d = -6.56;
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // Reference:
//     //				  http://paulbourke.net/fractals/peterdejong/
//     //				  xn+1 = d*sin(a xn) - sin(b xn)
//     //				  yn+1 = c*cos(a xn) + cos(b yn)
// 
//     double x = d * sin(a * pAffineTP.x) - sin(b * pAffineTP.y);
//     double y = c * cos(a * pAffineTP.x) + cos(b * pAffineTP.y);
// 
//     pVarTP.x = x * pAmount;
//     pVarTP.y = y * pAmount;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
// 
//   }
// 
//   public String getName() {
//     return "svensson_js";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   public Object[] getParameterValues() {
//     return new Object[]{a, b, c, d};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_A)) {
//       a = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_B)) {
//       b = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_C)) {
//       c = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_D)) {
//       d = pValue;
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// }
// 
