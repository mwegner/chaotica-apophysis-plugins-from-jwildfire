#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: wedge

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/WedgeFunc.java

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
	double angle; // M_PI_2
	double hole;
	int count;
	double swirl;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "wedge_"
#include "plugin.h"

APO_PLUGIN("wedge");
APO_VARIABLES(
	VAR_REAL(angle, M_PI_2),
	VAR_REAL(hole, 0.0),
	VAR_INTEGER(count, 1),
	VAR_REAL(swirl, 0.0),

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Wedge from apo plugins pack */
    double r = (sqrt(FTx * FTx + FTy * FTy) + SMALL_EPSILON);
    double a = atan2(FTx, FTy) + VAR(swirl) * r;
    double c = floor((VAR(count) * a + M_PI) * M_1_PI * 0.5);

    double comp_fac = 1 - VAR(angle) * VAR(count) * M_1_PI * 0.5;

    a = a * comp_fac + c * VAR(angle);

    double sa = sin(a);
    double ca = cos(a);

    r = VVAR * (r + VAR(hole));

    FPx += r * ca;
    FPy += r * sa;

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
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class WedgeFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_ANGLE = "angle";
//   private static final String PARAM_HOLE = "hole";
//   private static final String PARAM_COUNT = "count";
//   private static final String PARAM_SWIRL = "swirl";
//   private static final String[] paramNames = {PARAM_ANGLE, PARAM_HOLE, PARAM_COUNT, PARAM_SWIRL};
// 
//   private double angle = M_PI_2;
//   private double hole = 0.0;
//   private int count = 1;
//   private double swirl = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Wedge from apo plugins pack */
//     double r = pAffineTP.getPrecalcSqrt();
//     double a = pAffineTP.getPrecalcAtanYX() + swirl * r;
//     double c = floor((count * a + M_PI) * M_1_PI * 0.5);
// 
//     double comp_fac = 1 - angle * count * M_1_PI * 0.5;
// 
//     a = a * comp_fac + c * angle;
// 
//     double sa = sin(a);
//     double ca = cos(a);
// 
//     r = pAmount * (r + hole);
// 
//     pVarTP.x += r * ca;
//     pVarTP.y += r * sa;
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
//     return new Object[]{angle, hole, count, swirl};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_ANGLE.equalsIgnoreCase(pName))
//       angle = pValue;
//     else if (PARAM_HOLE.equalsIgnoreCase(pName))
//       hole = pValue;
//     else if (PARAM_COUNT.equalsIgnoreCase(pName))
//       count = Tools.FTOI(pValue);
//     else if (PARAM_SWIRL.equalsIgnoreCase(pName))
//       swirl = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "wedge";
//   }
// 
// }
// 
