#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: pow_block

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PowBlockFunc.java

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
	double numerator; // 2.0 + random01() * 5.0
	double denominator; // 1.0 + random01() * 3.0
	double correctn;
	double correctd;
	double root;
	double _power;
	double _deneps;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "pow_block_"
#include "plugin.h"

APO_PLUGIN("pow_block");
APO_VARIABLES(
	VAR_REAL(numerator, 0),
	VAR_REAL(denominator, 0),
	VAR_REAL(correctn, 1.0),
	VAR_REAL(correctd, 1.0),
	VAR_REAL(root, 1.0),

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_power) = VAR(denominator) * VAR(correctn) * 1.0 / (fabs(VAR(correctd)) + SMALL_EPSILON);
    if (fabs(VAR(_power)) <= SMALL_EPSILON)
      VAR(_power) = SMALL_EPSILON;
    VAR(_power) = (VAR(numerator) * 0.5) / VAR(_power);
    VAR(_deneps) = VAR(denominator);
    if (fabs(VAR(_deneps)) <= SMALL_EPSILON)
      VAR(_deneps) = SMALL_EPSILON;
    VAR(_deneps) = 1.0 / VAR(_deneps);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // pow_block optimized version, original by cothe coded by DarkBeam 2014
    double theta = atan2(FTx, FTy);
    double r2 = pow((FTx * FTx + FTy * FTy), VAR(_power)) * VVAR;

    double ran = ((theta) * VAR(_deneps) + (VAR(root)
            * M_2PI * floor(GOODRAND_01() * VAR(denominator)) * VAR(_deneps))) * VAR(numerator);

    FPx += r2 * cos(ran);
    FPy += r2 * sin(ran);
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
// public class PowBlockFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_NUMERATOR = "numerator";
//   private static final String PARAM_DENOMINATOR = "denominator";
//   private static final String PARAM_ROOT = "root";
//   private static final String PARAM_CORRECTN = "correctn";
//   private static final String PARAM_CORRECTD = "correctd";
// 
//   private static final String[] paramNames = {PARAM_NUMERATOR, PARAM_DENOMINATOR, PARAM_ROOT, PARAM_CORRECTN, PARAM_CORRECTD};
// 
//   private double numerator = 2.0 + Math.random() * 5.0;
//   private double denominator = 1.0 + Math.random() * 3.0;
//   private double correctn = 1.0;
//   private double correctd = 1.0;
//   private double root = 1.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // pow_block optimized version, original by cothe coded by DarkBeam 2014
//     double theta = pAffineTP.getPrecalcAtanYX();
//     double r2 = pow(pAffineTP.getPrecalcSumsq(), _power) * pAmount;
// 
//     double ran = ((theta) * _deneps + (root
//             * M_2PI * floor(pContext.random() * denominator) * _deneps)) * numerator;
// 
//     pVarTP.x += r2 * cos(ran);
//     pVarTP.y += r2 * sin(ran);
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
//     return new Object[]{numerator, denominator, root, correctn, correctd};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_NUMERATOR.equalsIgnoreCase(pName))
//       numerator = pValue;
//     else if (PARAM_DENOMINATOR.equalsIgnoreCase(pName))
//       denominator = pValue;
//     else if (PARAM_ROOT.equalsIgnoreCase(pName))
//       root = pValue;
//     else if (PARAM_CORRECTN.equalsIgnoreCase(pName))
//       correctn = pValue;
//     else if (PARAM_CORRECTD.equalsIgnoreCase(pName))
//       correctd = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "pow_block";
//   }
// 
//   private double _power;
//   private double _deneps;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _power = denominator * correctn * 1.0 / (fabs(correctd) + SMALL_EPSILON);
//     if (fabs(_power) <= SMALL_EPSILON)
//       _power = SMALL_EPSILON;
//     _power = (numerator * 0.5) / _power;
//     _deneps = denominator;
//     if (fabs(_deneps) <= SMALL_EPSILON)
//       _deneps = SMALL_EPSILON;
//     _deneps = 1.0 / _deneps;
//   }
// 
// }
