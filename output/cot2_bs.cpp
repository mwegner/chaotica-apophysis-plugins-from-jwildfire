#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: cot2_bs

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Cot2_BSFunc.java

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
	double x1;
	double x2;
	double y1;
	double y2;

} Variables;

#define APO_VARIABLE_PREFIX "cot2_bs_"
#include "plugin.h"

APO_PLUGIN("cot2_bs");
APO_VARIABLES(
	VAR_REAL(x1, 2.0),
	VAR_REAL(x2, 2.0),
	VAR_REAL(y1, 2.0),
	VAR_REAL(y2, 2.0)

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* complex vars by cothe */
    /* exp log sin cos tan sec csc cot sinh cosh tanh sech csch coth */
    /* Variables added by Brad Stefanov */
    //Cotangent COT
    double cotsin = sin(VAR(x1) * FTx);
    double cotcos = cos(VAR(x2) * FTx);
    double cotsinh = sinh(VAR(y1) * FTy);
    double cotcosh = cosh(VAR(y2) * FTy);
    double cotden = 1.0 / (cotcosh - cotcos);
    FPx += VVAR * cotden * cotsin;
    FPy += VVAR * cotden * -1 * cotsinh;

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
// public class Cot2_BSFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_X1 = "x1";
//   private static final String PARAM_X2 = "x2";
//   private static final String PARAM_Y1 = "y1";
//   private static final String PARAM_Y2 = "y2";
//   private static final String[] paramNames = {PARAM_X1, PARAM_X2, PARAM_Y1, PARAM_Y2};
//   private double x1 = 2.0;
//   private double x2 = 2.0;
//   private double y1 = 2.0;
//   private double y2 = 2.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* complex vars by cothe */
//     /* exp log sin cos tan sec csc cot sinh cosh tanh sech csch coth */
//     /* Variables added by Brad Stefanov */
//     //Cotangent COT
//     double cotsin = sin(x1 * pAffineTP.x);
//     double cotcos = cos(x2 * pAffineTP.x);
//     double cotsinh = sinh(y1 * pAffineTP.y);
//     double cotcosh = cosh(y2 * pAffineTP.y);
//     double cotden = 1.0 / (cotcosh - cotcos);
//     pVarTP.x += pAmount * cotden * cotsin;
//     pVarTP.y += pAmount * cotden * -1 * cotsinh;
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
//     return new Object[]{x1, x2, y1, y2};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_X1.equalsIgnoreCase(pName))
//       x1 = pValue;
//     else if (PARAM_X2.equalsIgnoreCase(pName))
//       x2 = pValue;
//     else if (PARAM_Y1.equalsIgnoreCase(pName))
//       y1 = pValue;
//     else if (PARAM_Y2.equalsIgnoreCase(pName))
//       y2 = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "cot2_bs";
//   }
// 
// }
// 
