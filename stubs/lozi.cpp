#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: lozi

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/LoziFunc.java

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
	double a;
	double b;
	double c;

} Variables;

#define APO_VARIABLE_PREFIX "lozi_"
#include "plugin.h"

APO_PLUGIN("lozi");
APO_VARIABLES(
	VAR_REAL(a, 0.5),
	VAR_REAL(b, 1.0),
	VAR_REAL(c, 1.0),

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
//   even the implied warranty of MERCHANTABILITY or FITNESS FOR a PARTICULAR PURPOSE. See the GNU 
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
// import static org.jwildfire.base.mathlib.MathLib.fabs;
// 
// public class LoziFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_A = "a";
//   private static final String PARAM_B = "b";
//   private static final String PARAM_C = "c";
// 
//   private static final String[] paramNames = {PARAM_A, PARAM_B, PARAM_C};
//   private double a = 0.5;
//   private double b = 1.0;
//   private double c = 1.0;
// 
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP,
//                         // Lozi by TyrantWave
//                         // https://www.deviantart.com/tyrantwave/art/Henon-and-Lozi-Apo-Plugins-125039554
//                         double pAmount) {
// 
// 
//     pVarTP.x += (c - (a * fabs(pAffineTP.x)) + pAffineTP.y) * pAmount;
//     pVarTP.y += b * pAffineTP.x * pAmount;
// 
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
// 
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{a, b, c};
//   }
// 
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_A.equalsIgnoreCase(pName)) {
//       a = pValue;
//     } else if (PARAM_B.equalsIgnoreCase(pName)) {
//       b = pValue;
//     } else if (PARAM_C.equalsIgnoreCase(pName)) {
//       c = pValue;
//     } else {
//       System.out.println("pName not recognized: " + pName);
//       throw new IllegalArgumentException(pName);
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "lozi";
//   }
// 
// }
// 
