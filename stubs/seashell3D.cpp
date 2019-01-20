#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: seashell3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/SeaShell3DFunc.java

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
	double _a = 2.0;
	double _b = 6.0;
	double _c = 0.0;
	int _n = 5;

} Variables;

#define APO_VARIABLE_PREFIX "seashell3D_"
#include "plugin.h"

APO_PLUGIN("seashell3D");
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
// import org.jwildfire.base.mathlib.MathLib;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.cos;
// import static org.jwildfire.base.mathlib.MathLib.sin;
// 
// public class SeaShell3DFunc extends VariationFunc {
//   /**
//    * Sea Shell
//    *
//    * @author Jesus Sosa
//    * @date February 1, 2018
//    * based on a work of:
//    * http://paulbourke.net/geometry/shell/
//    * parameters
//    * n: number of Spirals
//    * a: final Shell Radius
//    * b: height
//    * c: inner shell radius
//    */
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_A = "final radius";
//   private static final String PARAM_B = "height";
//   private static final String PARAM_C = "inner radius";
//   private static final String PARAM_N = "nSpirals";
// 
//   private static final String[] paramNames = {PARAM_A, PARAM_B, PARAM_C, PARAM_N};
// 
//   double a = 2.0;
//   double b = 6.0;
//   double c = 0.0;
//   int n = 5;
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /**
//      * Sea Shell
//      * Reference
//      * http://paulbourke.net/geometry/shell/
//      * parameters
//      * n: number of Spirals
//      * a: final Shell Radius
//      * b: height
//      * c: inner shell radius
//      */
//     double t;
//     double s;
//     t = MathLib.M_2PI * Math.random();
//     s = MathLib.M_2PI * Math.random();
// 
//     double x = a * (1 - t / MathLib.M_2PI) * cos(n * t) * (1.0 + cos(s)) + c * cos(n * t);
//     double y = a * (1 - t / MathLib.M_2PI) * sin(n * t) * (1.0 + cos(s)) + c * sin(n * t);
//     double z = b * t / MathLib.M_2PI + a * (1 - t / MathLib.M_2PI) * sin(s);
// 
//     pVarTP.x = x * pAmount;
//     pVarTP.y = y * pAmount;
//     pVarTP.z = z * pAmount;
// 
// 
//   }
// 
//   public String getName() {
//     return "seashell3D";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   public Object[] getParameterValues() {
//     return new Object[]{a, b, c, n};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_A)) {
//       a = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_B)) {
//       b = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_C)) {
//       c = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_N)) {
//       n = (int) pValue;
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// }
// 
