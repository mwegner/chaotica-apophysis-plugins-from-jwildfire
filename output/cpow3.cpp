#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: cpow3

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CPow3Func.java

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
	double d;
	double divisor;
	double spread;
	double _ang;
	double _p_a;
	double _c;
	double _half_c;
	double _d;
	double _half_d;
	double _coeff;
	double _full_spread;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "cpow3_"
#include "plugin.h"

APO_PLUGIN("cpow3");
APO_VARIABLES(
	VAR_REAL(r, 1.0),
	VAR_REAL(d, 1.0),
	VAR_REAL(divisor, 1),
	VAR_REAL(spread, 1),

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_ang) = 2.0 * M_PI / VAR(divisor);
    VAR(_p_a) = atan2((VAR(d) < 0 ? -log(-VAR(d)) : log(VAR(d))) * VAR(r), 2 * M_PI);
    VAR(_c) = cos(VAR(_p_a)) * VAR(r) * cos(VAR(_p_a)) / VAR(divisor);
    VAR(_d) = cos(VAR(_p_a)) * VAR(r) * sin(VAR(_p_a)) / VAR(divisor);
    VAR(_half_c) = VAR(_c) / 2.0;
    VAR(_half_d) = VAR(_d) / 2.0;
    VAR(_coeff) = VAR(_d) == 0 ? 0 : -0.095 * VAR(spread) / VAR(_d);


    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* cpow3 by Peter Sdobnov (Zueuk) translated by Brad Stefanov and Rick Sidwell  */

    double a = atan2(FTx, FTy);

    if (a < 0) a += 2 * M_PI;

    ;
    if (cos(a / 2) < GOODRAND_01() * 2.0 - 1.0)
      a -= 2 * M_PI;

    a += ((GOODRAND_01() < 0.5) ? 2 * M_PI : -2 * M_PI) * round(log(GOODRAND_01()) * VAR(_coeff));

    double lnr2 = log((FTx * FTx + FTy * FTy));  // logarithm * 2

    double r = VVAR * exp(VAR(_half_c) * lnr2 - VAR(_d) * a);
    double th = VAR(_c) * a + VAR(_half_d) * lnr2 + VAR(_ang) * floor(VAR(divisor) * GOODRAND_01());

    FPx += r * cos(th);
    FPy += r * sin(th);

    if (true /* pContext\.isPreserveZCoordinate() */) FPz += VVAR * FTz;



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
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class CPow3Func extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_R = "r";
//   private static final String PARAM_D = "d";
//   private static final String PARAM_DIVISOR = "divisor";
//   private static final String PARAM_SPREAD = "spread";
// 
//   private static final String[] paramNames = {PARAM_R, PARAM_D, PARAM_DIVISOR, PARAM_SPREAD};
// 
//   private double p_r = 1.0;
//   private double p_d = 1.0;
//   private double divisor = 1;
//   private double spread = 1;
// 
//   double ang, p_a, c, half_c, d, half_d, coeff, full_spread;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     ang = 2.0 * M_PI / divisor;
//     p_a = atan2((p_d < 0 ? -log(-p_d) : log(p_d)) * p_r, 2 * M_PI);
//     c = cos(p_a) * p_r * cos(p_a) / divisor;
//     d = cos(p_a) * p_r * sin(p_a) / divisor;
//     half_c = c / 2.0;
//     half_d = d / 2.0;
//     coeff = d == 0 ? 0 : -0.095 * spread / d;
// 
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* cpow3 by Peter Sdobnov (Zueuk) translated by Brad Stefanov and Rick Sidwell  */
// 
//     double a = pAffineTP.getPrecalcAtanYX();
// 
//     if (a < 0) a += 2 * M_PI;
// 
//     ;
//     if (cos(a / 2) < pContext.random() * 2.0 - 1.0)
//       a -= 2 * M_PI;
// 
//     a += ((pContext.random() < 0.5) ? 2 * M_PI : -2 * M_PI) * round(log(pContext.random()) * coeff);
// 
//     double lnr2 = log(pAffineTP.getPrecalcSumsq());  // logarithm * 2
// 
//     double r = pAmount * exp(half_c * lnr2 - d * a);
//     double th = c * a + half_d * lnr2 + ang * floor(divisor * pContext.random());
// 
//     pVarTP.x += r * cos(th);
//     pVarTP.y += r * sin(th);
// 
//     if (pContext.isPreserveZCoordinate()) pVarTP.z += pAmount * pAffineTP.z;
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
//     return new Object[]{p_r, p_d, divisor, spread};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_R.equalsIgnoreCase(pName))
//       p_r = pValue;
//     else if (PARAM_D.equalsIgnoreCase(pName))
//       p_d = pValue;
//     else if (PARAM_DIVISOR.equalsIgnoreCase(pName))
//       divisor = (pValue == 0) ? 1 : pValue;
//     else if (PARAM_SPREAD.equalsIgnoreCase(pName))
//       spread = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String[] getParameterAlternativeNames() {
//     return new String[]{"cpow_r", "cpow_d", "cpow_divisor", "cpow_spread"};
//   }
// 
//   @Override
//   public String getName() {
//     return "cpow3";
//   }
// 
// }
// 
