/*
    Apophysis Plugin: macmillan

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/MacMillanFunc.java

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
	double _a = 1.60;
	double _b = 0.40;
	double _N = 1;
	double _x0 = 0.1;
	double _y0 = 0.1;
	double _xa;
	double _x;
	double _y;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "macmillan_"
#include "plugin.h"

APO_PLUGIN("macmillan");
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
// 
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class MacMillanFunc extends VariationFunc {
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_A = "a";
//   private static final String PARAM_B = "b";
//   private static final String PARAM_STARTX = "startx";
//   private static final String PARAM_STARTY = "starty";
// 
// 
//   private static final String[] paramNames = {PARAM_A, PARAM_B, PARAM_STARTX, PARAM_STARTY};
// 
//   double a = 1.60;
//   double b = 0.40;
//   double N = 1;
//   double x0 = 0.1;
//   double y0 = 0.1;
// 
//   double xa, x, y;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     xa = x0;
//     y = y0;
//   }
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// 
//     x = y;
//     y = -xa + 2. * a * (y / (1 + y * y)) + b * y;
//     xa = x;
//     x = y;
//     y = -xa + 2 * a * (y / (1 + y * y)) + b * y;
// 
//     pVarTP.x += pAmount * x;
//     pVarTP.y += pAmount * y;
// 
//     // pVarTP.color=MathLib.fmod(MathLib.fabs(0.5 * ( (pVarTP.x + pVarTP.y ) + 1.0)), 1.0);
//     xa = x;
//   }
// 
//   public String getName() {
//     return "macmillan";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   public Object[] getParameterValues() {
//     return new Object[]{a, b, x0, y0};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_A)) {
//       a = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_B)) {
//       b = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_STARTX)) {
//       x0 = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_STARTY)) {
//       y0 = pValue;
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// }
// 
