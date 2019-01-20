#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: curliecue2

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CurliecueFunc2.java

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
	double _s = 0.02;
	int _seed = 1000;
	double _x0 = 0.0;
	double _y0 = 0.0;
	double _x1;
	double _y1;
	double _theta;
	double _phi;

} Variables;

#define APO_VARIABLE_PREFIX "curliecue2_"
#include "plugin.h"

APO_PLUGIN("curliecue2");
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
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import java.util.Random;
// 
// public class CurliecueFunc2 extends VariationFunc {
// 
//   /*
//    * Variation : curliecue2
//    * Autor: Jesus Sosa
//    * Date: August 10, 2018
//    * Reference https://oolong.co.uk/curlicue.htm
//    */
// 
//   private static final long serialVersionUID = 1L;
//   private static final String PARAM_SEED = "seed";
// 
//   private static final String[] paramNames = {PARAM_SEED};
// 
//   double s = 0.02;
//   int seed = 1000;
//   double x0 = 0.0, y0 = 0.0, x1, y1;
//   double theta = 0, phi = 0;
//   Random randomize = new Random((long) seed);
// 
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     x1 = x0 + 0.001 * Math.cos(phi);
//     y1 = y0 + 0.001 * Math.sin(phi);
//     x0 = x1;
//     y0 = y1;
//     phi = (theta + phi) % (2 * Math.PI);
//     theta = (theta + 2 * Math.PI * s) % (2 * Math.PI);
//     pVarTP.x += pAmount * x0;
//     pVarTP.y += pAmount * y0;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
// 
//     randomize = new Random((long) seed);
//     x0 = 0.0;
//     y0 = 0.0;
//     theta = 0;
//     phi = 0;
//     s = randomize.nextDouble();
//   }
// 
//   public String getName() {
//     return "curliecue2";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   public Object[] getParameterValues() {
//     return new Object[]{seed};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_SEED)) {
//       seed = (int) pValue;
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// }
// 
