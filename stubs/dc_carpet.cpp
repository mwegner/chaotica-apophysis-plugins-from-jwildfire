#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: dc_carpet

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/DCCarpetFunc.java

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
	double origin;
	double _H;

} Variables;

#define APO_VARIABLE_PREFIX "dc_carpet_"
#include "plugin.h"

APO_PLUGIN("dc_carpet");
APO_VARIABLES(
	VAR_REAL(origin, 1.0),

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
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.fabs;
// import static org.jwildfire.base.mathlib.MathLib.fmod;
// 
// public class DCCarpetFunc extends VariationFunc {
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_ORIGIN = "origin";
// 
//   private static final String[] paramNames = {PARAM_ORIGIN};
// 
//   private double origin = 1.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* dc_carpet by Xyrus02, http://apophysis-7x.org/extensions */
//     int x0 = (pContext.random() < 0.5) ? -1 : 1;
//     int y0 = (pContext.random() > 0.5) ? -1 : 1;
// 
//     double x = pAffineTP.x + x0, y = pAffineTP.y + y0;
//     double x0_xor_y0 = (double) (x0 ^ y0);
//     double h = -H + (1 - x0_xor_y0) * H;
// 
//     pVarTP.x += pAmount * (pXForm.getXYCoeff00() * x + pXForm.getXYCoeff10() * y + pXForm.getXYCoeff20());
//     pVarTP.y += pAmount * (pXForm.getXYCoeff01() * x + pXForm.getXYCoeff11() * y + pXForm.getXYCoeff21());
//     pVarTP.color = fmod(fabs(pVarTP.color * 0.5 * (1 + h) + x0_xor_y0 * (1 - h) * 0.5), 1.0);
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{origin};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_ORIGIN.equalsIgnoreCase(pName))
//       origin = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "dc_carpet";
//   }
// 
//   private double H;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     H = 0.1 * origin;
//   }
// 
// }
// 
