/*
    Apophysis Plugin: plusrecip

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PlusRecipFunc.java

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
	double ar;
	double ai;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "plusrecip_"
#include "plugin.h"

APO_PLUGIN("plusrecip");
APO_VARIABLES(
	VAR_REAL(ar, 4.0),
	VAR_REAL(ai, 0.0),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // author DarkBeam. Implemented by DarkBeam 2019
    Complex z = new Complex(FTx, FTy);
    Complex k = new Complex(z);
    Complex a = new Complex(VAR(ar), VAR(ai));
    double aa = sqrt(a.Mag2eps());
    k.Sqr();
    k.Sub(a);
    k.Sqrt();
    k.Add(z);
    z.Copy(k);
    z.Sqr();

    if (sqrt(z.Mag2eps()) < aa) {  // forces it to stay in its half plane but ONLY when imag(a) = 0.0 Else... ;)
      k.Conj();
      a.Scale(-1.0 / aa);
      k.Mul(a);
    }

    if (k.re < 0) {
      k.Neg(); // fixes the issue when imag(a) != 0.0
    }

    k.Scale(VVAR);
    FPx += k.re;
    FPy += k.im;
    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }


    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.base.mathlib.Complex;
// import static org.jwildfire.base.mathlib.MathLib.sqrt;
// 
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class PlusRecipFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_AR = "ar";
//   private static final String PARAM_AI = "ai";
// 
//   private static final String[] paramNames = {PARAM_AR, PARAM_AI};
// 
//   private double ar = 4.0;
//   private double ai = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // author DarkBeam. Implemented by DarkBeam 2019
//     Complex z = new Complex(pAffineTP.x, pAffineTP.y);
//     Complex k = new Complex(z);
//     Complex a = new Complex(ar, ai);
//     double aa = sqrt(a.Mag2eps());
//     k.Sqr();
//     k.Sub(a);
//     k.Sqrt();
//     k.Add(z);
//     z.Copy(k);
//     z.Sqr();
// 
//     if (sqrt(z.Mag2eps()) < aa) {  // forces it to stay in its half plane but ONLY when imag(a) = 0. Else... ;)
//       k.Conj();
//       a.Scale(-1.0 / aa);
//       k.Mul(a);
//     }
// 
//     if (k.re < 0) {
//       k.Neg(); // fixes the issue when imag(a) != 0.
//     }
// 
//     k.Scale(pAmount);
//     pVarTP.x += k.re;
//     pVarTP.y += k.im;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
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
//     return new Object[]{ar, ai};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_AR.equalsIgnoreCase(pName))
//       ar = pValue;
//     else if (PARAM_AI.equalsIgnoreCase(pName))
//       ai = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "plusrecip";
//   }
// 
// }
