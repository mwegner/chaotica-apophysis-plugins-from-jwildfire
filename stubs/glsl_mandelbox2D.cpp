#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: glsl_mandelbox2D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/GLSLMandelBox2DFunc.java

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
	int _seed = 10000;
	double _time = 0.0;
	int _gradient;

} Variables;

#define APO_VARIABLE_PREFIX "glsl_mandelbox2D_"
#include "plugin.h"

APO_PLUGIN("glsl_mandelbox2D");
APO_VARIABLES(


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
// import js.glsl.vec4;
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import java.util.Random;
// 
// 
// public class GLSLMandelBox2DFunc extends GLSLFunc {
// 
//   /*
//    * Variation : glsl_mandelbox2D
//    * Autor: Jesus Sosa
//    * Date: October 31, 2018
//    * Reference
//    */
// 
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_RESOLUTIONX = "Density Pixels";
//   private static final String PARAM_SEED = "seed";
//   private static final String PARAM_TIME = "time";
//   private static final String PARAM_GRADIENT = "Gradient";
// 
//   int resolutionX = 1000000;
//   int resolutionY = resolutionX;
//   private int seed = 10000;
//   double time = 0.0;
// 
//   int gradient = 0;
//   Random randomize = new Random(seed);
// 
//   private static final String[] paramNames = {PARAM_RESOLUTIONX, PARAM_SEED, PARAM_TIME, PARAM_GRADIENT};
// 
//   public double random(double r1, double r2) {
//     return r1 + (r2 - r1) * randomize.nextDouble();
//   }
// 
//   public vec3 getRGBColor(int xp, int yp) {
//     double x = (double) xp + 0.5;
//     double y = (double) yp + 0.5;
//     vec2 I = new vec2(7 * (x + x - resolutionX) / resolutionX, 7 * (y + y - resolutionY) / resolutionY);
// 
//     vec4 O = new vec4(I, -5. * G.cos(time * .1), 1.);
// 
//     double d = 1.;
//     for (int i = 0; i < 20; i++) { //this mandelbox loop should also work in 3D(with a proper DE (initialize d at O.z,remove the +1.,and the factor 5 at the end)
//       I = G.clamp(I, -1., 1.).multiply(2.).minus(I);//boxfold
//       double b = (O.a = G.length(I)) < .5 ? 4. : O.a < 1. ? 1. / O.a : 1.;//ballfold
//       I = I.multiply(O.z * b).plus(new vec2(O.x, O.y)); //scaling
//       d = b * d * G.abs(O.z) + 1.;//bound distance estimation
//     }
//     d = Math.pow(G.length(I) / d, .1) * 5.;
//     O = new vec4(G.cos(d), G.sin(10. * d + 1.), G.cos(3. * d + 1.), 0).multiply(0.5).add(0.5);
//     return new vec3(O.r, O.g, O.b);
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
//       //	pVarTP.color=color.r;
//       pVarTP.color = color.r * color.g;
//       //	pVarTP.color=color.r*color.g*color.b;
//     }
//     pVarTP.x += pAmount * ((double) (i) / resolutionX - 0.5);
//     pVarTP.y += pAmount * ((double) (j) / resolutionY - 0.5);
// 
//   }
// 
// 
//   public String getName() {
//     return "glsl_mandelbox2D";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
// 
//   public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
//     return new Object[]{resolutionX, seed, time, gradient};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_RESOLUTIONX)) {
//       resolutionX = (int) Tools.limitValue(pValue, 100, 10000000);
//     } else if (pName.equalsIgnoreCase(PARAM_SEED)) {
//       seed = (int) Tools.limitValue(pValue, 0, 10000);
//       randomize = new Random((long) seed);
//       time = random(0.0, 10000.0);
//     } else if (pName.equalsIgnoreCase(PARAM_TIME)) {
//       time = pValue;
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
