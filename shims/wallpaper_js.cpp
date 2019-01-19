/*
    Apophysis Plugin: wallpaper_js

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/WallPaperFunc.java

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
	double _a = 1.156;
	double _b = -0.28;
	double _c = 21.288;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "wallpaper_js_"
#include "plugin.h"

APO_PLUGIN("wallpaper_js");
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
// import org.jwildfire.create.tina.base.Flame;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class WallPaperFunc extends VariationFunc {
// 
//   /**
//    * WallPaper
//    *
//    * @author Jesus Sosa
//    * @date November 4, 2017
//    * based on a work of:
//    * http://paulbourke.net/fractals/wallpaper/
//    */
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_A = "a";
//   private static final String PARAM_B = "b";
//   private static final String PARAM_C = "c";
// 
//   private static final String[] paramNames = {PARAM_A, PARAM_B, PARAM_C};
// 
//   double a = 1.156, b = -0.28, c = 21.288;
// 
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     Flame flame = pContext.getFlameRenderer().getFlame();
//     flame.setBrightness(300.0);
//   }
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // WallPaper  Reference:
//     //	http://paulbourke.net/fractals/wallpaper/
//     if (pContext.random() < 0.5) {
//       pVarTP.x += pAffineTP.y - Integer.signum((int) pAffineTP.x) * MathLib.sqrt(Math.abs(b * pAffineTP.x - c));
//       pVarTP.y += a - pAffineTP.x;
//     } else {
//       pVarTP.x = pAffineTP.x;
//       pVarTP.y = pAffineTP.y;
//     }
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   public String getName() {
//     return "wallpaper_js";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   public Object[] getParameterValues() {
//     return new Object[]{a, b, c};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_A)) {
//       a = pValue;
// 
//     } else if (pName.equalsIgnoreCase(PARAM_B)) {
//       b = pValue;
// 
//     } else if (pName.equalsIgnoreCase(PARAM_C)) {
//       c = pValue;
// 
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// }
