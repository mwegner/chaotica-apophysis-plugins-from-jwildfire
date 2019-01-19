/*
    Apophysis Plugin: circleRand

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CircleRandFunc.java

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
	double Sc;
	double Dens;
	double X;
	double Y;
	int Seed;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "circleRand_"
#include "plugin.h"

APO_PLUGIN("circleRand");
APO_VARIABLES(
	VAR_REAL(Sc, 1.0),
	VAR_REAL(Dens, 0.5),
	VAR_REAL(X, 10.0),
	VAR_REAL(Y, 10.0),
	VAR_INTEGER(Seed, 0),

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
// import static org.jwildfire.base.mathlib.MathLib.floor;
// import static org.jwildfire.base.mathlib.MathLib.sqrt;
// 
// public class CircleRandFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_SC = "Sc";
//   private static final String PARAM_DENS = "Dens";
//   private static final String PARAM_X = "X";
//   private static final String PARAM_Y = "Y";
//   private static final String PARAM_SEED = "Seed";
//   private static final String[] paramNames = {PARAM_SC, PARAM_DENS, PARAM_X, PARAM_Y, PARAM_SEED};
// 
//   private double Sc = 1.0;
//   private double Dens = 0.5;
//   private double X = 10.0;
//   private double Y = 10.0;
//   private int Seed = 0;
// 
//   private static final double AM = 1.0 / 2147483647;
// 
//   private double DiscretNoise2(int X, int Y) {
//     int n = X + Y * 57;
//     n = (n << 13) ^ n;
//     return ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) * AM;
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* CircleRand by eralex, http://eralex61.deviantart.com/art/Circles-Plugins-126273412 */
//     double X, Y, U;
//     int M, N;
//     final int maxIter = 100;
//     int iter = 0;
//     do {
//       X = this.X * (1.0 - 2.0 * pContext.random());
//       Y = this.Y * (1.0 - 2.0 * pContext.random());
//       M = (int) floor(0.5 * X / this.Sc);
//       N = (int) floor(0.5 * Y / this.Sc);
//       X = X - (M * 2 + 1) * this.Sc;
//       Y = Y - (N * 2 + 1) * this.Sc;
//       U = sqrt(X * X + Y * Y);
//       if (++iter > maxIter) {
//         break;
//       }
//     }
//     while ((DiscretNoise2(M + this.Seed, N) > this.Dens) || (U > (0.3 + 0.7 * DiscretNoise2(M + 10, N + 3)) * this.Sc));
// 
//     pVarTP.x += pAmount * (X + (M * 2 + 1) * this.Sc);
//     pVarTP.y += pAmount * (Y + (N * 2 + 1) * this.Sc);
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
//     return new Object[]{Sc, Dens, X, Y, Seed};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_SC.equalsIgnoreCase(pName))
//       Sc = pValue;
//     else if (PARAM_DENS.equalsIgnoreCase(pName))
//       Dens = pValue;
//     else if (PARAM_X.equalsIgnoreCase(pName))
//       X = pValue;
//     else if (PARAM_Y.equalsIgnoreCase(pName))
//       Y = pValue;
//     else if (PARAM_SEED.equalsIgnoreCase(pName))
//       Seed = Tools.FTOI(pValue);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "circleRand";
//   }
// 
// }
// 
