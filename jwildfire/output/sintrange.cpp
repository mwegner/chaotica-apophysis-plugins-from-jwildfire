/*
    Apophysis Plugin: sintrange

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/SintrangeFunc.java

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
	double w;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "sintrange_"
#include "plugin.h"

APO_PLUGIN("sintrange");
APO_VARIABLES(
	VAR_REAL(w, 1.0),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Sintrange from Ffey, http://ffey.deviantart.com/art/apoplugin-Sintrange-245146228 */
    double v = ((sqr(FTx) + sqr(FTy)) * VAR(w));
    FPx = VVAR * (sin(FTx)) * (FTx * FTx + VAR(w) - v);
    FPy = VVAR * (sin(FTy)) * (FTy * FTy + VAR(w) - v);
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
// import static org.jwildfire.base.mathlib.MathLib.sin;
// import static org.jwildfire.base.mathlib.MathLib.sqr;
// 
// public class SintrangeFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_W = "w";
//   private static final String[] paramNames = {PARAM_W};
// 
//   private double w = 1.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Sintrange from Ffey, http://ffey.deviantart.com/art/apoplugin-Sintrange-245146228 */
//     double v = ((sqr(pAffineTP.x) + sqr(pAffineTP.y)) * w);
//     pVarTP.x = pAmount * (sin(pAffineTP.x)) * (pAffineTP.x * pAffineTP.x + w - v);
//     pVarTP.y = pAmount * (sin(pAffineTP.y)) * (pAffineTP.y * pAffineTP.y + w - v);
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
//     return new Object[]{w};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_W.equalsIgnoreCase(pName))
//       w = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "sintrange";
//   }
// 
// }
// 
