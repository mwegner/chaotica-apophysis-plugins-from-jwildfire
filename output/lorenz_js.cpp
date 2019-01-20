#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: lorenz_js

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/LorenzFunc.java

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
	double _a = 10.0;
	double _b = 28.0;
	double _c = 1.66;
	double _h = 0.00001;
	double centerx;
	double centery;
	double scale;
	double _bdcs;

} Variables;

#define APO_VARIABLE_PREFIX "lorenz_js_"
#include "plugin.h"

APO_PLUGIN("lorenz_js");
APO_VARIABLES(
	VAR_REAL(centerx, 0.0),
	VAR_REAL(centery, 0.0),
	VAR_REAL(scale, 1000.0)

);



int PluginVarPrepare(Variation* vp)
{
   VAR(_a) = 10.0;
   VAR(_b) = 28.0;
   VAR(_c) = 1.66;
   VAR(_h) = 0.00001;
    VAR(_bdcs) = 1.0 / (VAR(scale) == 0.0 ? 10E-6 : VAR(scale));

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // Reference:
    //		  http://paulbourke.net/fractals/lorenz/
    //		  xn+1 = xn + VAR(_h)*VAR(_a)*(yn-xn)s
    //		  yn+1 = yn + VAR(_h)*(xn*(VAR(_b)-zn)-yn)
    //        zn+1 = zn + VAR(_h)*(xn*yn-VAR(_c)*zn)

    double x = FTx + VAR(_h) * VAR(_a) * (FTy - FTx);
    double y = FTy + VAR(_h) * (FTx * (VAR(_b) - FTz) - FTy);
    double z = FTz + VAR(_h) * (FTx * FTy - VAR(_c) * FTz);

    FPx += x * VVAR;
    FPy += y * VVAR;
    FPz += z * VVAR;

    TC = fmod(fabs(VAR(_bdcs) * (sqr(FPx + VAR(centerx)) + sqr(FPy + VAR(centery)))), 1.0);
    //	    TC = fmod(fabs( (sqr(FPx) + sqr(FPy ))), 1.0);



    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class LorenzFunc extends VariationFunc {
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_A = "a";
//   private static final String PARAM_B = "b";
//   private static final String PARAM_C = "c";
//   private static final String PARAM_H = "h";
//   private static final String PARAM_CENTERX = "centerx";
//   private static final String PARAM_CENTERY = "centery";
//   private static final String PARAM_SCALE = "scale";
// 
//   private static final String[] paramNames = {PARAM_A, PARAM_B, PARAM_C, PARAM_H, PARAM_CENTERX, PARAM_CENTERY, PARAM_SCALE};
// 
//   double a = 10.0;
//   double b = 28.0;
//   double c = 1.66;
//   double h = 0.00001;
// 
//   private double centerx = 0.0;
//   private double centery = 0.0;
//   private double scale = 1000.0;
//   private double bdcs;
// 
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     bdcs = 1.0 / (scale == 0.0 ? 10E-6 : scale);
//   }
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // Reference:
//     //		  http://paulbourke.net/fractals/lorenz/
//     //		  xn+1 = xn + h*a*(yn-xn)s
//     //		  yn+1 = yn + h*(xn*(b-zn)-yn)
//     //        zn+1 = zn + h*(xn*yn-c*zn)
// 
//     double x = pAffineTP.x + h * a * (pAffineTP.y - pAffineTP.x);
//     double y = pAffineTP.y + h * (pAffineTP.x * (b - pAffineTP.z) - pAffineTP.y);
//     double z = pAffineTP.z + h * (pAffineTP.x * pAffineTP.y - c * pAffineTP.z);
// 
//     pVarTP.x += x * pAmount;
//     pVarTP.y += y * pAmount;
//     pVarTP.z += z * pAmount;
// 
//     pVarTP.color = fmod(fabs(bdcs * (sqr(pVarTP.x + centerx) + sqr(pVarTP.y + centery))), 1.0);
//     //	    pVarTP.color = fmod(fabs( (sqr(pVarTP.x) + sqr(pVarTP.y ))), 1.0);
// 
//   }
// 
//   public String getName() {
//     return "lorenz_js";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   public Object[] getParameterValues() {
//     return new Object[]{a, b, c, h, centerx, centery, scale};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_A)) {
//       a = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_B)) {
//       b = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_C)) {
//       c = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_H)) {
//       h = pValue;
//     } else if (PARAM_CENTERX.equalsIgnoreCase(pName))
//       centerx = pValue;
//     else if (PARAM_CENTERY.equalsIgnoreCase(pName))
//       centery = pValue;
//     else if (PARAM_SCALE.equalsIgnoreCase(pName))
//       scale = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// }
// 
