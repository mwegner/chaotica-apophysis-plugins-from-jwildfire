#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: glsl_kaleidocomplex

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/GLSLKaleidoComplexFunc.java

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
	int Seed;
	int _resolutionX = 1000000;
	int _resolutionY; // resolutionX
	double _time = 0.0;
	int _iMax = 12;
	double _fc = 2.0;
	double _FR = 1.0;
	double _FG = 1.0;
	double _FB = 1.0;
	int _gradient;

} Variables;

#define APO_VARIABLE_PREFIX "glsl_kaleidocomplex_"
#include "plugin.h"

APO_PLUGIN("glsl_kaleidocomplex");
APO_VARIABLES(
	VAR_INTEGER(Seed, 10000)

);


double random (Variation* vp, double r1, double r2) {

    return r1 + (r2 - r1) * GOODRAND_01();
}

boolean dynamicParameterExpansion (Variation* vp) {

    return true;
}

boolean dynamicParameterExpansion (Variation* vp, String pName) {

    // preset_id doesn't really expand parameters, but it changes them; this will make them refresh
    return true;
}


int PluginVarPrepare(Variation* vp)
{
   VAR(_resolutionX) = 1000000;
   VAR(_time) = 0.0;
   VAR(_iMax) = 12;
   VAR(_fc) = 2.0;
   VAR(_FR) = 1.0;
   VAR(_FG) = 1.0;
   VAR(_FB) = 1.0;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{


    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// import js.glsl.G;
// import js.glsl.vec2;
// import js.glsl.vec3;
// import js.glsl.vec4;
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import java.util.Random;
// 
// 
// public class GLSLKaleidoComplexFunc extends GLSLFunc {
// 
//   /*
//    * Variation : glsl_kaleidocomplex
//    * Date: October 31, 2018
//    * Reference
//    */
// 
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_RESOLUTIONX = "Density Pixels";
//   private static final String PARAM_SEED = "Seed";
//   private static final String PARAM_TIME = "time";
//   private static final String PARAM_IMAX = "iMax";
//   private static final String PARAM_COLOR = "Color";
//   private static final String PARAM_FR = "Red Fac.";
//   private static final String PARAM_FG = "Green Fac.";
//   private static final String PARAM_FB = "Blue Fac.";
//   private static final String PARAM_GRADIENT = "Gradient";
// 
//   int seed = 10000;
//   int resolutionX = 1000000;
//   int resolutionY = resolutionX;
//   double time = 0.0;
//   int iMax = 12;
//   double fc = 2.0;
//   double FR = 1.0, FG = 1.0, FB = 1.0;
//   int gradient = 0;
//   Random randomize = new Random(seed);
// 
// 
//   private static final String[] paramNames = {PARAM_RESOLUTIONX, PARAM_SEED, PARAM_TIME, PARAM_IMAX, PARAM_COLOR,
//           PARAM_FR, PARAM_FG, PARAM_FB, PARAM_GRADIENT};
// 
//   public double random(double r1, double r2) {
//     return r1 + (r2 - r1) * randomize.nextDouble();
//   }
// 
//   public vec2 cmult(vec2 a, vec2 b) {
//     return (new vec2(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x));
//   }
// 
//   public vec3 getRGBColor(int xp, int yp) {
//     double x = (double) xp + 0.5;
//     double y = (double) yp + 0.5;
// 
//     vec2 uv = new vec2(x / resolutionX - .5, y / resolutionY - .5);
// 
// 
//     vec4 z = new vec4(0.0, 0.0, 0.0, 0.0);
//     vec2 of = new vec2(G.abs(uv.x) / 0.125, G.abs(uv.y) / 0.125).multiply(1.0);
//     vec3 col = new vec3(0.0);
//     vec2 dist = new vec2(0.0);
//     // z.xy=of;
//     z.x = of.x;
//     z.y = of.y;
//     int ii = -1;
// 
//     double r = 1.;
//     for (int i = -1; i < iMax; ++i) {
//       r *= -1.;
//       ++ii;
// //	        z.xy = (double)ii*.1251*0.+cmult(new vec2(z.x,z.y), new vec2(1.,1.)).xy;
//       vec2 t1 = cmult(new vec2(z.x, z.y), new vec2(1., 1.));
//       z.x = t1.x;
//       z.y = t1.y;
// 
// //	        z.xy = abs(z.xy)-10.5+r;
//       t1 = G.abs(new vec2(z.x, z.y)).plus(r - 10.5);
//       z.x = t1.x;
//       z.y = t1.y;
// 
// //			z.xy = cmult(z.xy, vec2(sin(t*1.), cos(t*1.) )-0.*vec2(1., -1.) );	
//       t1 = cmult(new vec2(z.x, z.y), new vec2(Math.sin(time), Math.cos(time)));
//       z.x = t1.x;
//       z.y = t1.y;
//       z.z = fc * (z.x * z.z - z.y * z.w);
//       z.w = fc * (z.y * z.z - z.x * z.w);
//       dist.x = G.dot(new vec2(z.x, z.y), new vec2(z.x, z.y));
//       dist.y = G.dot(new vec2(z.z, z.w), new vec2(z.z, z.w));
//       if ((double) ii > 0. && (Math.sqrt(z.x * z.x) < .51 || Math.sqrt(z.y * z.y) < .51)) {
//         col.x = Math.exp(-Math.abs(z.x * z.x * z.y)); // expensive but pretty
//         col.y = Math.exp(-Math.abs(z.y * z.x * z.y));
//         col.z = Math.exp(-Math.abs(G.min(z.x, z.y)));
//         break;
//       }
// 
//       col.x += fc * Math.exp(-Math.abs(-z.x / (double) ii + (double) ii / z.x)); // expensive but pretty
//       col.y += fc * Math.exp(-Math.abs(-z.y / (double) ii + (double) ii / z.y));
//       col.z += fc * Math.exp(-Math.abs((-z.x - z.y) / (double) ii + (double) ii / (z.x + z.y)));
//       if (dist.x > 10000000.0 || dist.y > 100000000000.0)
//         break;
//     }
//     col = new vec3(G.cos(col.x * FR), G.cos(col.y * FG), G.cos(col.z * FB));
//     return col;
//   }
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// 
// 
//     int i = (int) (pContext.random() * resolutionX);
//     int j = (int) (pContext.random() * resolutionY);
// 
//     vec3 color = new vec3(0.0);
// 
//     color = getRGBColor(i, j);
// 
//     if (gradient == 0) {
//       int[] tcolor = new int[3];
//       tcolor = dbl2int(color);
// 
//       pVarTP.rgbColor = true;
//       ;
//       pVarTP.redColor = tcolor[0];
//       pVarTP.greenColor = tcolor[1];
//       pVarTP.blueColor = tcolor[2];
// 
//     } else {
//       double s = (color.x + color.y + color.z);
//       double red = color.x / s;
// 
//       pVarTP.color = Math.sin(red);
// 
//     }
//     pVarTP.x += pAmount * ((double) (i) / resolutionX - 0.5);
//     pVarTP.y += pAmount * ((double) (j) / resolutionY - 0.5);
// 
//   }
// 
// 
//   public String getName() {
//     return "glsl_kaleidocomplex";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
// 
//   public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
//     return new Object[]{resolutionX, seed, time, iMax, fc, FR, FG, FB, gradient};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_RESOLUTIONX)) {
//       resolutionX = (int) Tools.limitValue(pValue, 100, 10000000);
//     } else if (PARAM_SEED.equalsIgnoreCase(pName)) {
//       seed = (int) Tools.limitValue(pValue, 0, 10000);
//       // seed=(int)ThreadLocalRandom.current().nextDouble(0.0, 10000.0);
//       randomize = new Random((long) seed);
//       time = random(0.0, 10000.0);
//       // time=ThreadLocalRandom.current().nextDouble(0.0, 10000.0);
//     } else if (pName.equalsIgnoreCase(PARAM_TIME)) {
//       time = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_IMAX)) {
//       iMax = (int) Tools.limitValue(pValue, 1, 50);
//     } else if (pName.equalsIgnoreCase(PARAM_COLOR)) {
//       fc = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_FR)) {
//       FR = Tools.limitValue(pValue, 0.0, 5.0);
//     } else if (pName.equalsIgnoreCase(PARAM_FG)) {
//       FG = Tools.limitValue(pValue, 0.0, 5.0);
//     } else if (pName.equalsIgnoreCase(PARAM_FB)) {
//       FB = Tools.limitValue(pValue, 0.0, 5.0);
//     } else if (pName.equalsIgnoreCase(PARAM_GRADIENT)) {
//       gradient = (int) Tools.limitValue(pValue, 0, 1);
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
//     return true;
//   }
// 
// }
// 
// 
