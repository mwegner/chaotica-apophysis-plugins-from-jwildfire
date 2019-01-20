#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: acoth

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/AcothFunc.java

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
#include "complexhelpers.h"


typedef struct
{

} Variables;

#define APO_VARIABLE_PREFIX "acoth_"
#include "plugin.h"

APO_PLUGIN("acoth");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{


    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    //acoth by Whittaker Courtney,
    //based on the hyperbolic variations by Tatyana Zabanova and DarkBeam's implementation of them.

    Complex z(FTx, FTy);
    z = complexAcotH(z);
    z = complexFlip(z);
    z = complexScale(z, VVAR * M_2_PI);

     FPx += z.real();
     FPy += z.imag();

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
// import org.jwildfire.base.mathlib.Complex;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.M_2_PI;
// 
// public class AcothFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     //acoth by Whittaker Courtney,
//     //based on the hyperbolic variations by Tatyana Zabanova and DarkBeam's implementation of them.
// 
//     Complex z = new Complex(pAffineTP.x, pAffineTP.y);
//     z.AcotH();
//     z.Flip();
// 
//     z.Scale(pAmount * M_2_PI);
// 
//     pVarTP.y += z.im;
//     pVarTP.x += z.re;
// 
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "acoth";
//   }
// 
// }
