#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: bTransform

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/BTransformFunc.java

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
	double rotate;
	int power;
	double move;
	double split;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "bTransform_"
#include "plugin.h"

APO_PLUGIN("bTransform");
APO_VARIABLES(
	VAR_REAL(rotate, 0.0),
	VAR_INTEGER(power, 1),
	VAR_REAL(move, 0.0),
	VAR_REAL(split, 0.0),

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // bTransform by Michael Faber, http://michaelfaber.deviantart.com/art/bSeries-320574477
    double tau, sigma;
    double temp;
    double cosht, sinht;
    double sins, coss;

    tau = 0.5 * (log(sqr(FTx + 1.0) + sqr(FTy)) - log(sqr(FTx - 1.0) + sqr(FTy))) / VAR(power) + VAR(move);
    sigma = M_PI - atan2(FTy, FTx + 1.0) - atan2(FTy, 1.0 - FTx) + VAR(rotate);
    sigma = sigma / VAR(power) + M_2PI / VAR(power) * floor(GOODRAND_01() * VAR(power));

    if (FTx >= 0.0)
      tau += VAR(split);
    else
      tau -= VAR(split);
    sinht = sinh(tau);
    cosht = cosh(tau);
    sins = sin(sigma);
    coss = cos(sigma);
    temp = cosht - coss;
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
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class BTransformFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_ROTATE = "rotate";
//   private static final String PARAM_POWER = "power";
//   private static final String PARAM_MOVE = "move";
//   private static final String PARAM_SPLIT = "split";
// 
//   private static final String[] paramNames = {PARAM_ROTATE, PARAM_POWER, PARAM_MOVE, PARAM_SPLIT};
// 
//   private double rotate = 0.0;
//   private int power = 1;
//   private double move = 0.0;
//   private double split = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // bTransform by Michael Faber, http://michaelfaber.deviantart.com/art/bSeries-320574477
//     double tau, sigma;
//     double temp;
//     double cosht, sinht;
//     double sins, coss;
// 
//     tau = 0.5 * (log(sqr(pAffineTP.x + 1.0) + sqr(pAffineTP.y)) - log(sqr(pAffineTP.x - 1.0) + sqr(pAffineTP.y))) / power + move;
//     sigma = M_PI - atan2(pAffineTP.y, pAffineTP.x + 1.0) - atan2(pAffineTP.y, 1.0 - pAffineTP.x) + rotate;
//     sigma = sigma / power + M_2PI / power * floor(pContext.random() * power);
// 
//     if (pAffineTP.x >= 0.0)
//       tau += split;
//     else
//       tau -= split;
//     sinht = sinh(tau);
//     cosht = cosh(tau);
//     sins = sin(sigma);
//     coss = cos(sigma);
//     temp = cosht - coss;
//     pVarTP.x += pAmount * sinht / temp;
//     pVarTP.y += pAmount * sins / temp;
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
//     return new Object[]{rotate, power, move, split};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_ROTATE.equalsIgnoreCase(pName))
//       rotate = pValue;
//     else if (PARAM_POWER.equalsIgnoreCase(pName))
//       power = limitIntVal(Tools.FTOI(pValue), 1, Integer.MAX_VALUE);
//     else if (PARAM_MOVE.equalsIgnoreCase(pName))
//       move = pValue;
//     else if (PARAM_SPLIT.equalsIgnoreCase(pName))
//       split = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "bTransform";
//   }
// 
// }
// 
