#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: glsl_squares

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/GLSLSquaresFunc.java

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
	int _resolutionY; // resolutionX
	int Seed;
	double _time = 85.5;
	int _N = 3;
	int _dir = 1;
	double _FR = 1.8;
	double _FG = 1.9;
	double _FB = 2.2;
	int _gradient;

} Variables;

#define APO_VARIABLE_PREFIX "glsl_squares_"
#include "plugin.h"

APO_PLUGIN("glsl_squares");
APO_VARIABLES(
	VAR_INTEGER(Seed, 5000),

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
// public class GLSLSquaresFunc extends GLSLFunc {
// 
//   /*
//    * Variation : glsl_squares
//    * Date: October 31, 2018
//    * Reference  http://glslsandbox.com/e#8702.0
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
//   private static final String PARAM_DIR = "Direction";
//   private static final String PARAM_FR = "Red Fac.";
//   private static final String PARAM_FG = "Green Fac.";
//   private static final String PARAM_FB = "Blue Fac.";
// 
//   private static final String PARAM_GRADIENT = "Gradient";
// 
// 
//   int resolutionX = 1000000;
//   int resolutionY = resolutionX;
//   private int seed = 5000;
//   double time = 85.5;
//   int N = 3;
//   int dir = 1;
// 
// 
//   double FR = 1.8, FG = 1.9, FB = 2.2;
//   int gradient = 0;
// 
//   Random randomize = new Random(seed);
// 
// 
//   private static final String[] paramNames = {PARAM_RESOLUTIONX, PARAM_SEED, PARAM_TIME, PARAM_N, PARAM_DIR, PARAM_FR, PARAM_FG, PARAM_FB, PARAM_GRADIENT};
// 
//   public double random(double r1, double r2) {
//     return r1 + (int) ((r2 - r1) + 1) * randomize.nextDouble();
//   }
// 
// 
//   public boolean hit(vec2 p) {
//     double direction; // -1.0 to zoom out
// 
//     if (dir == 1)
//       direction = 0.1;
//     else
//       direction = -1.0;
// 
//     vec2 sectors;
//     int lim = N;
//     vec2 coordIter = p.division(Math.pow(0.5, G.mod(direction * time, 1.0)));
// 
//     for (int i = 0; i < lim; i++) {
//       sectors = (G.floor(coordIter.multiply(3.0)));
//       if (sectors.x == 1 && sectors.y == 1) {
//         // make a hole
//         return false;
//       } else {
//         // map current sector to whole carpet
//         coordIter = coordIter.multiply(3.0).minus(sectors);
//       }
//     }
// 
//     return true;
//   }
// 
//   public vec3 getRGBColor(int xp, int yp) {
//     double x = (double) xp + 0.5;
//     double y = (double) yp + 0.5;
// 
//     // Half the width and half the height gives the position of the center of the screen
// 
//     vec2 coordOrig = new vec2(Math.abs(x / resolutionX - .5), Math.abs(y / resolutionY - .5));
// 
//     coordOrig = G.mod(coordOrig, 1.0);
//     vec3 color = new vec3(G.cos(time), Math.tan(time), G.sin(time));
//     for (int i = 0; i < 4; i++) {
//       if (hit(new vec2((double) i * 0.1).plus(coordOrig)))
//         color = new vec3(1.0).minus(color);
//     }
//     return new vec3(G.cos(color.x * FR), G.cos(color.y * FG), G.cos(color.z * FB));
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
//     return "glsl_squares";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
//     return new Object[]{resolutionX, seed, time, N, dir, FR, FG, FB, gradient};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_RESOLUTIONX)) {
//       resolutionX = (int) Tools.limitValue(pValue, 100, 10000000);
//     } else if (PARAM_SEED.equalsIgnoreCase(pName)) {
//       seed = (int) pValue;
//       randomize = new Random(seed);
//       time = random(0.0, 10000.0);
//     } else if (pName.equalsIgnoreCase(PARAM_TIME)) {
//       time = Tools.limitValue(pValue, 0.0, 1000.0);
//     } else if (pName.equalsIgnoreCase(PARAM_N)) {
//       N = (int) Tools.limitValue(pValue, 1, 20);
//     } else if (pName.equalsIgnoreCase(PARAM_DIR)) {
//       dir = (int) Tools.limitValue(pValue, 0, 1);
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
