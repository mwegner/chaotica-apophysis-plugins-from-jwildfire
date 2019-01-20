#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: parabola

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ParabolaFunc.java

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
	double width;
	double height;

} Variables;

#define APO_VARIABLE_PREFIX "parabola_"
#include "plugin.h"

APO_PLUGIN("parabola");
APO_VARIABLES(
	VAR_REAL(width, 1.0),
	VAR_REAL(height, 0.5)

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* cyberxaos, 4/2007 */
    double r = (sqrt(FTx * FTx + FTy * FTy) + SMALL_EPSILON);
    double sr = sin(r);
    double cr = cos(r);
    FPx += VAR(height) * VVAR * sr * sr * GOODRAND_01();
    FPy += VAR(width) * VVAR * cr * GOODRAND_01();
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
// import static org.jwildfire.base.mathlib.MathLib.cos;
// import static org.jwildfire.base.mathlib.MathLib.sin;
// 
// public class ParabolaFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_WIDTH = "width";
//   private static final String PARAM_HEIGHT = "height";
// 
//   private static final String[] paramNames = {PARAM_WIDTH, PARAM_HEIGHT};
// 
//   private double width = 1.0;
//   private double height = 0.5;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* cyberxaos, 4/2007 */
//     double r = pAffineTP.getPrecalcSqrt();
//     double sr = sin(r);
//     double cr = cos(r);
//     pVarTP.x += height * pAmount * sr * sr * pContext.random();
//     pVarTP.y += width * pAmount * cr * pContext.random();
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
//     return new Object[]{width, height};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_WIDTH.equalsIgnoreCase(pName))
//       width = pValue;
//     else if (PARAM_HEIGHT.equalsIgnoreCase(pName))
//       height = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "parabola";
//   }
// 
// }
// 
