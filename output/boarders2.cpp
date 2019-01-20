#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: boarders2

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Boarders2Func.java

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
	double c;
	double left;
	double right;
	double _c;
	double _cl;
	double _cr;

} Variables;

#define APO_VARIABLE_PREFIX "boarders2_"
#include "plugin.h"

APO_PLUGIN("boarders2");
APO_VARIABLES(
	VAR_REAL(c, 0.4),
	VAR_REAL(left, 0.65),
	VAR_REAL(right, 0.35)

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_c) = fabs(VAR(c));
    VAR(_cl) = fabs(VAR(left));
    VAR(_cr) = fabs(VAR(right));
    VAR(_c) = VAR(_c) == 0 ? EPSILON : VAR(_c);
    VAR(_cl) = VAR(_cl) == 0 ? EPSILON : VAR(_cl);
    VAR(_cr) = VAR(_cr) == 0 ? EPSILON : VAR(_cr);
    VAR(_cl) = VAR(_c) * VAR(_cl);
    VAR(_cr) = VAR(_c) + (VAR(_c) * VAR(_cr));

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // boarders2 by Xyrus02, http://xyrus02.deviantart.com/art/Boarders2-plugin-for-Apophysis-173427128
    double roundX = rint(FTx);
    double roundY = rint(FTy);
    double offsetX = FTx - roundX;
    double offsetY = FTy - roundY;
    if (GOODRAND_01() >= VAR(_cr)) {
      FPx += VVAR * (offsetX * VAR(_c) + roundX);
      FPy += VVAR * (offsetY * VAR(_c) + roundY);
    } else {
      if (fabs(offsetX) >= fabs(offsetY)) {
        if (offsetX >= 0.0) {
          FPx += VVAR * (offsetX * VAR(_c) + roundX + VAR(_cl));
          FPy += VVAR * (offsetY * VAR(_c) + roundY + VAR(_cl) * offsetY / offsetX);
        } else {
          FPx += VVAR * (offsetX * VAR(_c) + roundX - VAR(_cl));
          FPy += VVAR * (offsetY * VAR(_c) + roundY - VAR(_cl) * offsetY / offsetX);
        }
      } else {
        if (offsetY >= 0.0) {
          FPy += VVAR * (offsetY * VAR(_c) + roundY + VAR(_cl));
          FPx += VVAR * (offsetX * VAR(_c) + roundX + offsetX / offsetY * VAR(_cl));
        } else {
          FPy += VVAR * (offsetY * VAR(_c) + roundY - VAR(_cl));
          FPx += VVAR * (offsetX * VAR(_c) + roundX - offsetX / offsetY * VAR(_cl));
        }
      }
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
// public class Boarders2Func extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_C = "c";
//   private static final String PARAM_LEFT = "left";
//   private static final String PARAM_RIGHT = "right";
//   private static final String[] paramNames = {PARAM_C, PARAM_LEFT, PARAM_RIGHT};
// 
//   private double c = 0.4;
//   private double left = 0.65;
//   private double right = 0.35;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // boarders2 by Xyrus02, http://xyrus02.deviantart.com/art/Boarders2-plugin-for-Apophysis-173427128
//     double roundX = rint(pAffineTP.x);
//     double roundY = rint(pAffineTP.y);
//     double offsetX = pAffineTP.x - roundX;
//     double offsetY = pAffineTP.y - roundY;
//     if (pContext.random() >= _cr) {
//       pVarTP.x += pAmount * (offsetX * _c + roundX);
//       pVarTP.y += pAmount * (offsetY * _c + roundY);
//     } else {
//       if (fabs(offsetX) >= fabs(offsetY)) {
//         if (offsetX >= 0.0) {
//           pVarTP.x += pAmount * (offsetX * _c + roundX + _cl);
//           pVarTP.y += pAmount * (offsetY * _c + roundY + _cl * offsetY / offsetX);
//         } else {
//           pVarTP.x += pAmount * (offsetX * _c + roundX - _cl);
//           pVarTP.y += pAmount * (offsetY * _c + roundY - _cl * offsetY / offsetX);
//         }
//       } else {
//         if (offsetY >= 0.0) {
//           pVarTP.y += pAmount * (offsetY * _c + roundY + _cl);
//           pVarTP.x += pAmount * (offsetX * _c + roundX + offsetX / offsetY * _cl);
//         } else {
//           pVarTP.y += pAmount * (offsetY * _c + roundY - _cl);
//           pVarTP.x += pAmount * (offsetX * _c + roundX - offsetX / offsetY * _cl);
//         }
//       }
//     }
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
//     return new Object[]{c, left, right};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_C.equalsIgnoreCase(pName))
//       c = pValue;
//     else if (PARAM_LEFT.equalsIgnoreCase(pName))
//       left = pValue;
//     else if (PARAM_RIGHT.equalsIgnoreCase(pName))
//       right = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "boarders2";
//   }
// 
//   private double _c, _cl, _cr;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _c = fabs(c);
//     _cl = fabs(left);
//     _cr = fabs(right);
//     _c = _c == 0 ? EPSILON : _c;
//     _cl = _cl == 0 ? EPSILON : _cl;
//     _cr = _cr == 0 ? EPSILON : _cr;
//     _cl = _c * _cl;
//     _cr = _c + (_c * _cr);
//   }
// 
// }
// 
