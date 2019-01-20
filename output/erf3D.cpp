#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: erf3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Erf3DFunc.java

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

#define APO_VARIABLE_PREFIX "erf3D_"
#include "plugin.h"

APO_PLUGIN("erf3D");
APO_VARIABLES(


);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // "erf3D" variation created by zephyrtronium implemented into JWildfire by darkbeam

    FPx += erf(FTx) * VVAR;
    FPy += erf(FTy) * VVAR;
    FPz += erf(FTz) * VVAR;


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
// import static org.jwildfire.base.mathlib.MathLib.erf;
// 
// 
// public class Erf3DFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // "erf3D" variation created by zephyrtronium implemented into JWildfire by darkbeam
// 
//     pVarTP.x += erf(pAffineTP.x) * pAmount;
//     pVarTP.y += erf(pAffineTP.y) * pAmount;
//     pVarTP.z += erf(pAffineTP.z) * pAmount;
//   }
// 
// 
//   @Override
//   public String getName() {
//     return "erf3D";
//   }
// 
// }
