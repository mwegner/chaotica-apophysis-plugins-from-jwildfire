#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: cannabiscurve_wf

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/CannabisCurveWFFunc.java

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
	int filled;

} Variables;

#define APO_VARIABLE_PREFIX "cannabiscurve_wf_"
#include "plugin.h"

APO_PLUGIN("cannabiscurve_wf");
APO_VARIABLES(
	VAR_INTEGER(filled, 1),

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
//   Copyright (C) 1995-2015 Andreas Maschke
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
// public class CannabisCurveWFFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   public static final String PARAM_FILLED = "filled";
//   private static final String[] paramNames = {PARAM_FILLED};
// 
//   private int filled = 1;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double a = pAffineTP.getPrecalcAtan();
// 
//     // cannabis curve (http://mathworld.wolfram.com/CannabisCurve.html)
//     double r = (1 + 9.0 / 10.0 * cos(8.0 * a)) * (1 + 1.0 / 10.0 * cos(24.0 * a)) * (9.0 / 10.0 + 1.0 / 10.0 * cos(200.0 * a)) * (1.0 + sin(a));
//     a += M_PI / 2.0;
// 
//     if (filled == 1) {
//       r *= pContext.random();
//     }
// 
//     double nx = sin(a) * r;
//     double ny = cos(a) * r;
// 
//     pVarTP.x += pAmount * nx;
//     pVarTP.y += pAmount * ny;
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
//     return new Object[]{filled};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_FILLED.equalsIgnoreCase(pName))
//       filled = Tools.FTOI(pValue);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "cannabiscurve_wf";
//   }
// 
// }
// 
