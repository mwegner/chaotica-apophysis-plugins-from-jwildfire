#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: circlize

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CirclizeFunc.java

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
	double hole;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "circlize_"
#include "plugin.h"

APO_PLUGIN("circlize");
APO_VARIABLES(
	VAR_REAL(hole, 0.40),

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double var4_PI = VVAR / M_PI_4;

    double absx = fabs(FTx);
    double absy = fabs(FTy);
    double perimeter, side;
    if (absx >= absy) {
      if (FTx >= absy) {
        perimeter = absx + FTy;
      } else {
        perimeter = 5.0 * absx - FTy;
      }
      side = absx;
    } else {
      if (FTy >= absx) {
        perimeter = 3.0 * absy - FTx;
      } else {
        perimeter = 7.0 * absy + FTx;
      }
      side = absy;
    }

    // tsk tsk... VAR(hole) is not scaled by vvar.
    double r = var4_PI * side + VAR(hole);
    double a = M_PI_4 * perimeter / side - M_PI_4;
    double sina = sin(a);
    double cosa = cos(a);

    FPx += r * cosa;
    FPy += r * sina;
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
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class CirclizeFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_HOLE = "hole";
// 
//   private static final String[] paramNames = {PARAM_HOLE};
// 
//   private double hole = 0.40;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double var4_PI = pAmount / M_PI_4;
// 
//     double absx = fabs(pAffineTP.x);
//     double absy = fabs(pAffineTP.y);
//     double perimeter, side;
//     if (absx >= absy) {
//       if (pAffineTP.x >= absy) {
//         perimeter = absx + pAffineTP.y;
//       } else {
//         perimeter = 5.0 * absx - pAffineTP.y;
//       }
//       side = absx;
//     } else {
//       if (pAffineTP.y >= absx) {
//         perimeter = 3.0 * absy - pAffineTP.x;
//       } else {
//         perimeter = 7.0 * absy + pAffineTP.x;
//       }
//       side = absy;
//     }
// 
//     // tsk tsk... hole is not scaled by vvar.
//     double r = var4_PI * side + hole;
//     double a = M_PI_4 * perimeter / side - M_PI_4;
//     double sina = sin(a);
//     double cosa = cos(a);
// 
//     pVarTP.x += r * cosa;
//     pVarTP.y += r * sina;
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
//     return new Object[]{hole};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_HOLE.equalsIgnoreCase(pName))
//       hole = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "circlize";
//   }
// 
// }
// 
