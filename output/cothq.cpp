#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: cothq

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CothqFunc.java

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

#define APO_VARIABLE_PREFIX "cothq_"
#include "plugin.h"

APO_PLUGIN("cothq");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Cothq by zephyrtronium http://zephyrtronium.deviantart.com/art/Quaternion-Apo-Plugin-Pack-165451482 */


    double abs_v = hypot(FTy, FTz);
    double s = sin(abs_v);
    double c = cos(abs_v);
    double sh = sinh(FTx);
    double ch = cosh(FTx);
    double sysz = sqr(FTy) + sqr(FTz);
    double ni = VVAR / (sqr(FTx) + sysz);
    double C = ch * s / abs_v;
    double B = sh * s / abs_v;
    double stcv = sh * c;
    double nstcv = -stcv;
    double ctcv = ch * c;

    FPx += (stcv * ctcv + C * B * sysz) * ni;
    FPy += (nstcv * B * FTy + C * FTy * ctcv) * ni;
    FPz += (nstcv * B * FTz + C * FTz * ctcv) * ni;




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
// import odk.lang.FastMath;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class CothqFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Cothq by zephyrtronium http://zephyrtronium.deviantart.com/art/Quaternion-Apo-Plugin-Pack-165451482 */
// 
// 
//     double abs_v = FastMath.hypot(pAffineTP.y, pAffineTP.z);
//     double s = sin(abs_v);
//     double c = cos(abs_v);
//     double sh = sinh(pAffineTP.x);
//     double ch = cosh(pAffineTP.x);
//     double sysz = sqr(pAffineTP.y) + sqr(pAffineTP.z);
//     double ni = pAmount / (sqr(pAffineTP.x) + sysz);
//     double C = ch * s / abs_v;
//     double B = sh * s / abs_v;
//     double stcv = sh * c;
//     double nstcv = -stcv;
//     double ctcv = ch * c;
// 
//     pVarTP.x += (stcv * ctcv + C * B * sysz) * ni;
//     pVarTP.y += (nstcv * B * pAffineTP.y + C * pAffineTP.y * ctcv) * ni;
//     pVarTP.z += (nstcv * B * pAffineTP.z + C * pAffineTP.z * ctcv) * ni;
// 
// 
//   }
// 
//   @Override
//   public String getName() {
//     return "cothq";
//   }
// 
// }
// 
