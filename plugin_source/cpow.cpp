/*
    Apophysis Plugin: cpow

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CPowFunc.java

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
	double r;
	double i;
	double power;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "cpow_"
#include "plugin.h"

APO_PLUGIN("cpow");
APO_VARIABLES(
	VAR_REAL(r, 1.0),
	VAR_REAL(i, 0.1),
	VAR_REAL(power, 1.5),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Cpow in the Apophysis Plugin Pack */
    double a = atan2(FTx, FTy);
    double lnr = 0.5 * log((FTx * FTx + FTy * FTy));
    double va = 2.0 * M_PI / VAR(power);
    double vc = VAR(r) / VAR(power);
    double vd = VAR(i) / VAR(power);
    double ang = vc * a + vd * lnr + va * floor(VAR(power) * GOODRAND_01());

    double m = VVAR * exp(vc * lnr - vd * a);
    double sa = sin(ang);
    double ca = cos(ang);

    FPx += m * ca;
    FPy += m * sa;
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
// public class CPowFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_R = "r";
//   private static final String PARAM_I = "i";
//   private static final String PARAM_POWER = "power";
// 
//   private static final String[] paramNames = {PARAM_R, PARAM_I, PARAM_POWER};
// 
//   private double r = 1.0;
//   private double i = 0.1;
//   private double power = 1.5;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Cpow in the Apophysis Plugin Pack */
//     double a = pAffineTP.getPrecalcAtanYX();
//     double lnr = 0.5 * log(pAffineTP.getPrecalcSumsq());
//     double va = 2.0 * M_PI / power;
//     double vc = r / power;
//     double vd = i / power;
//     double ang = vc * a + vd * lnr + va * floor(power * pContext.random());
// 
//     double m = pAmount * exp(vc * lnr - vd * a);
//     double sa = sin(ang);
//     double ca = cos(ang);
// 
//     pVarTP.x += m * ca;
//     pVarTP.y += m * sa;
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
//     return new Object[]{r, i, power};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_R.equalsIgnoreCase(pName))
//       r = pValue;
//     else if (PARAM_I.equalsIgnoreCase(pName))
//       i = pValue;
//     else if (PARAM_POWER.equalsIgnoreCase(pName))
//       power = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "cpow";
//   }
// 
// }
// 
