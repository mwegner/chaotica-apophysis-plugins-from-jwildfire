/*
    Apophysis Plugin: harmonograph_js

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/HarmonographFunc.java

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
	int seed;
	int time;
	int a1; // amplitude as you like
	double f1; //keep frequencies around 1
	int p1;
	double d1;
	int a2;
	double f2;
	int p2;
	double d2;
	int a3;
	double f3;
	int p3;
	double d3;
	int a4;
	double f4;
	int p4;
	double d4;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "harmonograph_js_"
#include "plugin.h"

APO_PLUGIN("harmonograph_js");
APO_VARIABLES(
	VAR_INTEGER(seed, 1234),
	VAR_INTEGER(time, 100),
	VAR_INTEGER(a1, 0),
	VAR_REAL(f1, 0),
	VAR_INTEGER(p1, 0),
	VAR_REAL(d1, 0),
	VAR_INTEGER(a2, 0),
	VAR_REAL(f2, 0),
	VAR_INTEGER(p2, 0),
	VAR_REAL(d2, 0),
	VAR_INTEGER(a3, 0),
	VAR_REAL(f3, 0),
	VAR_INTEGER(p3, 0),
	VAR_REAL(d3, 0),
	VAR_INTEGER(a4, 0),
	VAR_REAL(f4, 0),
	VAR_INTEGER(p4, 0),
	VAR_REAL(d4, 0),

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
// import org.jwildfire.base.mathlib.MathLib;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import java.util.Random;
// 
// import static org.jwildfire.base.mathlib.MathLib.M_PI;
// import static org.jwildfire.base.mathlib.MathLib.sin;
// 
// public class HarmonographFunc extends VariationFunc {
//   /**
//    * Harmonograph
//    *
//    * @author Jesus Sosa
//    * @date December 8, 2017
//    * based on this Article:
//    * http://www.instructables.com/id/Harmonographs-a-Subtle-Artform/
//    */
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_SEED = "seed";
//   private static final String PARAM_TIME = "time";
//   private static final String PARAM_AMPL_X = "a1";
//   private static final String PARAM_FREQ_X = "f1";
//   private static final String PARAM_PHAS_X = "p1";
//   private static final String PARAM_DAMP_X = "d1";
// 
//   private static final String PARAM_AMPL_Y = "a2";
//   private static final String PARAM_FREQ_Y = "f2";
//   private static final String PARAM_PHAS_Y = "p2";
//   private static final String PARAM_DAMP_Y = "d2";
// 
//   private static final String PARAM_ROT_AMPL_X = "a3";
//   private static final String PARAM_ROT_FREQ_X = "f3";
//   private static final String PARAM_ROT_PHAS_X = "p3";
//   private static final String PARAM_ROT_DAMP_X = "d3";
// 
//   private static final String PARAM_ROT_AMPL_Y = "a4";
//   private static final String PARAM_ROT_FREQ_Y = "f4";
//   private static final String PARAM_ROT_PHAS_Y = "p4";
//   private static final String PARAM_ROT_DAMP_Y = "d4";
// 
//   private static final String[] paramNames = {PARAM_SEED, PARAM_TIME, PARAM_AMPL_X, PARAM_FREQ_X, PARAM_PHAS_X, PARAM_DAMP_X,
//           PARAM_AMPL_Y, PARAM_FREQ_Y, PARAM_PHAS_Y, PARAM_DAMP_Y,
//           PARAM_ROT_AMPL_X, PARAM_ROT_FREQ_X, PARAM_ROT_PHAS_X, PARAM_ROT_DAMP_X,
//           PARAM_ROT_AMPL_Y, PARAM_ROT_FREQ_Y, PARAM_ROT_PHAS_Y, PARAM_ROT_DAMP_Y};
// 
//   private Random rand = new Random();
//   private int seed = 1234;
// 
//   private int time = 100;
//   private int a1; // amplitude as you like
//   private double f1; //keep frequencies around 1
//   private int p1;
//   private double d1;
// 
//   private int a2;
//   private double f2;
//   private int p2;
//   private double d2;
// 
//   private int a3;
//   private double f3;
//   private int p3;
//   private double d3;
// 
//   private int a4;
//   private double f4;
//   private int p4;
//   private double d4;
// 
//   public HarmonographFunc() {
//     rand.setSeed(seed);
//     calcParams();
//   }
// 
//   public void calcParams() {
//     a1 = (int) (rand.nextInt(180)); // amplitude as you like
//     f1 = -5.0 + rand.nextInt(5 - (-5) + 1); //keep frequencies around 1
//     p1 = (int) (rand.nextInt(180));
//     d1 = 0.0005 + Math.random() / 1000.0;
// 
//     a2 = (int) (rand.nextInt(180));
//     f2 = -5.0 + rand.nextInt(5 - (-5) + 1);
//     p2 = (int) (rand.nextInt(180));
//     d2 = 0.0005 + Math.random() / 1000.0;
// 
//     a3 = (int) (rand.nextInt(180));
//     f3 = -5.0 + rand.nextInt(5 - (-5) + 1);
//     p3 = (int) (rand.nextInt(90));
//     d3 = 0.0005 + Math.random() / 1000.0;
// 
//     a4 = (int) (rand.nextInt(180));
//     f4 = -5.0 + rand.nextInt(5 - (-5) + 1);
//     p4 = (int) (rand.nextInt(90));
//     d4 = 0.0005 + Math.random() / 1000.0;
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
// 
//   }
// 
//   public double mo(double t, double a1, double f1, double p_1, double d1, double a2, double f2, double p_2, double d2) {
//     double p1 = p_1 * M_PI / 180.0;
//     double p2 = p_2 * M_PI / 180.0;
// 
//     return a1 * sin(t * f1 + p1) * MathLib.exp(-1 * d1 * t) + a2 * sin(t * f2 + p2) * MathLib.exp(-1 * d2 * t);
//   }
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // Harmonograph: Reference
//     // based on this Article:
//     // http://www.instructables.com/id/Harmonographs-a-Subtle-Artform/
// 
//     double x, y;
//     double t = (double) (pContext.random() * time);
// 
//     x = mo(t, a1, f1, p1, d1, a2, f2, p2, d2) / 180;
//     y = mo(t, a3, f3, p3 + 90.0, d3, a4, f4, p4 + 90.0, d4) / 180;
// 
//     pVarTP.x += x * pAmount;
//     pVarTP.y += y * pAmount;
// 
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{seed, time, a1, f1, p1, d1, a2, f2, p2, d2, a3, f3, p3, d3, a4, f4, p4, d4};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_SEED.equalsIgnoreCase(pName)) {
//       seed = (int) pValue;
//       rand.setSeed(seed);
//       calcParams();
//     } else if (PARAM_TIME.equalsIgnoreCase(pName))
//       time = (int) pValue;
//     else if (PARAM_AMPL_X.equalsIgnoreCase(pName))
//       a1 = (int) pValue;
//     else if (PARAM_FREQ_X.equalsIgnoreCase(pName))
//       f1 = pValue;
//     else if (PARAM_PHAS_X.equalsIgnoreCase(pName))
//       p1 = (int) pValue;
//     else if (PARAM_DAMP_X.equalsIgnoreCase(pName))
//       d1 = pValue;
//     else if (PARAM_AMPL_Y.equalsIgnoreCase(pName))
//       a2 = (int) pValue;
//     else if (PARAM_FREQ_Y.equalsIgnoreCase(pName))
//       f2 = pValue;
//     else if (PARAM_PHAS_Y.equalsIgnoreCase(pName))
//       p2 = (int) pValue;
//     else if (PARAM_DAMP_Y.equalsIgnoreCase(pName))
//       d2 = pValue;
//     else if (PARAM_ROT_AMPL_X.equalsIgnoreCase(pName))
//       a3 = (int) pValue;
//     else if (PARAM_ROT_FREQ_X.equalsIgnoreCase(pName))
//       f3 = pValue;
//     else if (PARAM_ROT_PHAS_X.equalsIgnoreCase(pName))
//       p3 = (int) pValue;
//     else if (PARAM_ROT_DAMP_X.equalsIgnoreCase(pName))
//       d3 = pValue;
//     else if (PARAM_ROT_AMPL_Y.equalsIgnoreCase(pName))
//       a4 = (int) pValue;
//     else if (PARAM_ROT_FREQ_Y.equalsIgnoreCase(pName))
//       f4 = pValue;
//     else if (PARAM_ROT_PHAS_Y.equalsIgnoreCase(pName))
//       p4 = (int) pValue;
//     else if (PARAM_ROT_DAMP_Y.equalsIgnoreCase(pName))
//       d4 = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "harmonograph_js";
//   }
// }
// 
