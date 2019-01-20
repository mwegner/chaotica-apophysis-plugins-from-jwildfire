#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: cross

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CrossFunc.java

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

} Variables;

#define APO_VARIABLE_PREFIX "cross_"
#include "plugin.h"

APO_PLUGIN("cross");
APO_VARIABLES(


);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Z+ variation Jan 07
    procedure TXForm.Cross;
    var
      r: double;
    begin
      r := vars[36]*sqrt(1/(sqr(sqr(FTx)-sqr(FTy))+EPS));
      FPx := FPx + FTx * r;
      FPy := FPy + FTy * r;
    end;
    */

    double s = FTx * FTx - FTy * FTy;
    double r = VVAR * sqrt(1.0 / (s * s + SMALL_EPSILON));

    FPx += FTx * r;
    FPy += FTy * r;
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
// import static org.jwildfire.base.mathlib.MathLib.SMALL_EPSILON;
// import static org.jwildfire.base.mathlib.MathLib.sqrt;
// 
// public class CrossFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Z+ variation Jan 07
//     procedure TXForm.Cross;
//     var
//       r: double;
//     begin
//       r := vars[36]*sqrt(1/(sqr(sqr(FTx)-sqr(FTy))+EPS));
//       FPx := FPx + FTx * r;
//       FPy := FPy + FTy * r;
//     end;
//     */
// 
//     double s = pAffineTP.x * pAffineTP.x - pAffineTP.y * pAffineTP.y;
//     double r = pAmount * sqrt(1.0 / (s * s + SMALL_EPSILON));
// 
//     pVarTP.x += pAffineTP.x * r;
//     pVarTP.y += pAffineTP.y * r;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "cross";
//   }
// 
// }
// 
