#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: pre_stabilize

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PreStabilizeFunc.java

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
	int n;
	int seed; // (int) (random01() * 100000)
	double p;
	int dc;
	double _x[1];
	double _y[1];
	double _c[1];
	bool _start = true;
	double _nextColor;
	double _colorDelta;

} Variables;

#define APO_VARIABLE_PREFIX "pre_stabilize_"
#include "plugin.h"

APO_PLUGIN("pre_stabilize");
APO_VARIABLES(
	VAR_INTEGER(n, 4),
	VAR_INTEGER(seed, 0),
	VAR_REAL(p, 0.1),
	VAR_INTEGER(dc, 0),

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
// import java.util.Random;
// 
// public class PreStabilizeFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_N = "n";
//   private static final String PARAM_SEED = "seed";
//   private static final String PARAM_P = "p";
//   private static final String PARAM_DC = "dc";
//   private static final String[] paramNames = {PARAM_N, PARAM_SEED, PARAM_P, PARAM_DC};
// 
//   private int n = 4;
//   private int seed = (int) (Math.random() * 100000);
//   private double p = 0.1;
//   private int dc = 0;
//   private Random rand = new Random();
//   private double[] x, y, c;
//   private boolean start = true;
//   private double nextColor, colorDelta;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // pre_stabilize by Rick Sidwell, works as glitch repellent
// 
//     if (start || pContext.random() < p / 1000) {
//       start = false;
//       int i = pContext.random(n);
//       pAffineTP.x = x[i];
//       pAffineTP.y = y[i];
//       pAffineTP.z = 0;
//       if (dc != 0) pAffineTP.color = c[i];
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
//     return new Object[]{n, seed, p, dc};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_N.equalsIgnoreCase(pName))
//       n = Tools.FTOI(pValue);
//     else if (PARAM_SEED.equalsIgnoreCase(pName))
//       seed = Tools.FTOI(pValue);
//     else if (PARAM_P.equalsIgnoreCase(pName))
//       p = pValue;
//     else if (PARAM_DC.equalsIgnoreCase(pName))
//       dc = limitIntVal(Tools.FTOI(pValue), 0, 1);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "pre_stabilize";
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     if (n < 1)
//       n = 1;
// 
//     x = new double[n];
//     y = new double[n];
//     c = new double[n];
// 
//     rand.setSeed(seed);
//     nextColor = 0.5;
//     colorDelta = 1.0;
// 
//     for (int i = 0; i < n; i++) {
//       x[i] = rand.nextDouble() * 2 - 1;
//       y[i] = rand.nextDouble() * 2 - 1;
//       c[i] = nextColor;
//       nextColor += colorDelta;
//       if (nextColor >= 1) {
//         colorDelta /= 2;
//         nextColor = colorDelta / 2;
//       }
//     }
// 
//     start = true;
// 
//   }
// 
//   @Override
//   public int getPriority() {
//     return -1;
//   }
// 
// }
// 
