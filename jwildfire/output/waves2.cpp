/*
    Apophysis Plugin: waves2

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Waves2Func.java

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
	double scalex;
	double scaley;
	double freqx;
	double freqy;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "waves2_"
#include "plugin.h"

APO_PLUGIN("waves2");
APO_VARIABLES(
	VAR_REAL(scalex, 0.25),
	VAR_REAL(scaley, 0.5),
	VAR_REAL(freqx, M_PI / 2),
	VAR_REAL(freqy, M_PI / 4),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* waves2 from Joel F */
    FPx += VVAR * (FTx + VAR(scalex) * sin(FTy * VAR(freqx)));
    FPy += VVAR * (FTy + VAR(scaley) * sin(FTx * VAR(freqy)));
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
// import static org.jwildfire.base.mathlib.MathLib.M_PI;
// import static org.jwildfire.base.mathlib.MathLib.sin;
// 
// public class Waves2Func extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_SCALEX = "scalex";
//   private static final String PARAM_SCALEY = "scaley";
//   private static final String PARAM_FREQX = "freqx";
//   private static final String PARAM_FREQY = "freqy";
//   private static final String[] paramNames = {PARAM_SCALEX, PARAM_SCALEY, PARAM_FREQX, PARAM_FREQY};
// 
//   private double scalex = 0.25;
//   private double scaley = 0.5;
//   private double freqx = M_PI / 2;
//   private double freqy = M_PI / 4;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* waves2 from Joel F */
//     pVarTP.x += pAmount * (pAffineTP.x + scalex * sin(pAffineTP.y * freqx));
//     pVarTP.y += pAmount * (pAffineTP.y + scaley * sin(pAffineTP.x * freqy));
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
//     return new Object[]{scalex, scaley, freqx, freqy};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_SCALEX.equalsIgnoreCase(pName))
//       scalex = pValue;
//     else if (PARAM_SCALEY.equalsIgnoreCase(pName))
//       scaley = pValue;
//     else if (PARAM_FREQX.equalsIgnoreCase(pName))
//       freqx = pValue;
//     else if (PARAM_FREQY.equalsIgnoreCase(pName))
//       freqy = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "waves2";
//   }
// 
// }
// 
