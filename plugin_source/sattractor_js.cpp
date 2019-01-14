/*
    Apophysis Plugin: sattractor_js

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/SattractorFunc.java

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
	double _a[13];
	double _b[13];
	int _m = 10;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "sattractor_js_"
#include "plugin.h"

APO_PLUGIN("sattractor_js");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
   VAR(_m) = 10;
    for (int i = 1; i <= VAR(_m); i++) {
      VAR(_a)[i] = cos(2.0 * M_PI * (double) i / (double) VAR(_m));
      VAR(_b)[i] = sin(2.0 * M_PI * (double) i / (double) VAR(_m));
    }

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    //              Hennon IFS Reference:
    //				http://paulbourke.net/fractals/henonattractor/roger18.c

    double x, y;

    int l = (int) (GOODRAND_01() * (double) VAR(_m)) + 1;

    if (GOODRAND_01() < 0.5) {
      x = FTx / 2.0 + VAR(_a)[l];
      y = FTy / 2.0 + VAR(_b)[l];
    } else {
      x = FTx * VAR(_a)[l] + FTy * VAR(_b)[l] + FTx * FTx * VAR(_b)[l];
      y = FTy * VAR(_a)[l] - FTx * VAR(_b)[l] + FTx * FTx * VAR(_a)[l];
    }
    x /= 2.0;
    y /= 2.0;

    FPx += x * VVAR;
    FPy += y * VVAR;

    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }



    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class SattractorFunc extends VariationFunc {
// 
//   /**
//    * Hennon IFS
//    *
//    * @author Jesus Sosa
//    * @date November 4, 2017
//    * based on a work of:
//    * http://paulbourke.net/fractals/peterdejong/
//    */
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_M = "m";
// 
//   private static final String[] paramNames = {PARAM_M};
// 
//   double[] a = new double[13];
//   double[] b = new double[13];
// 
//   int m = 10;
// 
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     for (int i = 1; i <= m; i++) {
//       a[i] = cos(2.0 * M_PI * (double) i / (double) m);
//       b[i] = sin(2.0 * M_PI * (double) i / (double) m);
//     }
//   }
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     //              Hennon IFS Reference:
//     //				http://paulbourke.net/fractals/henonattractor/roger18.c
// 
//     double x, y;
// 
//     int l = (int) (pContext.random() * (double) m) + 1;
// 
//     if (pContext.random() < 0.5) {
//       x = pAffineTP.x / 2.0 + a[l];
//       y = pAffineTP.y / 2.0 + b[l];
//     } else {
//       x = pAffineTP.x * a[l] + pAffineTP.y * b[l] + pAffineTP.x * pAffineTP.x * b[l];
//       y = pAffineTP.y * a[l] - pAffineTP.x * b[l] + pAffineTP.x * pAffineTP.x * a[l];
//     }
//     x /= 2.0;
//     y /= 2.0;
// 
//     pVarTP.x += x * pAmount;
//     pVarTP.y += y * pAmount;
// 
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
// 
//   }
// 
//   public String getName() {
//     return "sattractor_js";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   public Object[] getParameterValues() {
//     return new Object[]{m};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_M)) {
//       m = (int) pValue;
//       if (m < 2)
//         m = 2;
//       if (m > 12)
//         m = 12;
// 
//       for (int i = 1; i <= m; i++) {
//         a[i] = cos(2.0 * M_PI * (double) i / (double) m);
//         b[i] = sin(2.0 * M_PI * (double) i / (double) m);
//         //			    	  System.out.println("i , a[i] ,b[i] " + i + " , " + a[i] +" , "+ b[i]);
//       }
// 
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// }
