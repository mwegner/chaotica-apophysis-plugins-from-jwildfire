#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: colordomain

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ColorDomainFunc.java

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
	int _size = 1000;
	int _zoomIn = 1;
	int _zoomOut = 1;
	int _nIters = 1;
	double _re_min = 0.0; // -1.0
	double _re_max = 1.0;
	double _im_min = 0.0; // -1.0
	double _im_max = 1.0;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "colordomain_"
#include "plugin.h"

APO_PLUGIN("colordomain");
APO_VARIABLES(

);


void initOnce (Variation* vp, Layer pLayer, XForm pXForm, double pAmount) {

    super.initOnce(vp, pLayer, pXForm, VVAR);
    // store result to cache


    if (cf_runner == null) {
      compile(vp);
    }
}

boolean dynamicParameterExpansion (Variation* vp) {

    return true;
}

boolean dynamicParameterExpansion (Variation* vp, String pName) {

    // preset_id doesn't really expand parameters, but it changes them; this will make them refresh
    if (pName.equalsIgnoreCase(PARAM_RMIN)) {
      return true;
    } else if (pName.equalsIgnoreCase(PARAM_RMAX)) {
      return true;
    } else if (PARAM_IMIN.equalsIgnoreCase(pName))
      return true;
    else if (pName.equalsIgnoreCase(PARAM_IMAX)) {
      return true;
    } else if (pName.equalsIgnoreCase(PARAM_ZOOMIN)) {
      return true;
    } else if (pName.equalsIgnoreCase(PARAM_ZOOMOUT)) {
      return true;
    } else
      return false;
}

void compile (Variation* vp) {

    try {
      cf_runner = ComplexFuncRunner.compile(vp, code);
    } catch (Throwable ex) {
      System.out.println("##############################################################");
      System.out.println(ex.getMessage());
      System.out.println("##############################################################");
      System.out.println(code);
      System.out.println("##############################################################");
    }
}

void validate (Variation* vp) {

    try {
      if (code != null) {
        ComplexFuncRunner.compile(vp, code);
      }
    } catch (Throwable ex) {
      throw new RuntimeException(ex);
    }
}

void setRessource (Variation* vp, String pName, byte[] pValue) {

    if (RESSOURCE_CODE.equalsIgnoreCase(pName)) {
      code = pValue != null ? new String(pValue) : "";
    } else
      throw new IllegalArgumentException(pName);
}


