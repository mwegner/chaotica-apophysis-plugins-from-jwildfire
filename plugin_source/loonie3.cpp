/*
    Apophysis Plugin: loonie3

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Loonie3Func.java

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
	double _sqrvvar;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "loonie3_"
#include "plugin.h"

APO_PLUGIN("loonie3");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
    VAR(_sqrvvar) = VVAR * VVAR;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* loonie2 by dark-beam, http://dark-beam.deviantart.com/art/Loonie2-update-2-Loonie3-457414891 */
    double r2 = 2 * VAR(_sqrvvar);
    if (FTx > SMALL_EPSILON) {
      r2 = sqr((sqr(FTx) + sqr(FTy)) / FTx);
    }
    if (r2 < VAR(_sqrvvar)) {
      double r = VVAR * sqrt(VAR(_sqrvvar) / r2 - 1.0);
      FPx += r * FTx;
      FPy += r * FTy;
    } else {
      FPx += VVAR * FTx;
      FPy += VVAR * FTy;
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
// public class Loonie3Func extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* loonie2 by dark-beam, http://dark-beam.deviantart.com/art/Loonie2-update-2-Loonie3-457414891 */
//     double r2 = 2 * _sqrvvar;
//     if (pAffineTP.x > SMALL_EPSILON) {
//       r2 = sqr((sqr(pAffineTP.x) + sqr(pAffineTP.y)) / pAffineTP.x);
//     }
//     if (r2 < _sqrvvar) {
//       double r = pAmount * sqrt(_sqrvvar / r2 - 1.0);
//       pVarTP.x += r * pAffineTP.x;
//       pVarTP.y += r * pAffineTP.y;
//     } else {
//       pVarTP.x += pAmount * pAffineTP.x;
//       pVarTP.y += pAmount * pAffineTP.y;
//     }
// 
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
// 
//   }
// 
//   @Override
//   public String getName() {
//     return "loonie3";
//   }
// 
//   private double _sqrvvar;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _sqrvvar = pAmount * pAmount;
//   }
// 
// }
// 
