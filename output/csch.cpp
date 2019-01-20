#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: csch

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CschFunc.java

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

#define APO_VARIABLE_PREFIX "csch_"
#include "plugin.h"

APO_PLUGIN("csch");
APO_VARIABLES(


);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* complex vars by cothe */
    /* exp log sin cos tan sec csc cot sinh cosh tanh sech csch coth */
    //Hyperbolic Cosecant CSCH
    double cschsin = sin(FTy);
    double cschcos = cos(FTy);
    double cschsinh = sinh(FTx);
    double cschcosh = cosh(FTx);
    double d = (cosh(2.0 * FTx) - cos(2.0 * FTy));
    if (d == 0) {
      return TRUE;
    }
    double cschden = 2.0 / d;
    FPx += VVAR * cschden * cschsinh * cschcos;
    FPy -= VVAR * cschden * cschcosh * cschsin;
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
// public class CschFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* complex vars by cothe */
//     /* exp log sin cos tan sec csc cot sinh cosh tanh sech csch coth */
//     //Hyperbolic Cosecant CSCH
//     double cschsin = sin(pAffineTP.y);
//     double cschcos = cos(pAffineTP.y);
//     double cschsinh = sinh(pAffineTP.x);
//     double cschcosh = cosh(pAffineTP.x);
//     double d = (cosh(2.0 * pAffineTP.x) - cos(2.0 * pAffineTP.y));
//     if (d == 0) {
//       return;
//     }
//     double cschden = 2.0 / d;
//     pVarTP.x += pAmount * cschden * cschsinh * cschcos;
//     pVarTP.y -= pAmount * cschden * cschcosh * cschsin;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "csch";
//   }
// 
// }
// 
