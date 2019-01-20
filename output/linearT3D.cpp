#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: linearT3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/LinearT3DFunc.java

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
	double powX;
	double powY;
	double powZ;

} Variables;

#define APO_VARIABLE_PREFIX "linearT3D_"
#include "plugin.h"

APO_PLUGIN("linearT3D");
APO_VARIABLES(
	VAR_REAL(powX, 1.2),
	VAR_REAL(powY, 1.2),
	VAR_REAL(powZ, 1.2)

);


double sgn (Variation* vp, double arg) {

    if (arg > 0)
      return 1.0;
    else
      return -1.0;
}


int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // linearT3D by FractalDesire, http://fractaldesire.deviantart.com/journal/linearT-plugin-219864320
    FPx += sgn(vp, FTx) * pow(fabs(FTx), VAR(powX)) * VVAR;
    FPy += sgn(vp, FTy) * pow(fabs(FTy), VAR(powY)) * VVAR;
    FPz += sgn(vp, FTz) * pow(fabs(FTz), VAR(powZ)) * VVAR;


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
// import static org.jwildfire.base.mathlib.MathLib.fabs;
// import static org.jwildfire.base.mathlib.MathLib.pow;
// 
// public class LinearT3DFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_POWX = "powX";
//   private static final String PARAM_POWY = "powY";
//   private static final String PARAM_POWZ = "powZ";
// 
//   private static final String[] paramNames = {PARAM_POWX, PARAM_POWY, PARAM_POWZ};
// 
//   private double powX = 1.2;
//   private double powY = 1.2;
//   private double powZ = 1.2;
// 
//   private double sgn(double arg) {
//     if (arg > 0)
//       return 1.0;
//     else
//       return -1.0;
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // linearT3D by FractalDesire, http://fractaldesire.deviantart.com/journal/linearT-plugin-219864320
//     pVarTP.x += sgn(pAffineTP.x) * pow(fabs(pAffineTP.x), this.powX) * pAmount;
//     pVarTP.y += sgn(pAffineTP.y) * pow(fabs(pAffineTP.y), this.powY) * pAmount;
//     pVarTP.z += sgn(pAffineTP.z) * pow(fabs(pAffineTP.z), this.powZ) * pAmount;
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{powX, powY, powZ};
//   }
// 
//   @Override
//   public String[] getParameterAlternativeNames() {
//     return new String[]{"lT_powX", "lT_powY", "lT_powZ"};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_POWX.equalsIgnoreCase(pName))
//       powX = pValue;
//     else if (PARAM_POWY.equalsIgnoreCase(pName))
//       powY = pValue;
//     else if (PARAM_POWZ.equalsIgnoreCase(pName))
//       powZ = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "linearT3D";
//   }
// 
// }
// 
