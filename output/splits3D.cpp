#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: splits3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Splits3DFunc.java

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
	double x;
	double y;
	double z;

} Variables;

#define APO_VARIABLE_PREFIX "splits3D_"
#include "plugin.h"

APO_PLUGIN("splits3D");
APO_VARIABLES(
	VAR_REAL(x, 0.1),
	VAR_REAL(y, 0.3),
	VAR_REAL(z, 0.2)

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* splits3D by TyrantWave, http://tyrantwave.deviantart.com/art/Splits3D-Plugin-107262795 */
    if (FTx >= 0) {
      FPx += VVAR * (FTx + VAR(x));
    } else {
      FPx += VVAR * (FTx - VAR(x));
    }

    if (FTy >= 0) {
      FPy += VVAR * (FTy + VAR(y));
    } else {
      FPy += VVAR * (FTy - VAR(y));
    }

    if (FTz >= 0) {
      FPz += VVAR * (FTz + VAR(z));
    } else {
      FPz += VVAR * (FTz - VAR(z));
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
// public class Splits3DFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_X = "x";
//   private static final String PARAM_Y = "y";
//   private static final String PARAM_Z = "z";
// 
//   private static final String[] paramNames = {PARAM_X, PARAM_Y, PARAM_Z};
// 
//   private double x = 0.1;
//   private double y = 0.3;
//   private double z = 0.2;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* splits3D by TyrantWave, http://tyrantwave.deviantart.com/art/Splits3D-Plugin-107262795 */
//     if (pAffineTP.x >= 0) {
//       pVarTP.x += pAmount * (pAffineTP.x + x);
//     } else {
//       pVarTP.x += pAmount * (pAffineTP.x - x);
//     }
// 
//     if (pAffineTP.y >= 0) {
//       pVarTP.y += pAmount * (pAffineTP.y + y);
//     } else {
//       pVarTP.y += pAmount * (pAffineTP.y - y);
//     }
// 
//     if (pAffineTP.z >= 0) {
//       pVarTP.z += pAmount * (pAffineTP.z + z);
//     } else {
//       pVarTP.z += pAmount * (pAffineTP.z - z);
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
//     return new Object[]{x, y, z};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_X.equalsIgnoreCase(pName))
//       x = pValue;
//     else if (PARAM_Y.equalsIgnoreCase(pName))
//       y = pValue;
//     else if (PARAM_Z.equalsIgnoreCase(pName))
//       z = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "splits3D";
//   }
// 
// }
// 
