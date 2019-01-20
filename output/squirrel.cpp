#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: squirrel

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/SquirrelFunc.java

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

} Variables;

#define APO_VARIABLE_PREFIX "squirrel_"
#include "plugin.h"

APO_PLUGIN("squirrel");
APO_VARIABLES(
	VAR_REAL(a, 1.0),
	VAR_REAL(b, 1.0)

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // squirrel by Raykoid666, http://raykoid666.deviantart.com/art/re-pack-1-new-plugins-100092186 
    double u = (VAR(a) + EPSILON) * sqr(FTx) + (VAR(b) + EPSILON) * sqr(FTy);

    FPx = cos(sqrt(u)) * tan(FTx) * VVAR;
    FPy = sin(sqrt(u)) * tan(FTy) * VVAR;

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
// public class SquirrelFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_A = "a";
//   private static final String PARAM_B = "b";
// 
//   private static final String[] paramNames = {PARAM_A, PARAM_B};
// 
//   private double a = 1.0;
//   private double b = 1.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // squirrel by Raykoid666, http://raykoid666.deviantart.com/art/re-pack-1-new-plugins-100092186 
//     double u = (a + EPSILON) * sqr(pAffineTP.x) + (b + EPSILON) * sqr(pAffineTP.y);
// 
//     pVarTP.x = cos(sqrt(u)) * tan(pAffineTP.x) * pAmount;
//     pVarTP.y = sin(sqrt(u)) * tan(pAffineTP.y) * pAmount;
// 
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{a, b};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_A.equalsIgnoreCase(pName))
//       a = pValue;
//     else if (PARAM_B.equalsIgnoreCase(pName))
//       b = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "squirrel";
//   }
// 
// }
// 
