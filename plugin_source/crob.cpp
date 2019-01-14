/*
    Apophysis Plugin: crob

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CrobFunc.java

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
	double left;
	double top;
	double right;
	double bottom;
	int blur;
	double ratioBlur;
	double directBlur;
	double _top_border;
	double _bottom_border;
	double _left_border;
	double _right_border;
	double _xInterval;
	double _yInterval;
	double _xInt_2;
	double _yInt_2;
	double _minInt_2;
	double _x0;
	double _y0;
	double _x0c;
	double _y0c;
	double _setProb;
	double _setProbH;
	double _setProbQ;
	double _setProbTQ;
	double _setCompProb;
	double _setCompProbH;
	double _setCompProbQ;
	double _setCompProbTQ;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "crob_"
#include "plugin.h"

APO_PLUGIN("crob");
APO_VARIABLES(
	VAR_REAL(left, -1.0),
	VAR_REAL(top, -1.0),
	VAR_REAL(right, 1.0),
	VAR_REAL(bottom, 1.0),
	VAR_INTEGER(blur, 1),
	VAR_REAL(ratioBlur, 0.05),
	VAR_REAL(directBlur, 2.0),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
    double tmp;

    // ***** Preventing bad inputs *****
    if (VAR(top) > VAR(bottom)) {
      tmp = VAR(top);
      VAR(top) = VAR(bottom);
      VAR(bottom) = tmp;
    }
    if (VAR(top) == VAR(bottom)) {
      VAR(top) = -1.0;
      VAR(bottom) = 1.0;
    }
    if (VAR(left) > VAR(right)) {
      tmp = VAR(left);
      VAR(left) = VAR(right);
      VAR(right) = tmp;
    }
    if (VAR(left) == VAR(right)) {
      VAR(left) = -1.0;
      VAR(right) = 1.0;
    }
    if (VAR(directBlur) < 0.0) VAR(directBlur) = 0.0;

    // ***** Initializing intervals *****
    if (VAR(blur) != 0) VAR(blur) = 1;
    VAR(_xInterval) = fabs(VAR(right) - VAR(left));
    VAR(_yInterval) = fabs(VAR(bottom) - VAR(top));
    VAR(_xInt_2) = VAR(_xInterval) / 2.0;
    VAR(_yInt_2) = VAR(_yInterval) / 2.0;
    VAR(_minInt_2) = (VAR(_xInt_2) > VAR(_yInt_2)) ? VAR(_yInt_2) : VAR(_xInt_2);
    VAR(_x0) = VAR(right) - VAR(_xInt_2);
    VAR(_y0) = VAR(top) + VAR(_yInt_2);

    // ***** Initializing reference point *****
    if (VAR(_xInt_2) > VAR(_yInt_2)) {
      VAR(_x0c) = VAR(right) - VAR(_minInt_2);
      VAR(_y0c) = VAR(_y0);
    } else if (VAR(_xInt_2) < VAR(_yInt_2)) {
      VAR(_x0c) = VAR(_x0);
      VAR(_y0c) = VAR(top) + VAR(_minInt_2);
    } else {
      VAR(_x0c) = VAR(_x0);
      VAR(_y0c) = VAR(_y0);
    }

    // ***** Initializing probabilities *****
    VAR(_setProb) = VAR(_yInterval) / (VAR(_xInterval) + VAR(_yInterval));
    VAR(_setProbQ) = 0.25 * VAR(_setProb);
    VAR(_setProbH) = 0.50 * VAR(_setProb);
    VAR(_setProbTQ) = 0.75 * VAR(_setProb);
    VAR(_setCompProb) = 1.0 - VAR(_setProb);
    VAR(_setCompProbQ) = VAR(_setProb) + 0.25 * VAR(_setCompProb);
    VAR(_setCompProbH) = VAR(_setProb) + 0.50 * VAR(_setCompProb);
    VAR(_setCompProbTQ) = VAR(_setProb) + 0.75 * VAR(_setCompProb);

    // ***** Defining inner area *****
    if (VAR(blur) == 0) {
      VAR(_top_border) = VAR(top);
      VAR(_bottom_border) = VAR(bottom);
      VAR(_left_border) = VAR(left);
      VAR(_right_border) = VAR(right);
    } else {
      VAR(_top_border) = VAR(top) + VAR(_minInt_2) * VAR(ratioBlur);
      VAR(_bottom_border) = VAR(bottom) - VAR(_minInt_2) * VAR(ratioBlur);
      VAR(_left_border) = VAR(left) + VAR(_minInt_2) * VAR(ratioBlur);
      VAR(_right_border) = VAR(right) - VAR(_minInt_2) * VAR(ratioBlur);
    }

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // crob by FractalDesire, https://fractaldesire.deviantart.com/art/crob-plugin-260173724

    double gradTmp, secTmp;
    double xTmp = FTx;
    double yTmp = FTy;

    if ((FTx < VAR(_left_border)) || (FTx > VAR(_right_border)) || (FTy < VAR(_top_border)) || (FTy > VAR(_bottom_border))) {
      //***** Case: no edge *****
      if (VAR(blur) == 0) {
        xTmp = 0;
        yTmp = 0;
      }
      //***** Case: with edge *****
      else {
        secTmp = GOODRAND_01();

        // ***** Drawing VAR(top) and VAR(bottom) *****
        if (secTmp < VAR(_setProb)) {
          do {
            yTmp = VAR(top) + GOODRAND_01() * VAR(_yInt_2);
            xTmp = VAR(right) - pow(GOODRAND_01(), VAR(directBlur)) * VAR(ratioBlur) * VAR(_minInt_2);
            gradTmp = (yTmp - VAR(_y0c)) / (xTmp - VAR(_x0c));
          } while (gradTmp < -1.0);

          if (secTmp < VAR(_setProbH)) xTmp = VAR(left) + VAR(right) - xTmp;
          if ((secTmp > VAR(_setProbQ)) && (secTmp < VAR(_setProbTQ))) yTmp = VAR(bottom) + VAR(top) - yTmp;
        }

        // ***** Drawing VAR(left) and VAR(right) *****
        else {
          do {
            xTmp = VAR(right) - GOODRAND_01() * VAR(_xInt_2);
            yTmp = VAR(top) + pow(GOODRAND_01(), VAR(directBlur)) * VAR(ratioBlur) * VAR(_minInt_2);
            gradTmp = (yTmp - VAR(_y0c)) / (xTmp - VAR(_x0c));
          } while ((gradTmp <= 0.0) && (gradTmp > -1.0));

          if (secTmp > VAR(_setCompProbH)) yTmp = VAR(bottom) + VAR(top) - yTmp;
          if ((secTmp > VAR(_setCompProbQ)) && (secTmp < VAR(_setCompProbTQ))) xTmp = VAR(left) + VAR(right) - xTmp;
        }
      }
    }

    FPx += xTmp;
    FPy += yTmp;
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
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.fabs;
// import static org.jwildfire.base.mathlib.MathLib.pow;
// 
// public class CrobFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_TOP = "top";
//   private static final String PARAM_BOTTOM = "bottom";
//   private static final String PARAM_LEFT = "left";
//   private static final String PARAM_RIGHT = "right";
//   private static final String PARAM_BLUR = "blur";
//   private static final String PARAM_RATIOBLUR = "ratioBlur";
//   private static final String PARAM_DIRECTBLUR = "directBlur";
// 
//   private static final String[] paramNames = {PARAM_TOP, PARAM_BOTTOM, PARAM_LEFT, PARAM_RIGHT, PARAM_BLUR, PARAM_RATIOBLUR, PARAM_DIRECTBLUR};
// 
//   private double left = -1.0;
//   private double top = -1.0;
//   private double right = 1.0;
//   private double bottom = 1.0;
//   private int blur = 1;
//   private double ratioblur = 0.05;
//   private double directblur = 2.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // crob by FractalDesire, https://fractaldesire.deviantart.com/art/crob-plugin-260173724
// 
//     double gradTmp, secTmp;
//     double xTmp = pAffineTP.x;
//     double yTmp = pAffineTP.y;
// 
//     if ((pAffineTP.x < left_border) || (pAffineTP.x > right_border) || (pAffineTP.y < top_border) || (pAffineTP.y > bottom_border)) {
//       //***** Case: no edge *****
//       if (blur == 0) {
//         xTmp = 0;
//         yTmp = 0;
//       }
//       //***** Case: with edge *****
//       else {
//         secTmp = pContext.random();
// 
//         // ***** Drawing top and bottom *****
//         if (secTmp < setProb) {
//           do {
//             yTmp = top + pContext.random() * yInt_2;
//             xTmp = right - pow(pContext.random(), directblur) * ratioblur * minInt_2;
//             gradTmp = (yTmp - y0c) / (xTmp - x0c);
//           } while (gradTmp < -1.0);
// 
//           if (secTmp < setProbH) xTmp = left + right - xTmp;
//           if ((secTmp > setProbQ) && (secTmp < setProbTQ)) yTmp = bottom + top - yTmp;
//         }
// 
//         // ***** Drawing left and right *****
//         else {
//           do {
//             xTmp = right - pContext.random() * xInt_2;
//             yTmp = top + pow(pContext.random(), directblur) * ratioblur * minInt_2;
//             gradTmp = (yTmp - y0c) / (xTmp - x0c);
//           } while ((gradTmp <= 0.0) && (gradTmp > -1.0));
// 
//           if (secTmp > setCompProbH) yTmp = bottom + top - yTmp;
//           if ((secTmp > setCompProbQ) && (secTmp < setCompProbTQ)) xTmp = left + right - xTmp;
//         }
//       }
//     }
// 
//     pVarTP.x += xTmp;
//     pVarTP.y += yTmp;
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
//     return new Object[]{top, bottom, left, right, blur, ratioblur, directblur};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_LEFT.equalsIgnoreCase(pName))
//       left = pValue;
//     else if (PARAM_RIGHT.equalsIgnoreCase(pName))
//       right = pValue;
//     else if (PARAM_TOP.equalsIgnoreCase(pName))
//       top = pValue;
//     else if (PARAM_BOTTOM.equalsIgnoreCase(pName))
//       bottom = pValue;
//     else if (PARAM_BLUR.equalsIgnoreCase(pName))
//       blur = Tools.FTOI(pValue);
//     else if (PARAM_RATIOBLUR.equalsIgnoreCase(pName))
//       ratioblur = pValue;
//     else if (PARAM_DIRECTBLUR.equalsIgnoreCase(pName))
//       directblur = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "crob";
//   }
// 
//   private double top_border, bottom_border, left_border, right_border;
//   private double xInterval, yInterval, xInt_2, yInt_2, minInt_2;
//   private double x0, y0, x0c, y0c;
//   private double setProb, setProbH, setProbQ, setProbTQ, setCompProb, setCompProbH, setCompProbQ, setCompProbTQ;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     double tmp;
// 
//     // ***** Preventing bad inputs *****
//     if (top > bottom) {
//       tmp = top;
//       top = bottom;
//       bottom = tmp;
//     }
//     if (top == bottom) {
//       top = -1.0;
//       bottom = 1.0;
//     }
//     if (left > right) {
//       tmp = left;
//       left = right;
//       right = tmp;
//     }
//     if (left == right) {
//       left = -1.0;
//       right = 1.0;
//     }
//     if (directblur < 0.0) directblur = 0.0;
// 
//     // ***** Initializing intervals *****
//     if (blur != 0) blur = 1;
//     xInterval = fabs(right - left);
//     yInterval = fabs(bottom - top);
//     xInt_2 = xInterval / 2.0;
//     yInt_2 = yInterval / 2.0;
//     minInt_2 = (xInt_2 > yInt_2) ? yInt_2 : xInt_2;
//     x0 = right - xInt_2;
//     y0 = top + yInt_2;
// 
//     // ***** Initializing reference point *****
//     if (xInt_2 > yInt_2) {
//       x0c = right - minInt_2;
//       y0c = y0;
//     } else if (xInt_2 < yInt_2) {
//       x0c = x0;
//       y0c = top + minInt_2;
//     } else {
//       x0c = x0;
//       y0c = y0;
//     }
// 
//     // ***** Initializing probabilities *****
//     setProb = yInterval / (xInterval + yInterval);
//     setProbQ = 0.25 * setProb;
//     setProbH = 0.50 * setProb;
//     setProbTQ = 0.75 * setProb;
//     setCompProb = 1.0 - setProb;
//     setCompProbQ = setProb + 0.25 * setCompProb;
//     setCompProbH = setProb + 0.50 * setCompProb;
//     setCompProbTQ = setProb + 0.75 * setCompProb;
// 
//     // ***** Defining inner area *****
//     if (blur == 0) {
//       top_border = top;
//       bottom_border = bottom;
//       left_border = left;
//       right_border = right;
//     } else {
//       top_border = top + minInt_2 * ratioblur;
//       bottom_border = bottom - minInt_2 * ratioblur;
//       left_border = left + minInt_2 * ratioblur;
//       right_border = right - minInt_2 * ratioblur;
//     }
//   }
// 
// }
// 
