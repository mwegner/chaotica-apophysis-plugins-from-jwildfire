#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: blob

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/BlobFunc.java

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
	double low;
	double high;
	double waves;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "blob_"
#include "plugin.h"

APO_PLUGIN("blob");
APO_VARIABLES(
	VAR_REAL(low, 0.3),
	VAR_REAL(high, 1.2),
	VAR_REAL(waves, 6),

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double a = atan2(FTx, FTy);
    double r = sqrt(FTx * FTx + FTy * FTy);
    r = r * (VAR(low) + (VAR(high) - VAR(low)) * (0.5 + 0.5 * sin(VAR(waves) * a)));
    double nx = sin(a) * r;
    double ny = cos(a) * r;

    FPx += VVAR * nx;
    FPy += VVAR * ny;
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
// public class BlobFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_LOW = "low";
//   private static final String PARAM_HIGH = "high";
//   private static final String PARAM_WAVES = "waves";
//   private static final String[] paramNames = {PARAM_LOW, PARAM_HIGH, PARAM_WAVES};
// 
//   private double low = 0.3;
//   private double high = 1.2;
//   private double waves = 6;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double a = atan2(pAffineTP.x, pAffineTP.y);
//     double r = sqrt(pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y);
//     r = r * (low + (high - low) * (0.5 + 0.5 * sin(waves * a)));
//     double nx = sin(a) * r;
//     double ny = cos(a) * r;
// 
//     pVarTP.x += pAmount * nx;
//     pVarTP.y += pAmount * ny;
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
//     return new Object[]{low, high, waves};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_LOW.equalsIgnoreCase(pName))
//       low = pValue;
//     else if (PARAM_HIGH.equalsIgnoreCase(pName))
//       high = pValue;
//     else if (PARAM_WAVES.equalsIgnoreCase(pName))
//       waves = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "blob";
//   }
// 
// }
// 
