#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: edisc

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/EDiscFunc.java

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

#define APO_VARIABLE_PREFIX "edisc_"
#include "plugin.h"

APO_PLUGIN("edisc");
APO_VARIABLES(


);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Edisc in the Apophysis Plugin Pack */

    double tmp = (FTx * FTx + FTy * FTy) + 1.0;
    double tmp2 = 2.0 * FTx;
    double r1 = sqrt(tmp + tmp2);
    double r2 = sqrt(tmp - tmp2);
    double xmax = (r1 + r2) * 0.5;
    double a1 = log(xmax + sqrt(xmax - 1.0));
    double a2 = -acos(FTx / xmax);
    double w = VVAR / 11.57034632;

    double snv = sin(a1);
    double csv = cos(a1);
    double snhu = sinh(a2);
    double cshu = cosh(a2);

    if (FTy > 0.0) {
      snv = -snv;
    }

    FPx += w * cshu * csv;
    FPy += w * snhu * snv;
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
// public class EDiscFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Edisc in the Apophysis Plugin Pack */
// 
//     double tmp = pAffineTP.getPrecalcSumsq() + 1.0;
//     double tmp2 = 2.0 * pAffineTP.x;
//     double r1 = sqrt(tmp + tmp2);
//     double r2 = sqrt(tmp - tmp2);
//     double xmax = (r1 + r2) * 0.5;
//     double a1 = log(xmax + sqrt(xmax - 1.0));
//     double a2 = -acos(pAffineTP.x / xmax);
//     double w = pAmount / 11.57034632;
// 
//     double snv = sin(a1);
//     double csv = cos(a1);
//     double snhu = sinh(a2);
//     double cshu = cosh(a2);
// 
//     if (pAffineTP.y > 0.0) {
//       snv = -snv;
//     }
// 
//     pVarTP.x += w * cshu * csv;
//     pVarTP.y += w * snhu * snv;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "edisc";
//   }
// 
// }
// 
