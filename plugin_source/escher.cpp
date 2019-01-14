/*
    Apophysis Plugin: escher

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/EscherFunc.java

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
	double beta;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "escher_"
#include "plugin.h"

APO_PLUGIN("escher");
APO_VARIABLES(
	VAR_REAL(beta, 0.30),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Escher in the Apophysis Plugin Pack */

    double a = atan2(FTx, FTy);
    double lnr = 0.5 * log((FTx * FTx + FTy * FTy));

    double seb = sin(VAR(beta));
    double ceb = cos(VAR(beta));

    double vc = 0.5 * (1.0 + ceb);
    double vd = 0.5 * seb;

    double m = VVAR * exp(vc * lnr - vd * a);
    double n = vc * a + vd * lnr;

    double sn = sin(n);
    double cn = cos(n);

    FPx += m * cn;
    FPy += m * sn;
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
// public class EscherFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_BETA = "beta";
// 
//   private static final String[] paramNames = {PARAM_BETA};
// 
//   private double beta = 0.30;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Escher in the Apophysis Plugin Pack */
// 
//     double a = pAffineTP.getPrecalcAtanYX();
//     double lnr = 0.5 * log(pAffineTP.getPrecalcSumsq());
// 
//     double seb = sin(beta);
//     double ceb = cos(beta);
// 
//     double vc = 0.5 * (1.0 + ceb);
//     double vd = 0.5 * seb;
// 
//     double m = pAmount * exp(vc * lnr - vd * a);
//     double n = vc * a + vd * lnr;
// 
//     double sn = sin(n);
//     double cn = cos(n);
// 
//     pVarTP.x += m * cn;
//     pVarTP.y += m * sn;
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
//     return new Object[]{beta};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_BETA.equalsIgnoreCase(pName))
//       beta = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "escher";
//   }
// 
// }
// 
