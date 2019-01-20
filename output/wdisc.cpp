#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: wdisc

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/WDiscFunc.java

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

#define APO_VARIABLE_PREFIX "wdisc_"
#include "plugin.h"

APO_PLUGIN("wdisc");
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
    // wdisc my Michael Faber, http://michaelfaber.deviantart.com/art/The-Lost-Variations-258913970 */
    double a = M_PI / (sqrt(sqr(FTx) + sqr(FTy)) + 1.0);
    double r = atan2(FTy, FTx) * M_1_PI;

    if (r > 0.0)
      a = M_PI - a;

    fsincos(a, &VAR(_sina), &VAR(_cosa));

    FPx += VVAR * r * VAR(_cosa);
    FPy += VVAR * r * VAR(_sina);

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
// public class WDiscFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private double sina = 0.0;
//   private double cosa = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // wdisc my Michael Faber, http://michaelfaber.deviantart.com/art/The-Lost-Variations-258913970 */
//     double a = M_PI / (sqrt(sqr(pAffineTP.x) + sqr(pAffineTP.y)) + 1.0);
//     double r = atan2(pAffineTP.y, pAffineTP.x) * M_1_PI;
// 
//     if (r > 0.0)
//       a = M_PI - a;
// 
//     sinAndCos(a, sina, cosa);
// 
//     pVarTP.x += pAmount * r * cosa.value;
//     pVarTP.y += pAmount * r * sina.value;
// 
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "wdisc";
//   }
// 
// }
// 
