#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: split

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/SplitFunc.java

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
	double xsize;
	double ysize;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "split_"
#include "plugin.h"

APO_PLUGIN("split");
APO_VARIABLES(
	VAR_REAL(xsize, 0.40),
	VAR_REAL(ysize, 0.60),

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Split from apo plugins pack */
    if (cos(FTx * VAR(xsize) * M_PI) >= 0) {
      FPy += VVAR * FTy;
    } else {
      FPy -= VVAR * FTy;
    }

    if (cos(FTy * VAR(ysize) * M_PI) >= 0) {
      FPx += VVAR * FTx;
    } else {
      FPx -= VVAR * FTx;
    }
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
// import static org.jwildfire.base.mathlib.MathLib.M_PI;
// import static org.jwildfire.base.mathlib.MathLib.cos;
// 
// public class SplitFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_XSIZE = "xsize";
//   private static final String PARAM_YSIZE = "ysize";
// 
//   private static final String[] paramNames = {PARAM_XSIZE, PARAM_YSIZE};
// 
//   private double xSize = 0.40;
//   private double ySize = 0.60;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Split from apo plugins pack */
//     if (cos(pAffineTP.x * xSize * M_PI) >= 0) {
//       pVarTP.y += pAmount * pAffineTP.y;
//     } else {
//       pVarTP.y -= pAmount * pAffineTP.y;
//     }
// 
//     if (cos(pAffineTP.y * ySize * M_PI) >= 0) {
//       pVarTP.x += pAmount * pAffineTP.x;
//     } else {
//       pVarTP.x -= pAmount * pAffineTP.x;
//     }
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
//     return new Object[]{xSize, ySize};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_XSIZE.equalsIgnoreCase(pName))
//       xSize = pValue;
//     else if (PARAM_YSIZE.equalsIgnoreCase(pName))
//       ySize = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "split";
//   }
// 
// }
// 
