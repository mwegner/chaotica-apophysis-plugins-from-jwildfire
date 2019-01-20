#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: fourth

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/FourthFunc.java

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
	double spin; // M_PI
	double space;
	double twist;
	double x;
	double y;
	double _sqrvvar;

} Variables;

#define APO_VARIABLE_PREFIX "fourth_"
#include "plugin.h"

APO_PLUGIN("fourth");
APO_VARIABLES(
	VAR_REAL(spin, M_PI),
	VAR_REAL(space, 0.0),
	VAR_REAL(twist, 0.0),
	VAR_REAL(x, 0.0),
	VAR_REAL(y, 0.0)

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_sqrvvar) = VVAR * VVAR;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* fourth from guagapunyaimel, http://amorinaashton.deviantart.com/art/Fourth-Plugin-175043938?q=favby%3Aamorinaashton%2F1243451&qo=14 */

    if (FTx > 0.0 && FTy > 0.0) //kuadran IV: spherical
    {
      double a = atan2(FTy, FTx);
      double r = 1.0 / sqrt(sqr(FTx) + sqr(FTy));
      double s = sin(a);
      double c = cos(a);
      FPx += VVAR * r * c;
      FPy += VVAR * r * s;
    } else if (FTx > 0.0 && FTy < 0.0) //kuadran I: loonie
    {
      double r2 = sqr(FTx) + sqr(FTy);

      if (r2 < VAR(_sqrvvar)) {
        double r = VVAR * sqrt(VAR(_sqrvvar) / r2 - 1.0);
        FPx += r * FTx;
        FPy += r * FTy;
      } else {
        FPx += VVAR * FTx;
        FPy += VVAR * FTy;
      }
    } else if (FTx < 0.0 && FTy > 0.0) // kuadran III: susan
    {
      double r;
      double sina, cosa;
      double VAR(x) = FTx - VAR(x);
      double VAR(y) = FTy + VAR(y);

      r = sqrt(VAR(x) * VAR(x) + VAR(y) * VAR(y));

      if (r < VVAR) {
        double a = atan2(VAR(y), VAR(x)) + VAR(spin) + VAR(twist) * (VVAR - r);
        sina = sin(a);
        cosa = cos(a);
        r = VVAR * r;
        FPx += r * cosa + VAR(x);
        FPy += r * sina - VAR(y);
      } else {
        r = VVAR * (1.0 + VAR(space) / r);
        FPx += r * VAR(x) + VAR(x);
        FPy += r * VAR(y) - VAR(y);
      }
    } else //kuadran II: Linear
    {
      FPx += VVAR * FTx;
      FPy += VVAR * FTy;
    }

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
// public class FourthFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_SPIN = "spin";
//   private static final String PARAM_SPACE = "space";
//   private static final String PARAM_TWIST = "twist";
//   private static final String PARAM_X = "x";
//   private static final String PARAM_Y = "y";
//   private static final String[] paramNames = {PARAM_SPIN, PARAM_SPACE, PARAM_TWIST, PARAM_X, PARAM_Y};
// 
//   private double spin = M_PI;
//   private double space = 0.0;
//   private double twist = 0.0;
//   private double x = 0.0;
//   private double y = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* fourth from guagapunyaimel, http://amorinaashton.deviantart.com/art/Fourth-Plugin-175043938?q=favby%3Aamorinaashton%2F1243451&qo=14 */
// 
//     if (pAffineTP.x > 0.0 && pAffineTP.y > 0.0) //kuadran IV: spherical
//     {
//       double a = atan2(pAffineTP.y, pAffineTP.x);
//       double r = 1.0 / sqrt(sqr(pAffineTP.x) + sqr(pAffineTP.y));
//       double s = sin(a);
//       double c = cos(a);
//       pVarTP.x += pAmount * r * c;
//       pVarTP.y += pAmount * r * s;
//     } else if (pAffineTP.x > 0.0 && pAffineTP.y < 0.0) //kuadran I: loonie
//     {
//       double r2 = sqr(pAffineTP.x) + sqr(pAffineTP.y);
// 
//       if (r2 < this.sqrvvar) {
//         double r = pAmount * sqrt(this.sqrvvar / r2 - 1.0);
//         pVarTP.x += r * pAffineTP.x;
//         pVarTP.y += r * pAffineTP.y;
//       } else {
//         pVarTP.x += pAmount * pAffineTP.x;
//         pVarTP.y += pAmount * pAffineTP.y;
//       }
//     } else if (pAffineTP.x < 0.0 && pAffineTP.y > 0.0) // kuadran III: susan
//     {
//       double r;
//       double sina, cosa;
//       double x = pAffineTP.x - this.x;
//       double y = pAffineTP.y + this.y;
// 
//       r = sqrt(x * x + y * y);
// 
//       if (r < pAmount) {
//         double a = atan2(y, x) + this.spin + this.twist * (pAmount - r);
//         sina = sin(a);
//         cosa = cos(a);
//         r = pAmount * r;
//         pVarTP.x += r * cosa + this.x;
//         pVarTP.y += r * sina - this.y;
//       } else {
//         r = pAmount * (1.0 + this.space / r);
//         pVarTP.x += r * x + this.x;
//         pVarTP.y += r * y - this.y;
//       }
//     } else //kuadran II: Linear
//     {
//       pVarTP.x += pAmount * pAffineTP.x;
//       pVarTP.y += pAmount * pAffineTP.y;
//     }
// 
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
//     return new Object[]{spin, space, twist, x, y};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_SPIN.equalsIgnoreCase(pName))
//       spin = pValue;
//     else if (PARAM_SPACE.equalsIgnoreCase(pName))
//       space = pValue;
//     else if (PARAM_TWIST.equalsIgnoreCase(pName))
//       twist = pValue;
//     else if (PARAM_X.equalsIgnoreCase(pName))
//       x = pValue;
//     else if (PARAM_Y.equalsIgnoreCase(pName))
//       y = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "fourth";
//   }
// 
//   private double sqrvvar;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     sqrvvar = pAmount * pAmount;
//   }
// }
// 
