#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: blur_zoom

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/BlurZoomFunc.java

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
	double length;
	double x;
	double y;

} Variables;

#define APO_VARIABLE_PREFIX "blur_zoom_"
#include "plugin.h"

APO_PLUGIN("blur_zoom");
APO_VARIABLES(
	VAR_REAL(length, 0.0),
	VAR_REAL(x, 0.0),
	VAR_REAL(y, 0.0)

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* blur_zoom from Apo7X15C */
    double z = 1.0 + VAR(length) * GOODRAND_01();

    FPx += VVAR * ((FTx - VAR(x)) * z + VAR(x));
    FPy += VVAR * ((FTy - VAR(y)) * z - VAR(y));
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
// public class BlurZoomFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_LENGTH = "length";
//   private static final String PARAM_X = "x";
//   private static final String PARAM_Y = "y";
//   private static final String[] paramNames = {PARAM_LENGTH, PARAM_X, PARAM_Y};
// 
//   private double length = 0.0;
//   private double x = 0.0;
//   private double y = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* blur_zoom from Apo7X15C */
//     double z = 1.0 + this.length * pContext.random();
// 
//     pVarTP.x += pAmount * ((pAffineTP.x - this.x) * z + this.x);
//     pVarTP.y += pAmount * ((pAffineTP.y - this.y) * z - this.y);
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
//     return new Object[]{length, x, y};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_LENGTH.equalsIgnoreCase(pName))
//       length = pValue;
//     else if (PARAM_X.equalsIgnoreCase(pName))
//       x = pValue;
//     else if (PARAM_Y.equalsIgnoreCase(pName))
//       y = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "blur_zoom";
//   }
// 
// }
// 
