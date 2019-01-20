#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: glsl_starsfield

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/GLSLStarsFieldFunc.java

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
	double _zdistance = 2.0;
	double _glow = 2.0;
	int _gradient;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "glsl_starsfield_"
#include "plugin.h"

APO_PLUGIN("glsl_starsfield");
APO_VARIABLES(
	VAR_INTEGER(Seed, 10000),

);


double random (Variation* vp, double r1, double r2) {

    return r1 + (r2 - r1) * GOODRAND_01();
}

double hash11 (Variation* vp, double p) {

    p = G.fract(p * 35.35);
    p += G.dot(p, p + 45.85);
    return G.fract(p * 7858.58);
}

double hash21 (Variation* vp, vec2 p) {

    p = G.fract(p.multiply(new vec2(451.45, 231.95)));
    p = p.plus(G.dot(p, p.plus(78.78)));
    return G.fract(p.x * p.y);
}

double layer (Variation* vp, vec2 uv) {


    double c = 0.0;

    uv = uv.multiply(5.0);

    vec2 i = G.floor(uv);
    vec2 f = G.fract(uv).multiply(VAR(_zdistance)).minus(1.0);

    vec2 p = hash22(i).multiply(0.3);
    double d = G.length(f.minus(p));
    c += G.smoothstep(.1 + .8 * hash21(vp, i), .01, d);
    c *= (1.0 / d) * .2;

    return c;
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
   VAR(_zdistance) = 2.0;
   VAR(_glow) = 2.0;

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
// import js.glsl.mat2;
// import js.glsl.vec2;
// import js.glsl.vec3;
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import java.util.Random;
// 
// 
// public class GLSLStarsFieldFunc extends GLSLFunc {
// 
//   /*
//    * Variation : glsl_starfield
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
//   private static final String PARAM_ZDISTANCE = "Z distance";
//   private static final String PARAM_GLOW = "Glow";
//   private static final String PARAM_GRADIENT = "Gradient";
// 
//   private int seed = 10000;
//   int resolutionX = 1000000;
//   int resolutionY = resolutionX;
//   double time = 0.0;
//   double zdistance = 2.0;
//   double glow = 2.0;
//   int gradient = 0;
//   Random randomize = new Random(seed);
// 
// 
//   private static final String[] paramNames = {PARAM_RESOLUTIONX, PARAM_SEED, PARAM_TIME, PARAM_ZDISTANCE, PARAM_GLOW, PARAM_GRADIENT};
// 
//   public double random(double r1, double r2) {
//     return r1 + (r2 - r1) * randomize.nextDouble();
//   }
// 
//   public mat2 rotate(double a) {
//     double c = G.cos(a);
//     double s = G.sin(a);
//     return new mat2(c, s, -s, c);
//   }
// 
// 
//   // one dimensional | 1 in 1 out
//   public double hash11(double p) {
//     p = G.fract(p * 35.35);
//     p += G.dot(p, p + 45.85);
//     return G.fract(p * 7858.58);
//   }
// 
//   // two dimensional | 2 in 1 out
//   public double hash21(vec2 p) {
//     p = G.fract(p.multiply(new vec2(451.45, 231.95)));
//     p = p.plus(G.dot(p, p.plus(78.78)));
//     return G.fract(p.x * p.y);
//   }
// 
//   // two dimensional | 2 in 2 out
//   public vec2 hash22(vec2 p) {
//     vec3 t1 = new vec3(p.x, p.y, p.x);
//     t1 = t1.multiply(new vec3(451.45, 231.95, 7878.5));
//     vec3 q = G.fract(t1);
//     q = q.add(G.dot(q, q.add(78.78)));
//     return G.fract(new vec2(q.x, q.z).multiply(q.y));
//   }
// 
//   public double layer(vec2 uv) {
// 
//     double c = 0.;
// 
//     uv = uv.multiply(5.);
// 
//     vec2 i = G.floor(uv);
//     vec2 f = G.fract(uv).multiply(zdistance).minus(1.);
// 
//     vec2 p = hash22(i).multiply(0.3);
//     double d = G.length(f.minus(p));
//     c += G.smoothstep(.1 + .8 * hash21(i), .01, d);
//     c *= (1. / d) * .2;
// 
//     return c;
//   }
// 
// 
//   public vec3 render(vec2 uv) {
// 
//     vec3 col = new vec3(0.);
//     uv = uv.times(rotate(time));
//     uv = uv.plus(new vec2(G.cos(time), G.sin(time)).multiply(2.0));
// 
//     for (double i = 0.; i < 1.; i += .1) {
// 
//       uv = uv.times(rotate(hash11(i) * 6.28));
// 
//       double t = G.fract(i - time);
//       double s = G.smoothstep(0., 1., t);
//       double f = G.smoothstep(0., 1., t);
//       f *= G.smoothstep(1., 0., t);
// 
//       vec2 k = hash22(new vec2(i, i * 5.)).multiply(0.1);
//       double l = layer((uv.minus(k)).multiply(s));
// 
//       col = col.add(G.mix(new vec3(.0, .0, 0), new vec3(1., 1.0, 1.0), l).multiply(f));
// 
//     }
// 
//     double t1 = glow * hash21(uv.plus(time));
//     col = col.add(new vec3(t1));
//     return col;
// 
//   }
// 
// 
//   public vec3 getRGBColor(int xp, int yp) {
//     double x = (double) xp + 0.5;
//     double y = (double) yp + 0.5;
// 
//     vec2 uv = new vec2(x / resolutionX - .5, y / resolutionY - .5);
//     vec3 col = render(uv);
// 
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
//     return "glsl_starsfield";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
// 
//   public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
//     return new Object[]{resolutionX, seed, time, zdistance, glow, gradient};
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
//     } else if (pName.equalsIgnoreCase(PARAM_ZDISTANCE)) {
//       zdistance = Tools.limitValue(pValue, 2.0, 150.0);
//     } else if (pName.equalsIgnoreCase(PARAM_GLOW)) {
//       glow = Tools.limitValue(pValue, 0.0, 1.0);
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
