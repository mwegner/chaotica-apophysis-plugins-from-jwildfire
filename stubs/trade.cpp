#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: trade

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/TradeFunc.java

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
	double r1;
	double d1;
	double r2;
	double d2;
	double _c1;
	double _c2;

} Variables;

#define APO_VARIABLE_PREFIX "trade_"
#include "plugin.h"

APO_PLUGIN("trade");
APO_VARIABLES(
	VAR_REAL(r1, 1.0),
	VAR_REAL(d1, 1.0),
	VAR_REAL(r2, 1.0),
	VAR_REAL(d2, 1.0),

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
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class TradeFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_R1 = "r1";
//   private static final String PARAM_D1 = "d1";
//   private static final String PARAM_R2 = "r2";
//   private static final String PARAM_D2 = "d2";
//   private static final String[] paramNames = {PARAM_R1, PARAM_D1, PARAM_R2, PARAM_D2};
// 
//   private double r1 = 1.0;
//   private double d1 = 1.0;
//   private double r2 = 1.0;
//   private double d2 = 1.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* trade by Michael Faber,  http://michaelfaber.deviantart.com/art/The-Lost-Variations-258913970 */
//     if (pAffineTP.x > 0.0) {
//       double r = sqrt(sqr(this._c1 - pAffineTP.x) + sqr(pAffineTP.y));
//       if (r <= this.r1) {
//         r *= this.r2 / this.r1;
//         double a = atan2(pAffineTP.y, this._c1 - pAffineTP.x);
//         double s = sin(a);
//         double c = cos(a);
//         pVarTP.x += pAmount * (r * c - this._c2);
//         pVarTP.y += pAmount * r * s;
//       } else {
//         pVarTP.x += pAmount * pAffineTP.x;
//         pVarTP.y += pAmount * pAffineTP.y;
//       }
//     } else {
//       double r = sqrt(sqr(-this._c2 - pAffineTP.x) + sqr(pAffineTP.y));
// 
//       if (r <= this.r2) {
//         r *= this.r1 / this.r2;
//         double a = atan2(pAffineTP.y, -this._c2 - pAffineTP.x);
//         double s = sin(a);
//         double c = cos(a);
//         pVarTP.x += pAmount * (r * c + this._c1);
//         pVarTP.y += pAmount * r * s;
//       } else {
//         pVarTP.x += pAmount * pAffineTP.x;
//         pVarTP.y += pAmount * pAffineTP.y;
//       }
//     }
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{r1, d1, r2, d2};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_R1.equalsIgnoreCase(pName))
//       r1 = limitVal(pValue, EPSILON, Double.MAX_VALUE);
//     else if (PARAM_D1.equalsIgnoreCase(pName))
//       d1 = limitVal(pValue, 0.0, Double.MAX_VALUE);
//     else if (PARAM_R2.equalsIgnoreCase(pName))
//       r2 = limitVal(pValue, EPSILON, Double.MAX_VALUE);
//     else if (PARAM_D2.equalsIgnoreCase(pName))
//       d2 = limitVal(pValue, 0.0, Double.MAX_VALUE);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "trade";
//   }
// 
//   private double _c1, _c2;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _c1 = r1 + d1;
//     _c2 = r2 + d2;
//   }
// 
// }
// 
