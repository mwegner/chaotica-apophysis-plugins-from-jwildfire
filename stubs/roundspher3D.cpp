#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: roundspher3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/RoundSpher3DFunc.java

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

} Variables;

#define APO_VARIABLE_PREFIX "roundspher3D_"
#include "plugin.h"

APO_PLUGIN("roundspher3D");
APO_VARIABLES(


);


int PluginVarPrepare(Variation* vp)
{
    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
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
// public class RoundSpher3DFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* roundspher3D by Larry Berlin, http://aporev.deviantart.com/art/3D-Plugins-Collection-One-138514007?q=gallery%3Aaporev%2F8229210&qo=15 */
//     double inZ = pAffineTP.z;
//     double otherZ = pVarTP.z;
//     double f = sqrt(sqr(pAffineTP.x) + sqr(pAffineTP.y));
//     double tempTZ, tempPZ;
//     if (inZ == 0.0) {
//       tempTZ = cos(f);
//     } else {
//       tempTZ = pAffineTP.z;
//     }
//     if (otherZ == 0.0) {
//       tempPZ = cos(f);
//     } else {
//       tempPZ = pVarTP.z;
//     }
//     double d = sqr(pAffineTP.x) + sqr(pAffineTP.y) + sqr(tempTZ);
//     double e = 1.0 / d + sqr(M_2_PI);
// 
//     pVarTP.x += pAmount * (pAmount / d * pAffineTP.x / e);
//     pVarTP.y += pAmount * (pAmount / d * pAffineTP.y / e);
//     pVarTP.z = tempPZ + pAmount * (pAmount / d * tempTZ / e);
//   }
// 
//   @Override
//   public String getName() {
//     return "roundspher3D";
//   }
// 
// }
// 
