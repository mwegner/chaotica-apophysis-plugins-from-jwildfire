/*
    Apophysis Plugin: vogel

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/VogelFunc.java

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
	double _M_PHI = 1.61803398874989484820;
	double _M_2PI_PHI2; // M_2PI / (M_PHI * M_PHI)
	double _sina = 0.0;
	double _cosa = 0.0;
	int n;
	double scale;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "vogel_"
#include "plugin.h"

APO_PLUGIN("vogel");
APO_VARIABLES(
	VAR_INTEGER(n, 20),
	VAR_REAL(scale, 1.0),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
   VAR(_M_PHI) = 1.61803398874989484820;
   VAR(_sina) = 0.0;
   VAR(_cosa) = 0.0;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // Vogel function by Victor Ganora
    int i = GOODRAND_0X(VAR(n)) + 1;
    double a = i * VAR(_M_2PI_PHI2);
    fsincos(a, &VAR(_sina), &VAR(_cosa));
    double r = VVAR * ((sqrt(FTx * FTx + FTy * FTy) + SMALL_EPSILON) + sqrt(i));
    FPx += r * (VAR(_cosa) + (VAR(scale) * FTx));
    FPy += r * (VAR(_sina) + (VAR(scale) * FTy));
    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }


    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// import odk.lang.double;
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class VogelFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
//   private static final String PARAM_N = "n";
//   private static final String PARAM_SCALE = "scale";
//   private static final String[] paramNames = {PARAM_N, PARAM_SCALE};
// 
//   private final double M_PHI = 1.61803398874989484820;
//   private final double M_2PI_PHI2 = M_2PI / (M_PHI * M_PHI);
// 
//   private final double sina = 0.0;
//   private final double cosa = 0.0;
// 
//   private int n = 20;
//   private double scale = 1.;
// 
//   @Override
//   public String getName() {
//     return "vogel";
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{n, scale};
//   }
// 
//   @Override
//   public void setParameter(final String pName, final double pValue) {
//     if (PARAM_N.equalsIgnoreCase(pName)) {
//       n = limitIntVal(Tools.FTOI(pValue), 1, Integer.MAX_VALUE);
//     } else if (PARAM_SCALE.equalsIgnoreCase(pName)) {
//       scale = pValue;
//     } else {
//       throw new IllegalArgumentException(pName);
//     }
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // Vogel function by Victor Ganora
//     final int i = pContext.random(n) + 1;
//     final double a = i * M_2PI_PHI2;
//     sinAndCos(a, sina, cosa);
//     final double r = pAmount * (pAffineTP.getPrecalcSqrt() + sqrt(i));
//     pVarTP.x += r * (cosa.value + (scale * pAffineTP.x));
//     pVarTP.y += r * (sina.value + (scale * pAffineTP.y));
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// }
// 
