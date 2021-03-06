#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: bSwirl

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/BSwirlFunc.java

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
	double in;
	double out;

} Variables;

#define APO_VARIABLE_PREFIX "bSwirl_"
#include "plugin.h"

APO_PLUGIN("bSwirl");
APO_VARIABLES(
	VAR_REAL(in, 0.0),
	VAR_REAL(out, 0.0)

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // bSwirl by Michael Faber, http://michaelfaber.deviantart.com/art/bSeries-320574477
    double tau, sigma;
    double temp;
    double cosht, sinht;
    double sins, coss;

    tau = 0.5 * (log(sqr(FTx + 1.0) + sqr(FTy)) - log(sqr(FTx - 1.0) + sqr(FTy)));
    sigma = M_PI - atan2(FTy, FTx + 1.0) - atan2(FTy, 1.0 - FTx);

    sigma = sigma + tau * VAR(out) + VAR(in) / tau;

    sinht = sinh(tau);
    cosht = cosh(tau);
    sins = sin(sigma);
    coss = cos(sigma);
    temp = cosht - coss;
    if (temp == 0) {
      return TRUE;
    }
    FPx += VVAR * sinht / temp;
    FPy += VVAR * sins / temp;

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
// public class BSwirlFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_IN = "in";
//   private static final String PARAM_OUT = "out";
// 
//   private static final String[] paramNames = {PARAM_IN, PARAM_OUT};
// 
//   private double in = 0.0;
//   private double out = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // bSwirl by Michael Faber, http://michaelfaber.deviantart.com/art/bSeries-320574477
//     double tau, sigma;
//     double temp;
//     double cosht, sinht;
//     double sins, coss;
// 
//     tau = 0.5 * (log(sqr(pAffineTP.x + 1.0) + sqr(pAffineTP.y)) - log(sqr(pAffineTP.x - 1.0) + sqr(pAffineTP.y)));
//     sigma = M_PI - atan2(pAffineTP.y, pAffineTP.x + 1.0) - atan2(pAffineTP.y, 1.0 - pAffineTP.x);
// 
//     sigma = sigma + tau * out + in / tau;
// 
//     sinht = sinh(tau);
//     cosht = cosh(tau);
//     sins = sin(sigma);
//     coss = cos(sigma);
//     temp = cosht - coss;
//     if (temp == 0) {
//       return;
//     }
//     pVarTP.x += pAmount * sinht / temp;
//     pVarTP.y += pAmount * sins / temp;
// 
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
//     return new Object[]{in, out};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_IN.equalsIgnoreCase(pName))
//       in = pValue;
//     else if (PARAM_OUT.equalsIgnoreCase(pName))
//       out = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "bSwirl";
//   }
// 
// }
// 
