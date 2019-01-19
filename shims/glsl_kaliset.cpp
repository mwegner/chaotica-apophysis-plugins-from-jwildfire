/*
    Apophysis Plugin: glsl_kaliset

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/GLSLKaliSetFunc.java

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
	int _resolutionX = 1000000;
	int _resolutionY = resolutionX;
	int Seed;
	double _time = 200.0;
	int _N = 60;
	double _shiftx = -0.22;
	double _shifty = -0.21;
	int _gradient;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "glsl_kaliset_"
#include "plugin.h"

APO_PLUGIN("glsl_kaliset");
APO_VARIABLES(
	VAR_INTEGER(Seed, 10000),

    { "WARNING_this_plugin_does_nothing", INTEGER, OFFSET(___warning), 0, 1, 0 },
);


int PluginVarPrepare(Variation* vp)
{
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
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import java.util.Random;
// 
// 
// public class GLSLKaliSetFunc extends GLSLFunc {
// 
//   /*
//    * Variation : glsl_kaliset
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
//   private static final String PARAM_N = "N";
// 
//   private static final String PARAM_SHIFT_X = "ShiftX";
//   private static final String PARAM_SHIFT_Y = "ShiftY";
// 
//   private static final String PARAM_GRADIENT = "Gradient";
// 
// 
//   int resolutionX = 1000000;
//   int resolutionY = resolutionX;
//   private int seed = 10000;
//   double time = 200.;
//   int N = 60;
// 
//   double shiftx = -0.22, shifty = -0.21;
// 
// 
//   int gradient = 0;
// 
//   Random randomize = new Random(seed);
// 
// 
//   private static final String[] paramNames = {PARAM_RESOLUTIONX, PARAM_SEED, PARAM_TIME, PARAM_N, PARAM_SHIFT_X, PARAM_SHIFT_Y, PARAM_GRADIENT};
// 
//   public double random(double r1, double r2) {
//     return r1 + (r2 - r1) * randomize.nextDouble();
//   }
// 
// 
//   public vec3 getRGBColor(int xp, int yp) {
//     double x = (double) xp + 0.5;
//     double y = (double) yp + 0.5;
// 
//     // Half the width and half the height gives the position of the center of the screen
// 
//     vec2 v = new vec2(x / resolutionX - .5, y / resolutionY - .5).multiply(20.0);
// 
//     /*
//      * inspired by http://www.fractalforums.com/new-theories-and-research/very-simple-formula-for-fractal-patterns/
//      * a slight(?) different
//      * public domain
//      */
// 
// 
//     double rsum = 0.0;
//     double pi2 = 3.6 * 2.0;
//     double C = G.cos(time / 603. * pi2);
//     double S = G.sin(time / 407.4 * pi2);
//     vec2 shift = new vec2(shiftx, shifty);
//     double zoom = (time / 184.0 + 1.0);
// 
//     for (int i = 0; i < N; i++) {
//       double rr = v.x * v.x + v.y * v.y;
//       if (rr > 1.0) {
//         rr = 1.0 / rr;
//         v.x = v.x * rr;
//         v.y = v.y * rr;
//       }
//       rsum *= 0.99;
//       rsum += rr;
// 
//       v = new vec2(C * v.x - S * v.y, S * v.x + C * v.y).multiply(zoom).plus(shift);
//     }
// 
//     double col = rsum * 0.5;
//     return new vec3(G.cos(col * 1.0), G.cos(col * 2.0), G.cos(col * 4.0));
//   }
// 
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
//     return "glsl_kaliset";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
// 
//   public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
//     return new Object[]{resolutionX, seed, time, N, shiftx, shifty, gradient};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_RESOLUTIONX)) {
//       resolutionX = (int) Tools.limitValue(pValue, 100, 10000000);
//     } else if (PARAM_SEED.equalsIgnoreCase(pName)) {
//       seed = (int) pValue;
//       randomize = new Random(seed);
//       time = random(1.0, 1000.0);
//     } else if (pName.equalsIgnoreCase(PARAM_TIME)) {
//       time = Tools.limitValue(pValue, 1.0, 1000.0);
//     } else if (pName.equalsIgnoreCase(PARAM_N)) {
//       N = (int) Tools.limitValue(pValue, 1, 100);
//     } else if (pName.equalsIgnoreCase(PARAM_SHIFT_X)) {
//       shiftx = Tools.limitValue(pValue, -5.0, 5.0);
//     } else if (pName.equalsIgnoreCase(PARAM_SHIFT_Y)) {
//       shifty = Tools.limitValue(pValue, -5.0, 5.0);
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
