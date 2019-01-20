#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: glsl_acrilic

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/GLSLAcrilicFunc.java

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
	double _time = 0.0;
	int _steps = 10;
	double _p1 = 12.0;
	double _p2 = 12.0;
	double _p3 = 12.0;
	double _p4 = 12.0;
	double _p5 = 75;
	double _p6 = 75;
	double _FR = 1.0;
	double _FG = 1.0;
	double _FB = 1.0;
	int _gradient;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "glsl_acrilic_"
#include "plugin.h"

APO_PLUGIN("glsl_acrilic");
APO_VARIABLES(
	VAR_INTEGER(Seed, 10000),

);


double random (Variation* vp, double r1, double r2) {

    return r1 + (r2 - r1) * GOODRAND_01();
}

double sq (Variation* vp, double x) {

    return x * x;
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
   VAR(_steps) = 10;
   VAR(_p1) = 12.0;
   VAR(_p2) = 12.0;
   VAR(_p3) = 12.0;
   VAR(_p4) = 12.0;
   VAR(_p5) = 75;
   VAR(_p6) = 75;
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
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import java.util.Random;
// 
// 
// public class GLSLAcrilicFunc extends GLSLFunc {
// 
//   /*
//    * Variation : glsl_acrilic
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
//   private static final String PARAM_STEPS = "Steps";
//   private static final String PARAM_P1 = "p1";
//   private static final String PARAM_P2 = "p2";
//   private static final String PARAM_P3 = "p3";
//   private static final String PARAM_P4 = "p4";
//   private static final String PARAM_P5 = "p5";
//   private static final String PARAM_P6 = "p6";
//   private static final String PARAM_FR = "Red Fac.";
//   private static final String PARAM_FG = "Green Fac.";
//   private static final String PARAM_FB = "Blue Fac.";
//   private static final String PARAM_GRADIENT = "Gradient";
// 
// 
//   int resolutionX = 1000000;
//   int resolutionY = resolutionX;
//   private int seed = 10000;
//   double time = 0.0;
//   int steps = 10;
//   double p1 = 12.0;
//   double p2 = 12.0;
//   double p3 = 12.0;
//   double p4 = 12.0;
//   double p5 = 75;
//   double p6 = 75;
//   double FR = 1.0, FG = 1.0, FB = 1.0;
//   int gradient = 0;
// 
// 
//   Random randomize = new Random(seed);
// 
// 
//   private static final String[] paramNames = {PARAM_RESOLUTIONX, PARAM_SEED, PARAM_TIME, PARAM_STEPS, PARAM_P1, PARAM_P2, PARAM_P3, PARAM_P4, PARAM_P5, PARAM_P6,
//           PARAM_FR, PARAM_FG, PARAM_FB, PARAM_GRADIENT};
// 
//   public double random(double r1, double r2) {
//     return r1 + (r2 - r1) * randomize.nextDouble();
//   }
// 
//   public double sq(double x) {
//     return x * x;
//   }
// 
// 
//   public vec3 getRGBColor(int xp, int yp) {
// 
// 
//     double x = (double) xp + 0.5;
//     double y = (double) yp + 0.5;
// 
//     vec2 p = new vec2(0.7 * x / resolutionX, 0.7 * y / resolutionY);
//     vec3 col = new vec3(0.0);
// 
//     for (int j = 0; j < 3; j++) {
//       for (int i = 1; i < steps; i++) {
//         p.x += 0.1 / (i + j) * G.sin(i * p1 * p.y + time + G.cos((time / (p2 * i)) * i + j));
//         p.y += 0.1 / (i + j) * G.cos(i * p3 * p.x + time + G.sin((time / (p4 * i)) * i + j));
//       }
//       if (j == 0)
//         col.x = G.sin(p5 * sq(p.x)) + G.sin(p6 * sq(p.y));
//       if (j == 1)
//         col.y = G.sin(p5 * sq(p.x)) + G.sin(p6 * sq(p.y));
//       if (j == 2)
//         col.z = G.sin(p5 * sq(p.x)) + G.sin(p6 * sq(p.y));
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
//     return "glsl_acrilic";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
// 
//   public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
//     return new Object[]{resolutionX, seed, time, steps, p1, p2, p3, p4, p5, p6, FR, FG, FB, gradient};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_RESOLUTIONX)) {
//       resolutionX = (int) Tools.limitValue(pValue, 100, 10000000);
//     } else if (PARAM_SEED.equalsIgnoreCase(pName)) {
//       seed = (int) pValue;
//       randomize = new Random(seed);
//       time = random(0.0, 10000000.0);
//     } else if (pName.equalsIgnoreCase(PARAM_TIME)) {
//       time = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_STEPS)) {
//       steps = (int) Tools.limitValue(pValue, 3, 100);
//     } else if (pName.equalsIgnoreCase(PARAM_P1)) {
//       p1 = Tools.limitValue(pValue, 1., 100.);
//     } else if (pName.equalsIgnoreCase(PARAM_P2)) {
//       p2 = Tools.limitValue(pValue, 1., 100.);
//     } else if (pName.equalsIgnoreCase(PARAM_P3)) {
//       p3 = Tools.limitValue(pValue, 1., 100.);
//     } else if (pName.equalsIgnoreCase(PARAM_P4)) {
//       p4 = Tools.limitValue(pValue, 1., 100.);
//     } else if (pName.equalsIgnoreCase(PARAM_P5)) {
//       p5 = Tools.limitValue(pValue, 1., 100.);
//     } else if (pName.equalsIgnoreCase(PARAM_P6)) {
//       p6 = Tools.limitValue(pValue, 1., 100.);
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