int PluginVarPrepare(Variation* vp)
{
   VAR(_size) = 1000;
   VAR(_zoomIn) = 1;
   VAR(_zoomOut) = 1;
   VAR(_nIters) = 1;
   VAR(_re_min) = 0.0;
   VAR(_re_max) = 1.0;
   VAR(_im_min) = 0.0;
   VAR(_im_max) = 1.0;
    if (cf_runner == null) {
      compile(vp);
    }

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{

    int j = (int) (GOODRAND_01() * VAR(_size));
    int i = (int) (GOODRAND_01() * VAR(_size));


    double im = VAR(_im_max) - ((VAR(_im_max) - VAR(_im_min)) * (double) j) / (double) (VAR(_size) - 1);
    double re = VAR(_re_min) - ((VAR(_re_min) - VAR(_re_max)) * (double) i) / (double) (VAR(_size) - 1);

    Complex c = new Complex(re, im);

    Complex v = c;
    for (int k = 0; k < VAR(_nIters); k++) {
      v = cf_runner.f(v);
    }

    double a;
    for (a = v.arg(); a < 0.0D; a += 6.2831853071795862D) ;
    a /= 6.2831853071795862D;
    double m = v.mod();
    double ranges = 0.0D;
    double rangee;
    for (rangee = 1.0D; m > rangee; rangee *= 2.7182818284590451D)
      ranges = rangee;

    double k = (m - ranges) / (rangee - ranges);
    double sat = k >= 0.5D ? 1.0D - (k - 0.5D) * 2D : k * 2D;
    sat = 1.0D - pow(1.0D - sat, 3D);
    sat = 0.40000000000000002D + sat * 0.59999999999999998D;
    double val = k >= 0.5D ? 1.0D - (k - 0.5D) * 2D : k * 2D;
    val = 1.0D - val;
    val = 1.0D - pow(1.0D - val, 3D);
    val = 0.59999999999999998D + val * 0.40000000000000002D;
    int theColor[] = SetHSV(a, sat, val);


    pVarTP.rgbColor = true;
    ;
    pVarTP.redColor = theColor[0];
    pVarTP.greenColor = theColor[1];
    pVarTP.blueColor = theColor[2];

    FPx += VVAR * ((double) (i) / VAR(_size) - 0.5);
    FPy += VVAR * ((double) (j) / VAR(_size) - 0.5);

    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }



    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// 
// import js.colordomain.Complex;
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// 
// public class ColorDomainFunc extends VariationFunc {
// 
//   /*
//    * Variation : colordomain
//    *
//    * Autor: Jesus Sosa
//    * Date: September 14, 2018
//    * Reference http://users.mai.liu.se/hanlu09/complex/domain_coloring.html
//    *      and  https://gandhiviswanathan.wordpress.com/2014/10/07/domain-coloring-for-visualizing-complex-functions/
//    */
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_SIZE = "size";
//   private static final String PARAM_RMIN = "re_min";
//   private static final String PARAM_RMAX = "re_max";
//   private static final String PARAM_IMIN = "im_min";
//   private static final String PARAM_IMAX = "im_max";
//   private static final String PARAM_ZOOMIN = "zoomIn";
//   private static final String PARAM_ZOOMOUT = "zoomOut";
//   private static final String PARAM_ITERS = "nIters";
// 
//   private static final String[] paramNames = {PARAM_SIZE, PARAM_RMIN, PARAM_RMAX, PARAM_IMIN, PARAM_IMAX, PARAM_ZOOMIN, PARAM_ZOOMOUT, PARAM_ITERS};
// 
//   private static final String RESSOURCE_CODE = "code";
//   private static final String[] ressourceNames = {RESSOURCE_CODE};
// 
//   int size = 1000;
//   int zoomIn = 1;
//   int zoomOut = 1;
//   int nIters = 1;
// 
// 
//   double re_min = -1.0, re_max = 1.0;
//   double im_min = -1.0, im_max = 1.0;
// 
// 
//   ComplexFuncRunner cf_runner = null;
// 
//   private String code = "import js.colordomain.Complex;\r\n" +
//           "\r\n" +
//           "    public Complex f(Complex z){\r\n" +
//           "\r\n" +
//           "       Complex c=z.scale(3.1415926535897931D);\r\n" +
//           "\r\n" +
//           "         return c.sin().mul(c.sin());\r\n" +
//           "    }\r\n" +
//           "";
// 
// 
//   @Override
//   public void initOnce(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     super.initOnce(pContext, pLayer, pXForm, pAmount);
//     // store result to cache
// 
// 
//     if (cf_runner == null) {
//       compile();
//     }
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     if (cf_runner == null) {
//       compile();
//     }
//   }
// 
// 
//   public Complex f(Complex z) {
//     Complex one = new Complex(1.0D, 0.0D);
//     return one.div(z);
//   }
// 
//   public int[] SetHSV(double h, double s, double v) {
//     double r = 0.0D;
//     double g = 0.0D;
//     double b = 0.0D;
//     int color[] = new int[3];
//     if (s == 0.0D) {
//       r = g = b = v;
//     } else {
//       if (h == 1.0D)
//         h = 0.0D;
//       double z = Math.floor(h * 6D);
//       int i = (int) z;
//       double f = h * 6D - z;
//       double p = v * (1.0D - s);
//       double q = v * (1.0D - s * f);
//       double t = v * (1.0D - s * (1.0D - f));
//       switch (i) {
//         case 0: // '\0'
//           r = v;
//           g = t;
//           b = p;
//           break;
// 
//         case 1: // '\001'
//           r = q;
//           g = v;
//           b = p;
//           break;
// 
//         case 2: // '\002'
//           r = p;
//           g = v;
//           b = t;
//           break;
// 
//         case 3: // '\003'
//           r = p;
//           g = q;
//           b = v;
//           break;
// 
//         case 4: // '\004'
//           r = t;
//           g = p;
//           b = v;
//           break;
// 
//         case 5: // '\005'
//           r = v;
//           g = p;
//           b = q;
//           break;
//       }
//     }
//     int c = (int) (256D * r);
//     if (c > 255)
//       c = 255;
//     color[0] = c;
//     c = (int) (256D * g);
//     if (c > 255)
//       c = 255;
//     color[1] = c;
//     c = (int) (256D * b);
//     if (c > 255)
//       c = 255;
//     color[2] = c;
//     return color;
//   }
// 
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// 
//     int j = (int) (pContext.random() * size);
//     int i = (int) (pContext.random() * size);
// 
// 
//     double im = im_max - ((im_max - im_min) * (double) j) / (double) (size - 1);
//     double re = re_min - ((re_min - re_max) * (double) i) / (double) (size - 1);
// 
//     Complex c = new Complex(re, im);
// 
//     Complex v = c;
//     for (int k = 0; k < nIters; k++) {
//       v = cf_runner.f(v);
//     }
// 
//     double a;
//     for (a = v.arg(); a < 0.0D; a += 6.2831853071795862D) ;
//     a /= 6.2831853071795862D;
//     double m = v.mod();
//     double ranges = 0.0D;
//     double rangee;
//     for (rangee = 1.0D; m > rangee; rangee *= 2.7182818284590451D)
//       ranges = rangee;
// 
//     double k = (m - ranges) / (rangee - ranges);
//     double sat = k >= 0.5D ? 1.0D - (k - 0.5D) * 2D : k * 2D;
//     sat = 1.0D - Math.pow(1.0D - sat, 3D);
//     sat = 0.40000000000000002D + sat * 0.59999999999999998D;
//     double val = k >= 0.5D ? 1.0D - (k - 0.5D) * 2D : k * 2D;
//     val = 1.0D - val;
//     val = 1.0D - Math.pow(1.0D - val, 3D);
//     val = 0.59999999999999998D + val * 0.40000000000000002D;
//     int theColor[] = SetHSV(a, sat, val);
// 
// 
//     pVarTP.rgbColor = true;
//     ;
//     pVarTP.redColor = theColor[0];
//     pVarTP.greenColor = theColor[1];
//     pVarTP.blueColor = theColor[2];
// 
//     pVarTP.x += pAmount * ((double) (i) / size - 0.5);
//     pVarTP.y += pAmount * ((double) (j) / size - 0.5);
// 
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
// 
//   }
// 
//   public String getName() {
//     return "colordomain";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   public Object[] getParameterValues() {
//     return new Object[]{size, re_min, re_max, im_min, im_max, zoomIn, zoomOut, nIters};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_SIZE)) {
//       size = (int) Tools.limitValue(pValue, 100, 10000);
//     } else if (pName.equalsIgnoreCase(PARAM_RMIN)) {
//       re_min = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_RMAX)) {
//       re_max = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_IMIN)) {
//       im_min = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_IMAX)) {
//       im_max = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_ZOOMIN)) {
//       zoomIn = (int) Tools.limitValue(pValue, 1, 1);
//       double rrange = Math.abs(re_max - re_min);
//       double irange = Math.abs(im_max - im_min);
//       rrange /= 4D;
//       irange /= 4D;
//       im_max = (im_max - irange);
//       re_max = (re_max - rrange);
//       im_min = (im_min + irange);
//       re_min = (re_min + rrange);
//     } else if (pName.equalsIgnoreCase(PARAM_ZOOMOUT)) {
//       zoomOut = (int) Tools.limitValue(pValue, 1, 1);
//       double rrange = Math.abs(re_max - re_min);
//       double irange = Math.abs(im_max - im_min);
//       rrange /= 2D;
//       irange /= 2D;
//       re_max = (re_max + rrange);
//       re_min = (re_min - rrange);
//       im_max = (im_max + irange);
//       im_min = (im_min - irange);
//     } else if (pName.equalsIgnoreCase(PARAM_ITERS)) {
//       nIters = (int) Tools.limitValue(pValue, 1, 20);
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public boolean dynamicParameterExpansion() {
//     return true;
//   }
// 
//   @Override
//   public boolean dynamicParameterExpansion(String pName) {
//     // preset_id doesn't really expand parameters, but it changes them; this will make them refresh
//     if (pName.equalsIgnoreCase(PARAM_RMIN)) {
//       return true;
//     } else if (pName.equalsIgnoreCase(PARAM_RMAX)) {
//       return true;
//     } else if (PARAM_IMIN.equalsIgnoreCase(pName))
//       return true;
//     else if (pName.equalsIgnoreCase(PARAM_IMAX)) {
//       return true;
//     } else if (pName.equalsIgnoreCase(PARAM_ZOOMIN)) {
//       return true;
//     } else if (pName.equalsIgnoreCase(PARAM_ZOOMOUT)) {
//       return true;
//     } else
//       return false;
//   }
// 
// 
//   private void compile() {
//     try {
//       cf_runner = ComplexFuncRunner.compile(code);
//     } catch (Throwable ex) {
//       System.out.println("##############################################################");
//       System.out.println(ex.getMessage());
//       System.out.println("##############################################################");
//       System.out.println(code);
//       System.out.println("##############################################################");
//     }
//   }
// 
//   @Override
//   public void validate() {
//     try {
//       if (code != null) {
//         ComplexFuncRunner.compile(code);
//       }
//     } catch (Throwable ex) {
//       throw new RuntimeException(ex);
//     }
//   }
// 
//   @Override
//   public String[] getRessourceNames() {
//     return ressourceNames;
//   }
// 
//   @Override
//   public byte[][] getRessourceValues() {
//     return new byte[][]{(code != null ? code.getBytes() : null)};
//   }
// 
//   @Override
//   public RessourceType getRessourceType(String pName) {
//     if (pName.equals(RESSOURCE_CODE)) {
//       return RessourceType.JAVA_CODE;
//     } else {
//       return super.getRessourceType(pName);
//     }
//   }
// 
//   @Override
//   public void setRessource(String pName, byte[] pValue) {
//     if (RESSOURCE_CODE.equalsIgnoreCase(pName)) {
//       code = pValue != null ? new String(pValue) : "";
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// }
// 
