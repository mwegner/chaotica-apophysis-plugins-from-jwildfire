#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: blur

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/BlurFunc.java

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

#define APO_VARIABLE_PREFIX "blur_"
#include "plugin.h"

APO_PLUGIN("blur");
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
    double r = GOODRAND_01() * (M_PI + M_PI);
    fsincos(r, &VAR(_sina), &VAR(_cosa));
    double r2 = VVAR * GOODRAND_01();
    FPx += r2 * VAR(_cosa);
    FPy += r2 * VAR(_sina);
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
// import org.jwildfire.base.mathlib.double;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.M_PI;
// import static org.jwildfire.base.mathlib.MathLib.sinAndCos;
// 
// public class BlurFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private double sina = 0.0;
//   private double cosa = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double r = pContext.random() * (M_PI + M_PI);
//     sinAndCos(r, sina, cosa);
//     double r2 = pAmount * pContext.random();
//     pVarTP.x += r2 * cosa.value;
//     pVarTP.y += r2 * sina.value;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "blur";
//   }
// 
// }
// 
