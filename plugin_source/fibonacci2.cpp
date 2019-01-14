/*
    Apophysis Plugin: fibonacci2

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Fibonacci2Func.java

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
	double sc;
	double sc2;
	double _ffive;
	double _fnatlog;
	double _M_SQRT5 = 2.2360679774997898;
	double _M_PHI = 1.61803398874989484820;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "fibonacci2_"
#include "plugin.h"

APO_PLUGIN("fibonacci2");
APO_VARIABLES(
	VAR_REAL(sc, 1.0),
	VAR_REAL(sc2, 1.0),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
   VAR(_M_SQRT5) = 2.2360679774997898;
   VAR(_M_PHI) = 1.61803398874989484820;
    VAR(_ffive) = 1.0 / VAR(_M_SQRT5);
    VAR(_fnatlog) = log(VAR(_M_PHI));

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // fibonacci2 by Larry Berlin, http://aporev.deviantart.com/gallery/#/d2blmhg
    //  p^z - (-p)^(-z)
    //z' = -----------------
    //      sqrt(5)
    //
    //Where p is the Golden Ratio.
    //This function generates the fibonacci sequence
    //for real integer values.
    //1 2 3 4 5 6  7  8  9 10 11  12  13  14  15 < Real Value
    //1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 < Fib Value
    //
    //Negative real integers produce the negative fibonacci sequence,
    //which is the same as the normal one, except every
    //other number is negative.
    //1 0 -1 -2 -3 -4 -5 -6 -7  -8 < Real Value
    //1 0  1 -1  3 -3  5 -8 13 -21 < Fib Value

    double a = FTy * VAR(_fnatlog);
    double snum1 = sin(a);
    double cnum1 = cos(a);
    double b = (FTx * M_PI + FTy * VAR(_fnatlog)) * -1.0;
    double snum2 = sin(b);
    double cnum2 = cos(b);

    double eradius1 = VAR(sc) * exp(VAR(sc2) * (FTx * VAR(_fnatlog)));
    double eradius2 = VAR(sc) * exp(VAR(sc2) * ((FTx * VAR(_fnatlog) - FTy * M_PI) * -1));

    FPx += VVAR * (eradius1 * cnum1 - eradius2 * cnum2) * VAR(_ffive);
    FPy += VVAR * (eradius1 * snum1 - eradius2 * snum2) * VAR(_ffive);
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
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class Fibonacci2Func extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_SC = "sc";
//   private static final String PARAM_SC2 = "sc2";
//   private static final String[] paramNames = {PARAM_SC, PARAM_SC2};
// 
//   private double sc = 1.0;
//   private double sc2 = 1.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // fibonacci2 by Larry Berlin, http://aporev.deviantart.com/gallery/#/d2blmhg
//     //  p^z - (-p)^(-z)
//     //z' = -----------------
//     //      sqrt(5)
//     //
//     //Where p is the Golden Ratio.
//     //This function generates the fibonacci sequence
//     //for real integer values.
//     //1 2 3 4 5 6  7  8  9 10 11  12  13  14  15 < Real Value
//     //1 1 2 3 5 8 13 21 34 55 89 144 233 377 610 < Fib Value
//     //
//     //Negative real integers produce the negative fibonacci sequence,
//     //which is the same as the normal one, except every
//     //other number is negative.
//     //1 0 -1 -2 -3 -4 -5 -6 -7  -8 < Real Value
//     //1 0  1 -1  3 -3  5 -8 13 -21 < Fib Value
// 
//     double a = pAffineTP.y * fnatlog;
//     double snum1 = sin(a);
//     double cnum1 = cos(a);
//     double b = (pAffineTP.x * M_PI + pAffineTP.y * fnatlog) * -1.0;
//     double snum2 = sin(b);
//     double cnum2 = cos(b);
// 
//     double eradius1 = sc * exp(sc2 * (pAffineTP.x * fnatlog));
//     double eradius2 = sc * exp(sc2 * ((pAffineTP.x * fnatlog - pAffineTP.y * M_PI) * -1));
// 
//     pVarTP.x += pAmount * (eradius1 * cnum1 - eradius2 * cnum2) * ffive;
//     pVarTP.y += pAmount * (eradius1 * snum1 - eradius2 * snum2) * ffive;
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
//     return new Object[]{sc, sc2};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_SC.equalsIgnoreCase(pName))
//       sc = pValue;
//     else if (PARAM_SC2.equalsIgnoreCase(pName))
//       sc2 = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "fibonacci2";
//   }
// 
//   private double ffive, fnatlog;
//   private final double M_SQRT5 = 2.2360679774997898;
//   private final double M_PHI = 1.61803398874989484820;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     ffive = 1.0 / M_SQRT5;
//     fnatlog = log(M_PHI);
//   }
// 
// }
// 
