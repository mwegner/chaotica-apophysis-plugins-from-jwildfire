/*
    Apophysis Plugin: glsl_circlesblue

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/GLSLCirclesBlueFunc.java

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
	double _time = 1.0;
	double _fRadius = 0.04;
	int _bubles = 40;
	int _gradient;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "glsl_circlesblue_"
#include "plugin.h"

APO_PLUGIN("glsl_circlesblue");
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
// public class GLSLCirclesBlueFunc extends GLSLFunc {
// 
//   /*
//    * Variation : glsl_circlesblue
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
//   private static final String PARAM_RADIUS = "Radiusy";
//   private static final String PARAM_BUBLES = "Bubles";
//   private static final String PARAM_GRADIENT = "Gradient";
// 
// 
//   int resolutionX = 1000000;
//   int resolutionY = resolutionX;
//   private int seed = 10000;
//   double time = 1.0;
//   double fRadius = 0.04;
//   int bubles = 40;
//   int gradient = 0;
// 
//   Random randomize = new Random(seed);
// 
// 
//   private static final String[] paramNames = {PARAM_RESOLUTIONX, PARAM_SEED, PARAM_TIME, PARAM_RADIUS, PARAM_BUBLES, PARAM_GRADIENT};
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
//     vec2 uv = new vec2(2 * x / resolutionX - 1., 2 * y / resolutionY - 1.0);
// 
// 
//     vec3 color = new vec3(0.0);
// 
//     // bubbles
//     for (int i = 0; i < bubles; i++) {
//       // bubble seeds
//       double pha = Math.tan((double) i * 6. + 1.0) * 0.5 + 0.5;
//       double siz = G.pow(G.cos((double) i * 2.4 + 5.0) * 0.5 + 0.5, 4.0);
//       double pox = G.cos((double) i * 3.55 + 4.1);
// 
//       // buble size, position and color
//       double rad = fRadius + G.sin((double) i) * 0.12 + 0.08;
// 
//       vec2 pos = new vec2(pox + G.sin(time / 15. + pha + siz), -1.0 - rad + (2.0 + 2.0 * rad)
//               * G.mod(pha + 0.1 * (time / 5.) * (0.2 + 0.8 * siz), 1.0));
// 
// 
//       double dis = G.length(uv.minus(pos));
//       vec3 col = G.mix(new vec3(0.1, 0.2, 0.8), new vec3(0.2, 0.8, 0.6), 0.5 + 0.5 * G.sin((double) i * G.sin(time * pox * 0.03) + 1.9));
// 
//       // render
// 
//       color = color.add(col.multiply(1. - G.smoothstep(rad * (0.65 + 0.20 * G.sin(pox * time)), rad, dis)).multiply((1.0 - G.cos(pox * time))));
//     }
// 
//     return color.multiply(0.3);
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
//     return "glsl_circlesblue";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
// 
//   public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
//     return new Object[]{resolutionX, seed, time, fRadius, bubles, gradient};
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
//     } else if (pName.equalsIgnoreCase(PARAM_RADIUS)) {
//       fRadius = Tools.limitValue(pValue, 0.0, 1.0);
//     } else if (pName.equalsIgnoreCase(PARAM_BUBLES)) {
//       bubles = (int) Tools.limitValue(pValue, 1, 100);
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
