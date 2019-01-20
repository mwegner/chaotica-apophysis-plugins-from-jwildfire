#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: cpow3_wf

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CPow3WFFunc.java

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
	double r;
	double a;
	double divisor;
	double spread;
	double discrete_spread;
	double spread2;
	double offset2;
	double _c;
	double _d;
	double _half_c;
	double _half_d;
	double _ang;
	double _inv_spread;
	double _full_spread;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "cpow3_wf_"
#include "plugin.h"

APO_PLUGIN("cpow3_wf");
APO_VARIABLES(
	VAR_REAL(r, 1.0),
	VAR_REAL(a, 0.1),
	VAR_REAL(divisor, 1.0),
	VAR_REAL(spread, 1.0),
	VAR_REAL(discrete_spread, 1.0),
	VAR_REAL(spread2, 0.0),
	VAR_REAL(offset2, 1.0),

);



int PluginVarPrepare(Variation* vp)
{
    /* CPow2 PluginVarPrepare()
    VAR(ang) = 2*M_PI / ((double) VAR(cpow2_divisor));
    VAR(c) = VAR(cpow2_r) * cos(M_PI/2*VAR(cpow2_a)) / ((double) VAR(cpow2_divisor));
    VAR(d) = VAR(cpow2_r) * sin(M_PI/2*VAR(cpow2_a)) / ((double) VAR(cpow2_divisor));
    VAR(half_c) = VAR(c) / 2;
    VAR(half_d) = VAR(d) / 2;
    VAR(inv_spread) = 0.5 / VAR(cpow2_spread);
    VAR(full_spread) = 2*M_PI*VAR(cpow2_spread);
    */
    VAR(_ang) = 2.0 * M_PI / VAR(divisor);
    VAR(_c) = VAR(r) * cos(M_PI / 2 * VAR(a)) / VAR(divisor);
    VAR(_d) = VAR(r) * sin(M_PI / 2 * VAR(a)) / VAR(divisor);
    VAR(_half_c) = VAR(_c) / 2;
    VAR(_half_d) = VAR(_d) / 2;
    VAR(_inv_spread) = 0.5 / VAR(spread);
    VAR(_full_spread) = 2 * M_PI * VAR(spread);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Cpow3_wf by Cozyg
      CPow2 PluginVarCalc
      double sn, cs;
      double VAR(a) = atan2(FTy, FTx);
      int n = rand() % VAR(cpow2_spread);
      if (VAR(a) < 0) n++;
      VAR(a) += 2*M_PI*n;
      if (cos(VAR(a)*VAR(inv_spread)) < rand()*2.0/RAND_MAX - 1.0)
          VAR(a) -= VAR(full_spread);
      double lnr2 = log(FTx*FTx + FTy*FTy); // logarithm * 2
      double VAR(r) = VVAR * exp(VAR(half_c) * lnr2 - VAR(d) * VAR(a));
      fsincos(VAR(c) * VAR(a) + VAR(half_d) * lnr2 + VAR(ang) * rand(),
          &sn, &cs);
      FPx += VAR(r) * cs;
      FPy += VAR(r) * sn;
      */

    double ai = atan2(FTx, FTy);
    double n = GOODRAND_01() * VAR(spread);
    if (VAR(discrete_spread) >= 1.0) {
      n = (int) n;
    }
    if (ai < 0) {
      n++;
    }
    ai += 2 * M_PI * n;
    if (cos(ai * VAR(_inv_spread)) < (GOODRAND_01() * 2.0 - 1.0)) {
      ai -= VAR(_full_spread);
    }
    double lnr2 = log((FTx * FTx + FTy * FTy));
    double ri = VVAR * exp(VAR(_half_c) * lnr2 - VAR(_d) * ai);
    double ang2 = VAR(_c) * ai * VAR(_half_d) * lnr2 * VAR(_ang) * (GOODRAND_01() * VAR(spread2) + VAR(offset2));
    FPx += ri * cos(ang2);
    FPy += ri * sin(ang2);

    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }



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
// 
// /*
//      CPow3 by CozyG
//      Started as attempt to port CPow2 Apophysis Plugin to JWildfire Variation, 
//           but by happy accident became something else? 
//           (doesn't look at all like cpow2 in Apophysis7x.15D (2.10.15.3))
//           original CPow2 Apophysis plugin written by xyrus02:
//              http://sourceforge.net/p/apo-plugins/code/HEAD/tree/personal/georgkiehne/updated_for_x64/cpow2.c
//  */
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class CPow3WFFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_R = "r";
//   private static final String PARAM_A = "a";
//   private static final String PARAM_DIVISOR = "divisor";
//   private static final String PARAM_SPREAD = "spread";
//   private static final String PARAM_DISCRETE_SPREAD = "discrete_spread";
//   private static final String PARAM_SPREAD2 = "spread2";
//   private static final String PARAM_OFFSET2 = "offset2";
// 
//   private static final String[] paramNames = {PARAM_R, PARAM_A, PARAM_DIVISOR, PARAM_SPREAD, PARAM_DISCRETE_SPREAD, PARAM_SPREAD2, PARAM_OFFSET2};
// 
//   // Parameters
//   private double r = 1.0;
//   private double a = 0.1;
//   private double divisor = 1.0;
//   private double spread = 1.0;
//   private double discrete_spread = 1.0;
//   private double spread2 = 0.0;
//   private double offset2 = 1.0;
// 
//   // Internal fields set in init (based on parameters)
//   double c;
//   double d;
//   double half_c;
//   double half_d;
//   double ang;
//   double inv_spread;
//   double full_spread;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Cpow3_wf by Cozyg
//       CPow2 PluginVarCalc
//       double sn, cs;
//       double a = atan2(FTy, FTx);
//       int n = rand() % VAR(cpow2_spread);
//       if (a < 0) n++;
//       a += 2*M_PI*n;
//       if (cos(a*VAR(inv_spread)) < rand()*2.0/RAND_MAX - 1.0)
//           a -= VAR(full_spread);
//       double lnr2 = log(FTx*FTx + FTy*FTy); // logarithm * 2
//       double r = VVAR * exp(VAR(half_c) * lnr2 - VAR(d) * a);
//       fsincos(VAR(c) * a + VAR(half_d) * lnr2 + VAR(ang) * rand(),
//           &sn, &cs);
//       FPx += r * cs;
//       FPy += r * sn;
//       */
// 
//     double ai = pAffineTP.getPrecalcAtanYX();
//     double n = pContext.random() * spread;
//     if (discrete_spread >= 1.0) {
//       n = (int) n;
//     }
//     if (ai < 0) {
//       n++;
//     }
//     ai += 2 * M_PI * n;
//     if (cos(ai * inv_spread) < (pContext.random() * 2.0 - 1.0)) {
//       ai -= full_spread;
//     }
//     double lnr2 = log(pAffineTP.getPrecalcSumsq());
//     double ri = pAmount * exp(half_c * lnr2 - d * ai);
//     double ang2 = c * ai * half_d * lnr2 * ang * (pContext.random() * spread2 + offset2);
//     pVarTP.x += ri * cos(ang2);
//     pVarTP.y += ri * sin(ang2);
// 
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
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
//     return new Object[]{r, a, divisor, spread, discrete_spread, spread2, offset2};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_R.equalsIgnoreCase(pName))
//       r = pValue;
//     else if (PARAM_A.equalsIgnoreCase(pName))
//       a = pValue;
//     else if (PARAM_DIVISOR.equalsIgnoreCase(pName))
//       divisor = pValue;
//     else if (PARAM_SPREAD.equalsIgnoreCase(pName)) {
//       spread = pValue;
//     } else if (PARAM_DISCRETE_SPREAD.equalsIgnoreCase(pName)) {
//       discrete_spread = pValue;
//     } else if (PARAM_SPREAD2.equalsIgnoreCase(pName)) {
//       spread2 = pValue;
//     } else if (PARAM_OFFSET2.equalsIgnoreCase(pName)) {
//       offset2 = pValue;
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "cpow3_wf";
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     /* CPow2 PluginVarPrepare()
//     VAR(ang) = 2*M_PI / ((double) VAR(cpow2_divisor));
//     VAR(c) = VAR(cpow2_r) * cos(M_PI/2*VAR(cpow2_a)) / ((double) VAR(cpow2_divisor));
//     VAR(d) = VAR(cpow2_r) * sin(M_PI/2*VAR(cpow2_a)) / ((double) VAR(cpow2_divisor));
//     VAR(half_c) = VAR(c) / 2;
//     VAR(half_d) = VAR(d) / 2;
//     VAR(inv_spread) = 0.5 / VAR(cpow2_spread);
//     VAR(full_spread) = 2*M_PI*VAR(cpow2_spread);
//     */
//     ang = 2.0 * M_PI / divisor;
//     c = r * cos(M_PI / 2 * a) / divisor;
//     d = r * sin(M_PI / 2 * a) / divisor;
//     half_c = c / 2;
//     half_d = d / 2;
//     inv_spread = 0.5 / spread;
//     full_spread = 2 * M_PI * spread;
//   }
// 
// }
// 
