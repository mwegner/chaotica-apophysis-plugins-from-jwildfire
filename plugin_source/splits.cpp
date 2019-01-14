/*
    Apophysis Plugin: splits

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/SplitsFunc.java

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
	double x;
	double y;
	double lshear;
	double rshear;
	double ushear;
	double dshear;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "splits_"
#include "plugin.h"

APO_PLUGIN("splits");
APO_VARIABLES(
	VAR_REAL(x, 0.40),
	VAR_REAL(y, 0.60),
	VAR_REAL(lshear, 0.00),
	VAR_REAL(rshear, 0.00),
	VAR_REAL(ushear, 0.00),
	VAR_REAL(dshear, 0.00),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Splits from apo plugins pack; shears added by DarkBeam 2018 to emulate splits.dll */
    if (FTx >= 0) {
      FPx += VVAR * (FTx + VAR(x));
      FPy += VVAR * (VAR(rshear));
    } else {
      FPx += VVAR * (FTx - VAR(x));
      FPy -= VVAR * (VAR(lshear));
    }

    if (FTy >= 0) {
      FPy += VVAR * (FTy + VAR(y));
      FPx += VVAR * (VAR(ushear));
    } else {
      FPy += VVAR * (FTy - VAR(y));
      FPx -= VVAR * (VAR(dshear));
    }
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
//   This is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser 
//   General Public License as published by the Free Software Foundation; either version 2.1 of the 
//   License, or (at your option) any later version.
//  
//   This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
//   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
//   Lesser General Public License for more details.
//   You should have received a copy of the GNU Lesser General Public License along with this software; 
//   if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
//   02110-1301 USA, or see the FSF site: http://www.fsf.org.
// */
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class SplitsFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_X = "x";
//   private static final String PARAM_Y = "y";
//   private static final String PARAM_LSH = "lshear";
//   private static final String PARAM_RSH = "rshear";
//   private static final String PARAM_USH = "ushear";
//   private static final String PARAM_DSH = "dshear";
// 
//   private static final String[] paramNames = {PARAM_X, PARAM_Y, PARAM_LSH, PARAM_RSH, PARAM_USH, PARAM_DSH};
// 
//   private double x = 0.40;
//   private double y = 0.60;
//   private double lshear = 0.00;
//   private double rshear = 0.00;
//   private double ushear = 0.00;
//   private double dshear = 0.00;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Splits from apo plugins pack; shears added by DarkBeam 2018 to emulate splits.dll */
//     if (pAffineTP.x >= 0) {
//       pVarTP.x += pAmount * (pAffineTP.x + x);
//       pVarTP.y += pAmount * (rshear);
//     } else {
//       pVarTP.x += pAmount * (pAffineTP.x - x);
//       pVarTP.y -= pAmount * (lshear);
//     }
// 
//     if (pAffineTP.y >= 0) {
//       pVarTP.y += pAmount * (pAffineTP.y + y);
//       pVarTP.x += pAmount * (ushear);
//     } else {
//       pVarTP.y += pAmount * (pAffineTP.y - y);
//       pVarTP.x -= pAmount * (dshear);
//     }
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
//     return new Object[]{x, y, lshear, rshear, ushear, dshear};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_X.equalsIgnoreCase(pName))
//       x = pValue;
//     else if (PARAM_Y.equalsIgnoreCase(pName))
//       y = pValue;
//     else if (PARAM_LSH.equalsIgnoreCase(pName))
//       lshear = pValue;
//     else if (PARAM_RSH.equalsIgnoreCase(pName))
//       rshear = pValue;
//     else if (PARAM_USH.equalsIgnoreCase(pName))
//       ushear = pValue;
//     else if (PARAM_DSH.equalsIgnoreCase(pName))
//       dshear = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "splits";
//   }
// 
// }
// 
