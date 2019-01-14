/*
    Apophysis Plugin: spherical3D_wf

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Spherical3DWFFunc.java

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
	int invert;
	double exponent;
	bool _regularForm;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "spherical3D_wf_"
#include "plugin.h"

APO_PLUGIN("spherical3D_wf");
APO_VARIABLES(
	VAR_INTEGER(invert, 0),
	VAR_REAL(exponent, 2.0),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
    VAR(_regularForm) = fabs(VAR(exponent) - 2.0) < EPSILON;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double r;
    if (VAR(_regularForm)) {
      r = VVAR / (FTx * FTx + FTy * FTy + FTz * FTz + SMALL_EPSILON);
    } else {
      r = VVAR / pow(FTx * FTx + FTy * FTy + FTz * FTz + SMALL_EPSILON, VAR(exponent) / 2.0);
    }
    if (VAR(invert) == 0) {
      FPx += FTx * r;
      FPy += FTy * r;
      FPz += FTz * r;
    } else /*if (VAR(invert) == 1)*/ {
      FPx -= FTx * r;
      FPy -= FTy * r;
      FPz -= FTz * r;
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
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class Spherical3DWFFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   public static final String PARAM_INVERT = "invert";
//   private static final String PARAM_EXPONENT = "exponent";
// 
//   private static final String[] paramNames = {PARAM_INVERT, PARAM_EXPONENT};
// 
//   private int invert = 0;
//   private double exponent = 2.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double r;
//     if (_regularForm) {
//       r = pAmount / (pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y + pAffineTP.z * pAffineTP.z + SMALL_EPSILON);
//     } else {
//       r = pAmount / pow(pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y + pAffineTP.z * pAffineTP.z + SMALL_EPSILON, exponent / 2.0);
//     }
//     if (invert == 0) {
//       pVarTP.x += pAffineTP.x * r;
//       pVarTP.y += pAffineTP.y * r;
//       pVarTP.z += pAffineTP.z * r;
//     } else /*if (invert == 1)*/ {
//       pVarTP.x -= pAffineTP.x * r;
//       pVarTP.y -= pAffineTP.y * r;
//       pVarTP.z -= pAffineTP.z * r;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "spherical3D_wf";
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{invert, exponent};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_INVERT.equalsIgnoreCase(pName))
//       invert = Tools.FTOI(pValue);
//     else if (PARAM_EXPONENT.equalsIgnoreCase(pName))
//       exponent = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   private boolean _regularForm;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _regularForm = fabs(exponent - 2.0) < EPSILON;
//   }
// 
// }
// 
