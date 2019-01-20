#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: mobiusN

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/MobiusNFunc.java

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
	double re_a;
	double re_b;
	double re_c;
	double re_d;
	double im_a;
	double im_b;
	double im_c;
	double im_d;
	double power;
	double dist;

} Variables;

#define APO_VARIABLE_PREFIX "mobiusN_"
#include "plugin.h"

APO_PLUGIN("mobiusN");
APO_VARIABLES(
	VAR_REAL(re_a, 1.0),
	VAR_REAL(re_b, 0.0),
	VAR_REAL(re_c, 0.0),
	VAR_REAL(re_d, 1.0),
	VAR_REAL(im_a, 0.0),
	VAR_REAL(im_b, 0.0),
	VAR_REAL(im_c, 0.0),
	VAR_REAL(im_d, 0.0),
	VAR_REAL(power, 1.0),
	VAR_REAL(dist, 1.0)

);



int PluginVarPrepare(Variation* vp)
{
    if (fabs(VAR(power)) < 1.0)
      VAR(power) = 1.0;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{

    double realU, imagU, realV, imagV, radV, x, y, z, r, alpha, sina, cosa, n;

    // Transformation into N-VAR(power) space
    z = 4.0 * VAR(dist) / VAR(power);
    r = pow((sqrt(FTx * FTx + FTy * FTy) + SMALL_EPSILON), z);

    alpha = atan2(FTy, FTx) * VAR(power);
    sina = sin(alpha);
    cosa = cos(alpha);
    x = r * cosa;
    y = r * sina;

    // We perform what appears to be a rotation matrix and shift,
    // letting x and y form a matrix through which we modify the points [VAR(re_a),VAR(im_a)] and [VAR(re_c),VAR(im_c)]
    //[Ux,Uy] = [x,-y; y,-x]*[VAR(re_a), VAR(im_a)] + [VAR(re_b), VAR(im_b)]
    realU = VAR(re_a) * x - VAR(im_a) * y + VAR(re_b);
    imagU = VAR(re_a) * y + VAR(im_a) * x + VAR(im_b);
    realV = VAR(re_c) * x - VAR(im_c) * y + VAR(re_d);
    imagV = VAR(re_c) * y + VAR(im_c) * x + VAR(im_d);
    radV = sqr(realV) + sqr(imagV);

    x = (realU * realV + imagU * imagV) / radV;
    y = (imagU * realV - realU * imagV) / radV;

    // Reverse transformation into N-VAR(power) space
    z = 1.0 / z;
    r = pow(sqrt(sqr(x) + sqr(y)), z);

    n = floor(VAR(power) * GOODRAND_01());
    alpha = (atan2(y, x) + n * M_2PI) / floor(VAR(power));
    sina = sin(alpha);
    cosa = cos(alpha);

    FPx += VVAR * r * cosa;
    FPy += VVAR * r * sina;
    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }


    return TRUE;
}





// original java file embedded here:
//
// /*
//   JWildfire - an image and animation processor written in Java 
//   Copyright (C) 1995-2016 Andreas Maschke
// 
//   Copyright (C) 2016 Nicolaus Anderson
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
// /**
//  * @author eralex61, transcribed by chronologicaldot, fixed by thargor6
//  */
// public class MobiusNFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_RE_A = "re_a";
//   private static final String PARAM_RE_B = "re_b";
//   private static final String PARAM_RE_C = "re_c";
//   private static final String PARAM_RE_D = "re_d";
//   private static final String PARAM_IM_A = "im_a";
//   private static final String PARAM_IM_B = "im_b";
//   private static final String PARAM_IM_C = "im_c";
//   private static final String PARAM_IM_D = "im_d";
//   private static final String PARAM_POWER = "power";
//   private static final String PARAM_DIST = "dist";
// 
//   private static final String[] params = {PARAM_RE_A, PARAM_RE_B, PARAM_RE_C, PARAM_RE_D, PARAM_IM_A, PARAM_IM_B, PARAM_IM_C, PARAM_IM_D, PARAM_POWER, PARAM_DIST};
// 
//   private double realA = 1.0, realB = 0.0, realC = 0.0, realD = 1.0, imagA = 0.0, imagB = 0.0, imagC = 0.0, imagD = 0.0, power = 1.0, dist = 1.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// 
//     double realU, imagU, realV, imagV, radV, x, y, z, r, alpha, sina, cosa, n;
// 
//     // Transformation into N-power space
//     z = 4.0 * dist / power;
//     r = pow(pAffineTP.getPrecalcSqrt(), z);
// 
//     alpha = atan2(pAffineTP.y, pAffineTP.x) * power;
//     sina = sin(alpha);
//     cosa = cos(alpha);
//     x = r * cosa;
//     y = r * sina;
// 
//     // We perform what appears to be a rotation matrix and shift,
//     // letting x and y form a matrix through which we modify the points [realA,imagA] and [realC,imagC]
//     //[Ux,Uy] = [x,-y; y,-x]*[realA, imagA] + [realB, imagB]
//     realU = realA * x - imagA * y + realB;
//     imagU = realA * y + imagA * x + imagB;
//     realV = realC * x - imagC * y + realD;
//     imagV = realC * y + imagC * x + imagD;
//     radV = sqr(realV) + sqr(imagV);
// 
//     x = (realU * realV + imagU * imagV) / radV;
//     y = (imagU * realV - realU * imagV) / radV;
// 
//     // Reverse transformation into N-power space
//     z = 1.0 / z;
//     r = pow(sqrt(sqr(x) + sqr(y)), z);
// 
//     n = floor(power * pContext.random());
//     alpha = (atan2(y, x) + n * M_2PI) / floor(power);
//     sina = sin(alpha);
//     cosa = cos(alpha);
// 
//     pVarTP.x += pAmount * r * cosa;
//     pVarTP.y += pAmount * r * sina;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "mobiusN";
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return params;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{realA, realB, realC, realD, imagA, imagB, imagC, imagD, power, dist};
//   }
// 
//   @Override
//   public String[] getParameterAlternativeNames() {
//     return new String[]{"MobiusNRe_A", "MobiusNRe_B", "MobiusNRe_C", "MobiusNRe_D", "MobiusNIm_A", "MobiusNIm_B", "MobiusNIm_C", "MobiusNIm_D", "MobiusN_Power", "MobiusN_Dist"};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_RE_A.equalsIgnoreCase(pName)) {
//       realA = pValue;
//     } else if (PARAM_RE_B.equalsIgnoreCase(pName)) {
//       realB = pValue;
//     } else if (PARAM_RE_C.equalsIgnoreCase(pName)) {
//       realC = pValue;
//     } else if (PARAM_RE_D.equalsIgnoreCase(pName)) {
//       realD = pValue;
//     } else if (PARAM_IM_A.equalsIgnoreCase(pName)) {
//       imagA = pValue;
//     } else if (PARAM_IM_B.equalsIgnoreCase(pName)) {
//       imagB = pValue;
//     } else if (PARAM_IM_C.equalsIgnoreCase(pName)) {
//       imagC = pValue;
//     } else if (PARAM_IM_D.equalsIgnoreCase(pName)) {
//       imagD = pValue;
//     } else if (PARAM_POWER.equalsIgnoreCase(pName)) {
//       power = pValue;
//     } else if (PARAM_DIST.equalsIgnoreCase(pName)) {
//       dist = pValue;
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     if (fabs(power) < 1.0)
//       power = 1.0;
//   }
// 
// }
