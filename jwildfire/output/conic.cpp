/*
    Apophysis Plugin: conic

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ConicFunc.java

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
	double eccentricity;
	double holes;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "conic_"
#include "plugin.h"

APO_PLUGIN("conic");
APO_VARIABLES(
	VAR_REAL(eccentricity, 1.0),
	VAR_REAL(holes, 0.0),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* cyberxaos, 4/2007 */
    double ct = FTx / (sqrt(FTx * FTx + FTy * FTy) + SMALL_EPSILON);
    double r = VVAR * (GOODRAND_01() - VAR(holes)) * VAR(eccentricity) / (1 + VAR(eccentricity) * ct) / (sqrt(FTx * FTx + FTy * FTy) + SMALL_EPSILON);
    FPx += r * FTx;
    FPy += r * FTy;
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
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class ConicFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_ECCENTRICITY = "eccentricity";
//   private static final String PARAM_HOLES = "holes";
// 
//   private static final String[] paramNames = {PARAM_ECCENTRICITY, PARAM_HOLES};
// 
//   private double eccentricity = 1.0;
//   private double holes = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* cyberxaos, 4/2007 */
//     double ct = pAffineTP.x / pAffineTP.getPrecalcSqrt();
//     double r = pAmount * (pContext.random() - holes) * eccentricity / (1 + eccentricity * ct) / pAffineTP.getPrecalcSqrt();
//     pVarTP.x += r * pAffineTP.x;
//     pVarTP.y += r * pAffineTP.y;
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
//     return new Object[]{eccentricity, holes};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_ECCENTRICITY.equalsIgnoreCase(pName))
//       eccentricity = pValue;
//     else if (PARAM_HOLES.equalsIgnoreCase(pName))
//       holes = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "conic";
//   }
// 
// }
// 
