/*
    Apophysis Plugin: butterfly3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Butterfly3DFunc.java

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

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "butterfly3D_"
#include "plugin.h"

APO_PLUGIN("butterfly3D");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* wx is weight*4/sqrt(3*pi) */
    double wx = VVAR * 1.3029400317411197908970256609023;

    double y2 = FTy * 2.0;
    double r = wx * sqrt(fabs(FTy * FTx) / (SMALL_EPSILON + FTx * FTx + y2 * y2));

    FPx += r * FTx;
    FPy += r * y2;
    FPz += r * fabs(y2) * sqrt(FTx * FTx + FTy * FTy) / 4.0;


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
// public class Butterfly3DFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* wx is weight*4/sqrt(3*pi) */
//     double wx = pAmount * 1.3029400317411197908970256609023;
// 
//     double y2 = pAffineTP.y * 2.0;
//     double r = wx * sqrt(fabs(pAffineTP.y * pAffineTP.x) / (SMALL_EPSILON + pAffineTP.x * pAffineTP.x + y2 * y2));
// 
//     pVarTP.x += r * pAffineTP.x;
//     pVarTP.y += r * y2;
//     pVarTP.z += r * fabs(y2) * sqrt(pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y) / 4.0;
//   }
// 
//   @Override
//   public String getName() {
//     return "butterfly3D";
//   }
// 
// }
// 
