#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: spliptic_bs

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/SplipticBSFunc.java

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
	double x;
	double y;
	double _v;

} Variables;

#define APO_VARIABLE_PREFIX "spliptic_bs_"
#include "plugin.h"

APO_PLUGIN("spliptic_bs");
APO_VARIABLES(
	VAR_REAL(x, 0.05),
	VAR_REAL(y, 0.05)

);


double sqrt_safe (Variation* vp, double x) {

    return (VAR(x) < SMALL_EPSILON) ? 0.0 : sqrt(VAR(x));
}


int PluginVarPrepare(Variation* vp)
{
    VAR(_v) = VVAR / (M_PI / 2.0);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // A  mix of elliptic and splits by Brad Stefanov
    double tmp = FTy * FTy + FTx * FTx + 1.0;
    double x2 = 2.0 * FTx;
    double xmax = 0.5 * (sqrt(tmp + x2) + sqrt(tmp - x2));

    double a = FTx / xmax;
    double b = sqrt_safe(vp, 1.0 - a * a);

    if (FTx >= 0) {
      FPx += VAR(_v) * atan2(a, b) + VAR(x);
    } else {
      FPx += VAR(_v) * atan2(a, b) - VAR(x);
    }
    //    if (FTy > 0)
    if (GOODRAND_01() < 0.5)
      FPy += VAR(_v) * log(xmax + sqrt_safe(vp, xmax - 1.0)) + VAR(y);
    else
      FPy -= VAR(_v) * log(xmax + sqrt_safe(vp, xmax - 1.0)) + VAR(y);
    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }


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
// public class SplipticBSFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_X = "x";
//   private static final String PARAM_Y = "y";
//   private static final String[] paramNames = {PARAM_X, PARAM_Y};
//   private double x = 0.05;
//   private double y = 0.05;
// 
//   private double sqrt_safe(double x) {
//     return (x < SMALL_EPSILON) ? 0.0 : sqrt(x);
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // A  mix of elliptic and splits by Brad Stefanov
//     double tmp = pAffineTP.y * pAffineTP.y + pAffineTP.x * pAffineTP.x + 1.0;
//     double x2 = 2.0 * pAffineTP.x;
//     double xmax = 0.5 * (sqrt(tmp + x2) + sqrt(tmp - x2));
// 
//     double a = pAffineTP.x / xmax;
//     double b = sqrt_safe(1.0 - a * a);
// 
//     if (pAffineTP.x >= 0) {
//       pVarTP.x += _v * atan2(a, b) + x;
//     } else {
//       pVarTP.x += _v * atan2(a, b) - x;
//     }
//     //    if (pAffineTP.y > 0)
//     if (pContext.random() < 0.5)
//       pVarTP.y += _v * log(xmax + sqrt_safe(xmax - 1.0)) + y;
//     else
//       pVarTP.y -= _v * log(xmax + sqrt_safe(xmax - 1.0)) + y;
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
//     return new Object[]{x, y};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_X.equalsIgnoreCase(pName))
//       x = pValue;
//     else if (PARAM_Y.equalsIgnoreCase(pName))
//       y = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "spliptic_bs";
//   }
// 
//   private double _v;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _v = pAmount / (M_PI / 2.0);
//   }
// }
// 
