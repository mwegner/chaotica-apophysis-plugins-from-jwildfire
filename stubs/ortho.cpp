#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: ortho

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/OrthoFunc.java

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
	double in;
	double out;

} Variables;

#define APO_VARIABLE_PREFIX "ortho_"
#include "plugin.h"

APO_PLUGIN("ortho");
APO_VARIABLES(
	VAR_REAL(in, 0.0),
	VAR_REAL(out, 0.0)

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
// /*
//   JWildfire - an image and animation processor written in Java 
//   Copyright (C) 1995-2011 Andreas Maschke
// 
//   This is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser 
//   General Public License as published by the Free Software Foundation; either version 2.1 of the 
//   License, or (at your option) any later version.
//  
//   This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
//   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
//   Lesser General Public License for more details.
// 
//   You should have received a copy of the GNU Lesser General Public License along with this software; 
//   if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
//   02110-1301 USA, or see the FSF site: http://www.fsf.org.
// */
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class OrthoFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_IN = "in";
//   private static final String PARAM_OUT = "out";
//   private static final String[] paramNames = {PARAM_IN, PARAM_OUT};
// 
//   private double in = 0.0;
//   private double out = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* ortho by Michael Faber,  http://michaelfaber.deviantart.com/art/The-Lost-Variations-258913970 */
// 
//     double r, a, ta;
//     double xo;
//     double ro;
//     double c, s;
//     double x, y, tc, ts;
//     double theta;
// 
//     r = sqr(pAffineTP.x) + sqr(pAffineTP.y);
// 
//     if (r < 1.0) { // && FTx > 0.0 && FTy > 0.0) 
//       if (pAffineTP.x >= 0.0) {
//         xo = (r + 1.0) / (2.0 * pAffineTP.x);
//         ro = sqrt(sqr(pAffineTP.x - xo) + sqr(pAffineTP.y));
//         theta = atan2(1.0, ro);
//         a = fmod(in * theta + atan2(pAffineTP.y, xo - pAffineTP.x) + theta, 2.0 * theta) - theta;
//         s = sin(a);
//         c = cos(a);
// 
//         pVarTP.x += pAmount * (xo - c * ro);
//         pVarTP.y += pAmount * s * ro;
//       } else {
//         xo = -(r + 1.0) / (2.0 * pAffineTP.x);
//         ro = sqrt(sqr(-pAffineTP.x - xo) + sqr(pAffineTP.y));
//         theta = atan2(1.0, ro);
//         a = fmod(in * theta + atan2(pAffineTP.y, xo + pAffineTP.x) + theta, 2.0 * theta) - theta;
//         s = sin(a);
//         c = cos(a);
// 
//         pVarTP.x -= pAmount * (xo - c * ro);
//         pVarTP.y += pAmount * s * ro;
//       }
//     } else {
//       r = 1.0 / sqrt(r);
//       ta = atan2(pAffineTP.y, pAffineTP.x);
//       ts = sin(ta);
//       tc = cos(ta);
// 
//       x = r * tc;
//       y = r * ts;
// 
//       if (x >= 0.0) {
//         xo = (sqr(x) + sqr(y) + 1.0) / (2.0 * x);
//         ro = sqrt(sqr(x - xo) + sqr(y));
//         theta = atan2(1.0, ro);
//         a = fmod(out * theta + atan2(y, xo - x) + theta, 2.0 * theta) - theta;
//         s = sin(a);
//         c = cos(a);
// 
//         x = (xo - c * ro);
//         y = s * ro;
//         ta = atan2(y, x);
//         ts = sin(ta);
//         tc = cos(ta);
// 
//         r = 1.0 / sqrt(sqr(x) + sqr(y));
// 
//         pVarTP.x += pAmount * r * tc;
//         pVarTP.y += pAmount * r * ts;
//       } else {
//         xo = -(sqr(x) + sqr(y) + 1.0) / (2.0 * x);
//         ro = sqrt(sqr(-x - xo) + sqr(y));
//         theta = atan2(1.0, ro);
//         a = fmod(out * theta + atan2(y, xo + x) + theta, 2.0 * theta) - theta;
//         s = sin(a);
//         c = cos(a);
// 
//         x = (xo - c * ro);
//         y = s * ro;
//         ta = atan2(y, x);
//         ts = sin(ta);
//         tc = cos(ta);
//         r = 1.0 / sqrt(sqr(x) + sqr(y));
// 
//         pVarTP.x -= pAmount * r * tc;
//         pVarTP.y += pAmount * r * ts;
// 
//       }
//     }
// 
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
// 
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{in, out};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_IN.equalsIgnoreCase(pName))
//       in = pValue;
//     else if (PARAM_OUT.equalsIgnoreCase(pName))
//       out = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "ortho";
//   }
// 
// }
// 
