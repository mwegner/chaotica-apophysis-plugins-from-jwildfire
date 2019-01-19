/*
    Apophysis Plugin: hypercrop

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/HypercropFunc.java

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
	int n;
	double rad;
	double zero;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "hypercrop_"
#include "plugin.h"

APO_PLUGIN("hypercrop");
APO_VARIABLES(
	VAR_INTEGER(n, 4),
	VAR_REAL(rad, 1.0),
	VAR_REAL(zero, 0.0),

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
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class HypercropFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_N = "n";
//   private static final String PARAM_RAD = "rad";
//   private static final String PARAM_ZERO = "zero";
// 
//   private static final String[] paramNames = {PARAM_N, PARAM_RAD, PARAM_ZERO};
// 
//   private int n = 4;
//   private double rad = 1.0;
//   private double zero = 0.0;
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP,
//                         double pAmount) {
// 
//     // "Hypercrop" variation created by tatasz implemented into JWildfire by Brad
//     // Stefanov https://www.deviantart.com/tatasz/art/Hyperstuff-721510796
//     double coef = n * 0.5 / M_PI;
//     double FX = pAffineTP.x;
//     double FY = pAffineTP.y;
//     double FZ = pAffineTP.z;
//     double a0 = M_PI / n;
//     double len = 1 / cos(a0);
//     double d = rad * sin(a0) * len;
//     double angle = atan2(pAffineTP.y, pAffineTP.x);
//     angle = floor(angle * coef) / coef + M_PI / n;
//     double x0 = cos(angle) * len;
//     double y0 = sin(angle) * len;
//     if (sqrt(sqr(pAffineTP.x - x0) + sqr(pAffineTP.y - y0)) < d) {
//       if (zero > 1.5) {
//         FX = x0;
//         FY = y0;
//         FZ = 0.0;
//       } else {
//         if (zero > 0.5) {
//           FX = 0.0;
//           FY = 0.0;
//           FZ = 0.0;
//         } else {
//           double rangle = atan2(pAffineTP.y - y0, pAffineTP.x - x0);
//           FX = x0 + cos(rangle) * d;
//           FY = y0 + sin(rangle) * d;
//           FZ = 0.0;
//         }
//       }
//     }
// 
//     pVarTP.x += FX * pAmount;
//     pVarTP.y += FY * pAmount;
//     pVarTP.z += FZ * pAmount;
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{n, rad, zero};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_N.equalsIgnoreCase(pName))
//       n = Tools.FTOI(pValue);
//     else if (PARAM_RAD.equalsIgnoreCase(pName))
//       rad = pValue;
//     else if (PARAM_ZERO.equalsIgnoreCase(pName))
//       zero = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "hypercrop";
//   }
// 
// }
// 
