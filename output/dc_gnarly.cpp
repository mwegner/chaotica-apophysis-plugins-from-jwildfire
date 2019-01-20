#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: dc_gnarly

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/DCGnarlyFunc.java

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
	int mode;
	double scalex;
	double scaley;
	double freqx1;
	double freqy1;
	double freqx2;
	double freqy2;
	double freqx3;
	double freqy3;
	int dc;
	double color1;
	double color2;
	double fmag;
	double distort;
	double blur;
	double scale_z;
	double offset_z;
	int reset_z;
	double _gauss_rnd[6];
	int _gauss_N;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "dc_gnarly_"
#include "plugin.h"

APO_PLUGIN("dc_gnarly");
APO_VARIABLES(
	VAR_INTEGER(mode, 1),
	VAR_REAL(scalex, 0.05),
	VAR_REAL(scaley, 0.05),
	VAR_REAL(freqx1, 3.5),
	VAR_REAL(freqy1, 3.5),
	VAR_REAL(freqx2, 2),
	VAR_REAL(freqy2, 2),
	VAR_REAL(freqx3, 5),
	VAR_REAL(freqy3, 5),
	VAR_INTEGER(dc, 1),
	VAR_REAL(color1, 5),
	VAR_REAL(color2, 5),
	VAR_REAL(fmag, 1),
	VAR_REAL(distort, 0.0),
	VAR_REAL(blur, 5.0),
	VAR_REAL(scale_z, 0.0),
	VAR_REAL(offset_z, 0.0),
	VAR_INTEGER(reset_z, 0),

);



