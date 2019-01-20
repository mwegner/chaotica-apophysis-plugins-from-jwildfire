#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: juliac

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/JuliaCFunc.java

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
	double re; // genRandomPower()
	double im;
	double dist;

} Variables;

#define APO_VARIABLE_PREFIX "juliac_"
#include "plugin.h"

APO_PLUGIN("juliac");
APO_VARIABLES(
	VAR_REAL(re, 0),
	VAR_REAL(im, 0.0),
	VAR_REAL(dist, 1.0)

);


double genRandomPower (Variation* vp) {

    double res = (int) (GOODRAND_01() * 5.0 + 2.5) + 0.5;
    return GOODRAND_01() < 0.5 ? res : -res;
}


int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // juliac by David Young, http://sc0t0ma.deviantart.com/
    double VAR(re) = 1.0 / (VAR(re) + SMALL_EPSILON);
    double VAR(im) = VAR(im) / 100.0;
    double arg = atan2(FTy, FTx) + fmod(GOODRAND_0X(INT_MAX), VAR(re)) * 2.0 * M_PI;
    double lnmod = VAR(dist) * 0.5 * log(FTx * FTx + FTy * FTy);
    double a = arg * VAR(re) + lnmod * VAR(im);
    double s = sin(a);
    double c = cos(a);
    double mod2 = exp(lnmod * VAR(re) - arg * VAR(im));

    FPx += VVAR * mod2 * c;
    FPy += VVAR * mod2 * s;

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
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class JuliaCFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_RE = "re";
//   private static final String PARAM_IM = "im";
//   private static final String PARAM_DIST = "dist";
//   private static final String[] paramNames = {PARAM_RE, PARAM_IM, PARAM_DIST};
// 
//   private double re = genRandomPower();
//   private double im = 0.0;
//   private double dist = 1.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // juliac by David Young, http://sc0t0ma.deviantart.com/
//     double re = 1.0 / (this.re + SMALL_EPSILON);
//     double im = this.im / 100.0;
//     double arg = atan2(pAffineTP.y, pAffineTP.x) + fmod(pContext.random(Integer.MAX_VALUE), this.re) * 2.0 * M_PI;
//     double lnmod = dist * 0.5 * log(pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y);
//     double a = arg * re + lnmod * im;
//     double s = sin(a);
//     double c = cos(a);
//     double mod2 = exp(lnmod * re - arg * im);
// 
//     pVarTP.x += pAmount * mod2 * c;
//     pVarTP.y += pAmount * mod2 * s;
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
//     return new Object[]{re, im, dist};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_RE.equalsIgnoreCase(pName)) {
//       re = pValue;
//     } else if (PARAM_IM.equalsIgnoreCase(pName))
//       im = pValue;
//     else if (PARAM_DIST.equalsIgnoreCase(pName))
//       dist = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "juliac";
//   }
// 
//   private double genRandomPower() {
//     double res = (int) (Math.random() * 5.0 + 2.5) + 0.5;
//     return Math.random() < 0.5 ? res : -res;
//   }
// 
//   @Override
//   public String[] getParameterAlternativeNames() {
//     return new String[]{"juliac_re", "juliac_im", "juliac_dist"};
//   }
// 
// }
// 
