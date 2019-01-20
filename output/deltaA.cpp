#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: deltaA

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/DeltaAFunc.java

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
	double _sina = 0.0;
	double _cosa = 0.0;

} Variables;

#define APO_VARIABLE_PREFIX "deltaA_"
#include "plugin.h"

APO_PLUGIN("deltaA");
APO_VARIABLES(


);



int PluginVarPrepare(Variation* vp)
{
   VAR(_sina) = 0.0;
   VAR(_cosa) = 0.0;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // deltaA my Michael Faber, http://michaelfaber.deviantart.com/art/The-Lost-Variations-258913970 */
    double avgr = VVAR * (sqrt(sqr(FTy) + sqr(FTx + 1.0)) / sqrt(sqr(FTy) + sqr(FTx - 1.0)));
    double avga = (atan2(FTy, FTx - 1.0) - atan2(FTy, FTx + 1.0)) / 2.0;
    fsincos(avga, &VAR(_sina), &VAR(_cosa));

    FPx += avgr * VAR(_cosa);
    FPy += avgr * VAR(_sina);
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
// import odk.lang.double;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class DeltaAFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private double sina = 0.0;
//   private double cosa = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // deltaA my Michael Faber, http://michaelfaber.deviantart.com/art/The-Lost-Variations-258913970 */
//     double avgr = pAmount * (sqrt(sqr(pAffineTP.y) + sqr(pAffineTP.x + 1.0)) / sqrt(sqr(pAffineTP.y) + sqr(pAffineTP.x - 1.0)));
//     double avga = (atan2(pAffineTP.y, pAffineTP.x - 1.0) - atan2(pAffineTP.y, pAffineTP.x + 1.0)) / 2.0;
//     sinAndCos(avga, sina, cosa);
// 
//     pVarTP.x += avgr * cosa.value;
//     pVarTP.y += avgr * sina.value;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "deltaA";
//   }
// 
// }
// 
