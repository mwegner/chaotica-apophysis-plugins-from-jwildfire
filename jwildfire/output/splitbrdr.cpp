/*
    Apophysis Plugin: splitbrdr

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/SplitBrdrFunc.java

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
	double y;
	double px;
	double py;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "splitbrdr_"
#include "plugin.h"

APO_PLUGIN("splitbrdr");
APO_VARIABLES(
	VAR_REAL(x, 0.25),
	VAR_REAL(y, 0.25),
	VAR_REAL(px, 0.0),
	VAR_REAL(py, 0.0),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* splitbrdr from FracFx, http://fracfx.deviantart.com/art/FracFx-Plugin-Pack-171806681 */
    double B, b;
    B = (sqr(FTx) + sqr(FTy)) / 4 + 1; //make a bubble ;p
    b = VVAR / B;
    FPx += FTx * b;
    FPy += FTy * b;

    double roundX, roundY, offsetX, offsetY;
    //add a border 0.25 default adjustable wih VAR(x) and VAR(y)

    roundX = rint(FTx);
    roundY = rint(FTy);
    offsetX = FTx - roundX;
    offsetY = FTy - roundY;

    if (GOODRAND_01() >= 0.75) {
      FPx += VVAR * (offsetX * 0.5 + roundX);
      FPy += VVAR * (offsetY * 0.5 + roundY);
    } else {
      if (fabs(offsetX) >= fabs(offsetY)) {
        if (offsetX >= 0.0) {
          FPx += VVAR * (offsetX * 0.5 + roundX + VAR(x));
          FPy += VVAR * (offsetY * 0.5 + roundY + VAR(y) * offsetY / offsetX);
        } else {
          FPx += VVAR * (offsetX * 0.5 + roundX - VAR(y));
          FPy += VVAR * (offsetY * 0.5 + roundY - VAR(y) * offsetY / offsetX);
        }
      } else {
        if (offsetY >= 0.0) {
          FPy += VVAR * (offsetY * 0.5 + roundY + VAR(y));
          FPx += VVAR * (offsetX * 0.5 + roundX + offsetX / offsetY * VAR(y));
        } else {
          FPy += VVAR * (offsetY * 0.5 + roundY - VAR(y));
          FPx += VVAR * (offsetX * 0.5 + roundX - offsetX / offsetY * VAR(x));
        }
      }
    }
    FPx += FTx * VAR(px);
    FPy += FTy * VAR(py);
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
// public class SplitBrdrFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_X = "x";
//   private static final String PARAM_Y = "y";
//   private static final String PARAM_PX = "px";
//   private static final String PARAM_PY = "py";
//   private static final String[] paramNames = {PARAM_X, PARAM_Y, PARAM_PX, PARAM_PY};
// 
//   private double x = 0.25;
//   private double y = 0.25;
//   private double px = 0.0;
//   private double py = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* splitbrdr from FracFx, http://fracfx.deviantart.com/art/FracFx-Plugin-Pack-171806681 */
//     double B, b;
//     B = (sqr(pAffineTP.x) + sqr(pAffineTP.y)) / 4 + 1; //make a bubble ;p
//     b = pAmount / B;
//     pVarTP.x += pAffineTP.x * b;
//     pVarTP.y += pAffineTP.y * b;
// 
//     double roundX, roundY, offsetX, offsetY;
//     //add a border 0.25 default adjustable wih this.x and this.y
// 
//     roundX = rint(pAffineTP.x);
//     roundY = rint(pAffineTP.y);
//     offsetX = pAffineTP.x - roundX;
//     offsetY = pAffineTP.y - roundY;
// 
//     if (Math.random() >= 0.75) {
//       pVarTP.x += pAmount * (offsetX * 0.5 + roundX);
//       pVarTP.y += pAmount * (offsetY * 0.5 + roundY);
//     } else {
//       if (fabs(offsetX) >= fabs(offsetY)) {
//         if (offsetX >= 0.0) {
//           pVarTP.x += pAmount * (offsetX * 0.5 + roundX + this.x);
//           pVarTP.y += pAmount * (offsetY * 0.5 + roundY + this.y * offsetY / offsetX);
//         } else {
//           pVarTP.x += pAmount * (offsetX * 0.5 + roundX - this.y);
//           pVarTP.y += pAmount * (offsetY * 0.5 + roundY - this.y * offsetY / offsetX);
//         }
//       } else {
//         if (offsetY >= 0.0) {
//           pVarTP.y += pAmount * (offsetY * 0.5 + roundY + this.y);
//           pVarTP.x += pAmount * (offsetX * 0.5 + roundX + offsetX / offsetY * this.y);
//         } else {
//           pVarTP.y += pAmount * (offsetY * 0.5 + roundY - this.y);
//           pVarTP.x += pAmount * (offsetX * 0.5 + roundX - offsetX / offsetY * this.x);
//         }
//       }
//     }
//     pVarTP.x += pAffineTP.x * this.px;
//     pVarTP.y += pAffineTP.y * this.py;
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
//     return new Object[]{x, y, px, py};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_X.equalsIgnoreCase(pName))
//       x = pValue;
//     else if (PARAM_Y.equalsIgnoreCase(pName))
//       y = pValue;
//     else if (PARAM_PX.equalsIgnoreCase(pName))
//       px = pValue;
//     else if (PARAM_PY.equalsIgnoreCase(pName))
//       py = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "splitbrdr";
//   }
// 
// }
// 