int PluginVarPrepare(Variation* vp)
{


    VAR(_gauss_rnd)[0] = GOODRAND_01();
    VAR(_gauss_rnd)[1] = GOODRAND_01();
    VAR(_gauss_rnd)[2] = GOODRAND_01();
    VAR(_gauss_rnd)[3] = GOODRAND_01();
    VAR(_gauss_rnd)[4] = GOODRAND_01();
    VAR(_gauss_rnd)[5] = GOODRAND_01();
    VAR(_gauss_N) = 0;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // dc_gnarly by Brad Stefanov and Rick Sidwell
    // uses techniques and formulas by Tatyana Zabanova, Georg Kiehne, Clifford Pickover, and Mark Townsend

    double x0 = FTx;
    double y0 = FTy;

    if (VAR(blur) > 0) {
      double r = GOODRAND_01() * 2 * M_PI;
      double sina = sin(r);
      double cosa = cos(r);
      r = VAR(blur) * (VAR(_gauss_rnd)[0] + VAR(_gauss_rnd)[1] + VAR(_gauss_rnd)[2] + VAR(_gauss_rnd)[3] + VAR(_gauss_rnd)[4] + VAR(_gauss_rnd)[5] - 3);
      VAR(_gauss_rnd)[VAR(_gauss_N)] = GOODRAND_01();
      VAR(_gauss_N) = (VAR(_gauss_N) + 1) & 5;

      x0 += r * cosa;
      y0 += r * sina;
    } else if (VAR(blur) < 0) {
      x0 += GOODRAND_01() * VAR(blur) * 2 - VAR(blur);
      y0 += GOODRAND_01() * VAR(blur) * 2 - VAR(blur);
    }

    double x1, y1;
    switch (VAR(mode)) {
      case 1:
        x1 = cos(VAR(freqx1) * y0 + sin(VAR(freqx2) * (y0 + sin(VAR(freqx3) * y0)))) * VAR(scalex);
        y1 = cos(VAR(freqy1) * x0 + sin(VAR(freqy2) * (x0 + sin(VAR(freqy3) * x0)))) * VAR(scaley);
        break;
      case 2:
        x1 = sin(VAR(freqx1) * y0 + sin(VAR(freqx2) * (y0 + cos(VAR(freqx3) * y0)))) * VAR(scalex);
        y1 = sin(VAR(freqy1) * x0 + sin(VAR(freqy2) * (x0 + cos(VAR(freqy3) * x0)))) * VAR(scaley);
        break;
      case 3:
        x1 = cos(VAR(freqx1) * y0 + sin(VAR(freqx2) * (x0 + sin(VAR(freqx3) * y0)))) * VAR(scalex);
        y1 = cos(VAR(freqy1) * x0 + sin(VAR(freqy2) * (y0 + sin(VAR(freqy3) * x0)))) * VAR(scaley);
        break;
      case 4:
        x1 = sin(VAR(freqx1) * y0 + sin(sqrt(fabs(VAR(freqx2) * (y0 + cos(VAR(freqx3) * y0)))))) * VAR(scalex);
        y1 = sin(VAR(freqy1) * x0 + sin(sqrt(fabs(VAR(freqy2) * (x0 + cos(VAR(freqy3) * x0)))))) * VAR(scaley);
        break;
      case 5:
        x1 = cos(VAR(freqx1) * y0 + asinh(VAR(freqx2) * (y0 + sin(VAR(freqx3) * y0)))) * VAR(scalex);
        y1 = cos(VAR(freqy1) * x0 + asinh(VAR(freqy2) * (x0 + sin(VAR(freqy3) * x0)))) * VAR(scaley);
        break;
      case 6:
        x1 = cos(VAR(freqx1) * y0 + tan(VAR(freqx2) * (y0 + sin(VAR(freqx3) * y0)))) * VAR(scalex);
        y1 = cos(VAR(freqy1) * x0 + tan(VAR(freqy2) * (x0 + sin(VAR(freqy3) * x0)))) * VAR(scaley);
        break;
      case 7:
        x1 = sin(VAR(freqx1) * y0 + sin(sqr(VAR(freqx2) * (y0 + cos(VAR(freqx3) * y0))))) * VAR(scalex);
        y1 = sin(VAR(freqy1) * x0 + sin(sqr(VAR(freqy2) * (x0 + cos(VAR(freqy3) * x0))))) * VAR(scaley);
        break;
      case 8:
        x1 = sin(VAR(freqx1) * y0 + sin(sqr(VAR(freqx2) * (x0 + cos(VAR(freqx3) * y0))))) * VAR(scalex);
        y1 = sin(VAR(freqy1) * x0 + sin(sqr(VAR(freqy2) * (y0 + cos(VAR(freqy3) * x0))))) * VAR(scaley);
        break;
      default:
        x1 = sin(VAR(freqx1) * y0) * VAR(scalex);
        y1 = sin(VAR(freqy1) * x0) * VAR(scaley);
        break;
    }

    double s1 = log(sqrt(sqr(x1) + sqr(y1))) * VAR(distort);

    FPx += VVAR * (x0 + x1) / 2;
    FPy += VVAR * (y0 + y1) / 2;

    if (VAR(dc) != 0) {
      TC = fmod(fabs(cos(x0 + x1 * VAR(color1) + s1) + sin(y0 + y1 * VAR(color2) + s1)), VAR(fmag));
    }

    double dz = TC * VAR(scale_z) + VAR(offset_z);
    if (VAR(reset_z) > 0) {
      FPz = dz;
    } else {
      FPz += dz;
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
// public class DCGnarlyFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_MODE = "mode";
//   private static final String PARAM_SCALEX = "scalex";
//   private static final String PARAM_SCALEY = "scaley";
//   private static final String PARAM_FREQX1 = "freqx1";
//   private static final String PARAM_FREQY1 = "freqy1";
//   private static final String PARAM_FREQX2 = "freqx2";
//   private static final String PARAM_FREQY2 = "freqy2";
//   private static final String PARAM_FREQX3 = "freqx3";
//   private static final String PARAM_FREQY3 = "freqy3";
//   private static final String PARAM_DC = "dc";
//   private static final String PARAM_COLOR1 = "color1";
//   private static final String PARAM_COLOR2 = "color2";
//   private static final String PARAM_FMAG = "fmag";
//   private static final String PARAM_DISTORT = "distort";
//   private static final String PARAM_BLUR = "blur";
//   private static final String PARAM_SCALEZ = "scale_z";
//   private static final String PARAM_OFFSETZ = "offset_z";
//   private static final String PARAM_RESETZ = "reset_z";
// 
//   private static final String[] paramNames = {PARAM_MODE, PARAM_SCALEX, PARAM_SCALEY, PARAM_FREQX1, PARAM_FREQY1,
//           PARAM_FREQX2, PARAM_FREQY2, PARAM_FREQX3, PARAM_FREQY3, PARAM_DC, PARAM_COLOR1, PARAM_COLOR2,
//           PARAM_FMAG, PARAM_DISTORT, PARAM_BLUR, PARAM_SCALEZ, PARAM_OFFSETZ, PARAM_RESETZ};
// 
//   private int mode = 1;
//   private double scalex = 0.05;
//   private double scaley = 0.05;
//   private double freqx1 = 3.5;
//   private double freqy1 = 3.5;
//   private double freqx2 = 2;
//   private double freqy2 = 2;
//   private double freqx3 = 5;
//   private double freqy3 = 5;
//   private int dc = 1;
//   private double color1 = 5;
//   private double color2 = 5;
//   private double fmag = 1;
//   private double distort = 0.0;
//   private double blur = 5.0;
//   private double scale_z = 0.0;
//   private double offset_z = 0.0;
//   private int reset_z = 0;
// 
//   private final double gauss_rnd[] = new double[6];
//   private int gauss_N;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // dc_gnarly by Brad Stefanov and Rick Sidwell
//     // uses techniques and formulas by Tatyana Zabanova, Georg Kiehne, Clifford Pickover, and Mark Townsend
// 
//     double x0 = pAffineTP.x;
//     double y0 = pAffineTP.y;
// 
//     if (blur > 0) {
//       double r = pContext.random() * 2 * M_PI;
//       double sina = sin(r);
//       double cosa = cos(r);
//       r = blur * (gauss_rnd[0] + gauss_rnd[1] + gauss_rnd[2] + gauss_rnd[3] + gauss_rnd[4] + gauss_rnd[5] - 3);
//       gauss_rnd[gauss_N] = pContext.random();
//       gauss_N = (gauss_N + 1) & 5;
// 
//       x0 += r * cosa;
//       y0 += r * sina;
//     } else if (blur < 0) {
//       x0 += pContext.random() * blur * 2 - blur;
//       y0 += pContext.random() * blur * 2 - blur;
//     }
// 
//     double x1, y1;
//     switch (mode) {
//       case 1:
//         x1 = cos(freqx1 * y0 + sin(freqx2 * (y0 + sin(freqx3 * y0)))) * scalex;
//         y1 = cos(freqy1 * x0 + sin(freqy2 * (x0 + sin(freqy3 * x0)))) * scaley;
//         break;
//       case 2:
//         x1 = sin(freqx1 * y0 + sin(freqx2 * (y0 + cos(freqx3 * y0)))) * scalex;
//         y1 = sin(freqy1 * x0 + sin(freqy2 * (x0 + cos(freqy3 * x0)))) * scaley;
//         break;
//       case 3:
//         x1 = cos(freqx1 * y0 + sin(freqx2 * (x0 + sin(freqx3 * y0)))) * scalex;
//         y1 = cos(freqy1 * x0 + sin(freqy2 * (y0 + sin(freqy3 * x0)))) * scaley;
//         break;
//       case 4:
//         x1 = sin(freqx1 * y0 + sin(sqrt(fabs(freqx2 * (y0 + cos(freqx3 * y0)))))) * scalex;
//         y1 = sin(freqy1 * x0 + sin(sqrt(fabs(freqy2 * (x0 + cos(freqy3 * x0)))))) * scaley;
//         break;
//       case 5:
//         x1 = cos(freqx1 * y0 + asinh(freqx2 * (y0 + sin(freqx3 * y0)))) * scalex;
//         y1 = cos(freqy1 * x0 + asinh(freqy2 * (x0 + sin(freqy3 * x0)))) * scaley;
//         break;
//       case 6:
//         x1 = cos(freqx1 * y0 + tan(freqx2 * (y0 + sin(freqx3 * y0)))) * scalex;
//         y1 = cos(freqy1 * x0 + tan(freqy2 * (x0 + sin(freqy3 * x0)))) * scaley;
//         break;
//       case 7:
//         x1 = sin(freqx1 * y0 + sin(sqr(freqx2 * (y0 + cos(freqx3 * y0))))) * scalex;
//         y1 = sin(freqy1 * x0 + sin(sqr(freqy2 * (x0 + cos(freqy3 * x0))))) * scaley;
//         break;
//       case 8:
//         x1 = sin(freqx1 * y0 + sin(sqr(freqx2 * (x0 + cos(freqx3 * y0))))) * scalex;
//         y1 = sin(freqy1 * x0 + sin(sqr(freqy2 * (y0 + cos(freqy3 * x0))))) * scaley;
//         break;
//       default:
//         x1 = sin(freqx1 * y0) * scalex;
//         y1 = sin(freqy1 * x0) * scaley;
//         break;
//     }
// 
//     double s1 = log(sqrt(sqr(x1) + sqr(y1))) * distort;
// 
//     pVarTP.x += pAmount * (x0 + x1) / 2;
//     pVarTP.y += pAmount * (y0 + y1) / 2;
// 
//     if (dc != 0) {
//       pVarTP.color = fmod(fabs(cos(x0 + x1 * color1 + s1) + sin(y0 + y1 * color2 + s1)), fmag);
//     }
// 
//     double dz = pVarTP.color * scale_z + offset_z;
//     if (reset_z > 0) {
//       pVarTP.z = dz;
//     } else {
//       pVarTP.z += dz;
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
//     return new Object[]{mode, scalex, scaley, freqx1, freqy1, freqx2, freqy2, freqx3, freqy3,
//             dc, color1, color2, fmag, distort, blur, scale_z, offset_z, reset_z};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_MODE.equalsIgnoreCase(pName))
//       mode = Tools.limitValue(Tools.FTOI(pValue), 0, 8);
//     else if (PARAM_SCALEX.equalsIgnoreCase(pName))
//       scalex = pValue;
//     else if (PARAM_SCALEY.equalsIgnoreCase(pName))
//       scaley = pValue;
//     else if (PARAM_FREQX1.equalsIgnoreCase(pName))
//       freqx1 = pValue;
//     else if (PARAM_FREQY1.equalsIgnoreCase(pName))
//       freqy1 = pValue;
//     else if (PARAM_FREQX2.equalsIgnoreCase(pName))
//       freqx2 = pValue;
//     else if (PARAM_FREQY2.equalsIgnoreCase(pName))
//       freqy2 = pValue;
//     else if (PARAM_FREQX3.equalsIgnoreCase(pName))
//       freqx3 = pValue;
//     else if (PARAM_FREQY3.equalsIgnoreCase(pName))
//       freqy3 = pValue;
//     else if (PARAM_DC.equalsIgnoreCase(pName))
//       dc = Tools.limitValue(Tools.FTOI(pValue), 0, 1);
//     else if (PARAM_COLOR1.equalsIgnoreCase(pName))
//       color1 = pValue;
//     else if (PARAM_COLOR2.equalsIgnoreCase(pName))
//       color2 = pValue;
//     else if (PARAM_FMAG.equalsIgnoreCase(pName))
//       fmag = Tools.limitValue(pValue, 0.05, 1);
//     else if (PARAM_DISTORT.equalsIgnoreCase(pName))
//       distort = pValue;
//     else if (PARAM_BLUR.equalsIgnoreCase(pName))
//       blur = pValue;
//     else if (PARAM_SCALEZ.equalsIgnoreCase(pName))
//       scale_z = pValue;
//     else if (PARAM_OFFSETZ.equalsIgnoreCase(pName))
//       offset_z = pValue;
//     else if (PARAM_RESETZ.equalsIgnoreCase(pName))
//       reset_z = Tools.limitValue(Tools.FTOI(pValue), 0, 1);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "dc_gnarly";
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
// 
// 
//     gauss_rnd[0] = pContext.random();
//     gauss_rnd[1] = pContext.random();
//     gauss_rnd[2] = pContext.random();
//     gauss_rnd[3] = pContext.random();
//     gauss_rnd[4] = pContext.random();
//     gauss_rnd[5] = pContext.random();
//     gauss_N = 0;
//   }
// 
//   public static double asinh(double x) {
//     return log(x + sqrt(x * x + 1.0));
//   }
// 
// }
// 
