#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: circlecrop

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CircleCropFunc.java

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
	double radius;
	double x;
	double y;
	double scatter_area;
	int zero;
	double _cA;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "circlecrop_"
#include "plugin.h"

APO_PLUGIN("circlecrop");
APO_VARIABLES(
	VAR_REAL(radius, 1.0),
	VAR_REAL(x, 0.0),
	VAR_REAL(y, 0.0),
	VAR_REAL(scatter_area, 0.0),
	VAR_INTEGER(zero, 1),

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_cA) =  MAX(-1.0, MIN(VAR(scatter_area), 1.0));

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // circlecrop by Xyrus02, http://xyrus02.deviantart.com/art/CircleCrop-Plugins-185353309
    double x0 = VAR(x);
    double y0 = VAR(y);
    double cr = VAR(radius);
    double ca = VAR(_cA);
    double vv = VVAR;

    FTx -= x0;
    FTy -= y0;

    double rad = sqrt(FTx * FTx + FTy * FTy);
    double ang = atan2(FTy, FTx);
    double rdc = cr + (GOODRAND_01() * 0.5 * ca);

    bool esc = rad > cr;
    bool cr0 = VAR(zero) == 1;

    double s = sin(ang);
    double c = cos(ang);

    /* pVarTP.doHide = false; */
    if (cr0 && esc) {
      FPx = FPy = 0;
      /* pVarTP.doHide = true; */
    } else if (cr0 && !esc) {
      FPx += vv * FTx + x0;
      FPy += vv * FTy + y0;
    } else if (!cr0 && esc) {
      FPx += vv * rdc * c + x0;
      FPy += vv * rdc * s + y0;
    } else if (!cr0 && !esc) {
      FPx += vv * FTx + x0;
      FPy += vv * FTy + y0;
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
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class CircleCropFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_RADIUS = "radius";
//   private static final String PARAM_X = "x";
//   private static final String PARAM_Y = "y";
//   private static final String PARAM_SCATTER_AREA = "scatter_area";
//   private static final String PARAM_ZERO = "zero";
// 
//   private static final String[] paramNames = {PARAM_RADIUS, PARAM_X, PARAM_Y, PARAM_SCATTER_AREA, PARAM_ZERO};
// 
//   private double radius = 1.0;
//   private double x = 0.0;
//   private double y = 0.0;
//   private double scatter_area = 0.0;
//   private int zero = 1;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // circlecrop by Xyrus02, http://xyrus02.deviantart.com/art/CircleCrop-Plugins-185353309
//     double x0 = x;
//     double y0 = y;
//     double cr = radius;
//     double ca = cA;
//     double vv = pAmount;
// 
//     pAffineTP.x -= x0;
//     pAffineTP.y -= y0;
// 
//     double rad = sqrt(pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y);
//     double ang = atan2(pAffineTP.y, pAffineTP.x);
//     double rdc = cr + (pContext.random() * 0.5 * ca);
// 
//     boolean esc = rad > cr;
//     boolean cr0 = zero == 1;
// 
//     double s = sin(ang);
//     double c = cos(ang);
// 
//     pVarTP.doHide = false;
//     if (cr0 && esc) {
//       pVarTP.x = pVarTP.y = 0;
//       pVarTP.doHide = true;
//     } else if (cr0 && !esc) {
//       pVarTP.x += vv * pAffineTP.x + x0;
//       pVarTP.y += vv * pAffineTP.y + y0;
//     } else if (!cr0 && esc) {
//       pVarTP.x += vv * rdc * c + x0;
//       pVarTP.y += vv * rdc * s + y0;
//     } else if (!cr0 && !esc) {
//       pVarTP.x += vv * pAffineTP.x + x0;
//       pVarTP.y += vv * pAffineTP.y + y0;
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
//     return new Object[]{radius, x, y, scatter_area, zero};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_RADIUS.equalsIgnoreCase(pName))
//       radius = pValue;
//     else if (PARAM_X.equalsIgnoreCase(pName))
//       x = pValue;
//     else if (PARAM_Y.equalsIgnoreCase(pName))
//       y = pValue;
//     else if (PARAM_SCATTER_AREA.equalsIgnoreCase(pName))
//       scatter_area = pValue;
//     else if (PARAM_ZERO.equalsIgnoreCase(pName))
//       zero = Tools.FTOI(pValue);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "circlecrop";
//   }
// 
//   private double cA;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     cA = max(-1.0, min(scatter_area, 1.0));
//   }
// 
// }
// 
