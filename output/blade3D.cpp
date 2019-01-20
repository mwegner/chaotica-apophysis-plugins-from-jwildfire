#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: blade3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Blade3DFunc.java

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

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "blade3D_"
#include "plugin.h"

APO_PLUGIN("blade3D");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Z+ variation Jan 07
    procedure TXForm.Blade;
    var
      r, sinr, cosr: double;
    begin
      r := sqrt(sqr(FTx) + sqr(FTy))*vars[33];
      SinCos(r*random, sinr, cosr);
      FPx := FPx + vars[33] * FTx * (cosr + sinr);
      FPy := FPy + vars[33] * FTx * (cosr - sinr);
    end;
    */

    double r = GOODRAND_01() * VVAR * sqrt(FTx * FTx + FTy * FTy);
    double sinr = sin(r);
    double cosr = cos(r);
    FPx += VVAR * FTx * (cosr + sinr);
    FPy += VVAR * FTx * (cosr - sinr);
    FPz += VVAR * FTy * (sinr - cosr);


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
// public class Blade3DFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Z+ variation Jan 07
//     procedure TXForm.Blade;
//     var
//       r, sinr, cosr: double;
//     begin
//       r := sqrt(sqr(FTx) + sqr(FTy))*vars[33];
//       SinCos(r*random, sinr, cosr);
//       FPx := FPx + vars[33] * FTx * (cosr + sinr);
//       FPy := FPy + vars[33] * FTx * (cosr - sinr);
//     end;
//     */
// 
//     double r = pContext.random() * pAmount * sqrt(pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y);
//     double sinr = sin(r);
//     double cosr = cos(r);
//     pVarTP.x += pAmount * pAffineTP.x * (cosr + sinr);
//     pVarTP.y += pAmount * pAffineTP.x * (cosr - sinr);
//     pVarTP.z += pAmount * pAffineTP.y * (sinr - cosr);
//   }
// 
//   @Override
//   public String getName() {
//     return "blade3D";
//   }
// 
// }
// 
