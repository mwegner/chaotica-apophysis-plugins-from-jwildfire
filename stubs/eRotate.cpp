#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: eRotate

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ERotateFunc.java

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
	double rotate;

} Variables;

#define APO_VARIABLE_PREFIX "eRotate_"
#include "plugin.h"

APO_PLUGIN("eRotate");
APO_VARIABLES(
	VAR_REAL(rotate, 0.0)

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
// public class ERotateFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_ROTATE = "rotate";
// 
//   private static final String[] paramNames = {PARAM_ROTATE};
// 
//   private double rotate = 0.0;
// 
//   //Taking the square root of numbers close to zero is dangerous.  If x is negative
//   //due to floating point errors we get NaN results.
//   private double sqrt_safe(double x) {
//     if (x <= 0.0)
//       return 0.0;
//     return sqrt(x);
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // eRotate by Michael Faber, http://michaelfaber.deviantart.com/art/eSeries-306044892
//     double tmp = pAffineTP.y * pAffineTP.y + pAffineTP.x * pAffineTP.x + 1.0;
//     double tmp2 = 2.0 * pAffineTP.x;
//     double xmax = (sqrt_safe(tmp + tmp2) + sqrt_safe(tmp - tmp2)) * 0.5;
//     double sinnu, cosnu;
//     if (xmax < 1.0)
//       xmax = 1.0;
// 
//     double t = pAffineTP.x / xmax;
//     if (t > 1.0)
//       t = 1.0;
//     else if (t < -1.0)
//       t = -1.0;
//     double nu = acos(t); // -Pi < nu < Pi
//     if (pAffineTP.y < 0)
//       nu *= -1.0;
// 
//     nu = fmod(nu + rotate + M_PI, M_2PI) - M_PI;
// 
//     sinnu = sin(nu);
//     cosnu = cos(nu);
//     pVarTP.x += pAmount * xmax * cosnu;
//     pVarTP.y += pAmount * sqrt(xmax - 1.0) * sqrt(xmax + 1.0) * sinnu;
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
//     return new Object[]{rotate};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_ROTATE.equalsIgnoreCase(pName))
//       rotate = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "eRotate";
//   }
// 
// }
// 
