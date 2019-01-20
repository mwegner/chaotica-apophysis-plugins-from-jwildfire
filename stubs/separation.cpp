#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: separation

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/SeparationFunc.java

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
	double x;
	double xinside;
	double y;
	double yinside;

} Variables;

#define APO_VARIABLE_PREFIX "separation_"
#include "plugin.h"

APO_PLUGIN("separation");
APO_VARIABLES(
	VAR_REAL(x, 0.5),
	VAR_REAL(xinside, 0.05),
	VAR_REAL(y, 0.25),
	VAR_REAL(yinside, 0.025),

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
// import static org.jwildfire.base.mathlib.MathLib.sqrt;
// 
// public class SeparationFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_X = "x";
//   private static final String PARAM_XINSIDE = "xinside";
//   private static final String PARAM_Y = "y";
//   private static final String PARAM_YINSIDE = "yinside";
// 
//   private static final String[] paramNames = {PARAM_X, PARAM_XINSIDE, PARAM_Y, PARAM_YINSIDE};
// 
//   private double x = 0.5;
//   private double xinside = 0.05;
//   private double y = 0.25;
//   private double yinside = 0.025;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* separation from the apophysis plugin pack */
//     double sx2 = x * x;
//     double sy2 = y * y;
// 
//     if (pAffineTP.x > 0.0) {
//       pVarTP.x += pAmount * (sqrt(pAffineTP.x * pAffineTP.x + sx2) - pAffineTP.x * xinside);
//     } else {
//       pVarTP.x -= pAmount * (sqrt(pAffineTP.x * pAffineTP.x + sx2) + pAffineTP.x * xinside);
//     }
// 
//     if (pAffineTP.y > 0.0) {
//       pVarTP.y += pAmount * (sqrt(pAffineTP.y * pAffineTP.y + sy2) - pAffineTP.y * yinside);
//     } else {
//       pVarTP.y -= pAmount * (sqrt(pAffineTP.y * pAffineTP.y + sy2) + pAffineTP.y * yinside);
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
//     return new Object[]{x, xinside, y, yinside};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_X.equalsIgnoreCase(pName))
//       x = pValue;
//     else if (PARAM_XINSIDE.equalsIgnoreCase(pName))
//       xinside = pValue;
//     else if (PARAM_Y.equalsIgnoreCase(pName))
//       y = pValue;
//     else if (PARAM_YINSIDE.equalsIgnoreCase(pName))
//       yinside = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "separation";
//   }
// 
// }
// 
