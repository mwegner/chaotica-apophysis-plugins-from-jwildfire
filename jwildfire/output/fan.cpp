/*
    Apophysis Plugin: fan

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/FanFunc.java

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

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "fan_"
#include "plugin.h"

APO_PLUGIN("fan");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double dx = M_PI * XFORM_COEFF_20 * XFORM_COEFF_20 + SMALL_EPSILON;
    double dx2 = dx / 2;
    double a;
    if ((atan2(FTx, FTy) + XFORM_COEFF_21 - ((int) ((atan2(FTx, FTy) + XFORM_COEFF_21) / dx)) * dx) > dx2)
      a = atan2(FTx, FTy) - dx2;
    else
      a = atan2(FTx, FTy) + dx2;
    double sinr = sin(a);
    double cosr = cos(a);
    double r = VVAR * sqrt(FTx * FTx + FTy * FTy);
    FPx += r * cosr;
    FPy += r * sinr;
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
// public class FanFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double dx = M_PI * pXForm.getXYCoeff20() * pXForm.getXYCoeff20() + SMALL_EPSILON;
//     double dx2 = dx / 2;
//     double a;
//     if ((pAffineTP.getPrecalcAtan() + pXForm.getXYCoeff21() - ((int) ((pAffineTP.getPrecalcAtan() + pXForm.getXYCoeff21()) / dx)) * dx) > dx2)
//       a = pAffineTP.getPrecalcAtan() - dx2;
//     else
//       a = pAffineTP.getPrecalcAtan() + dx2;
//     double sinr = sin(a);
//     double cosr = cos(a);
//     double r = pAmount * sqrt(pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y);
//     pVarTP.x += r * cosr;
//     pVarTP.y += r * sinr;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "fan";
//   }
// 
// }
// 
