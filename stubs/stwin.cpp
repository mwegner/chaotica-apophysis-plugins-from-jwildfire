#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: stwin

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/STwinFunc.java

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
	double distort;
	double offset_xy;
	double offset_x2;
	double offset_y2;
	double _multiplier = 0.05;
	double _multiplier2 = 0.0001;
	double _multiplier3 = 0.1;

} Variables;

#define APO_VARIABLE_PREFIX "stwin_"
#include "plugin.h"

APO_PLUGIN("stwin");
APO_VARIABLES(
	VAR_REAL(distort, 1.0),
	VAR_REAL(offset_xy, 0.0),
	VAR_REAL(offset_x2, 0.0),
	VAR_REAL(offset_y2, 0.0),

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
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.M_2PI;
// import static org.jwildfire.base.mathlib.MathLib.sin;
// 
// /*
//  *  STwinFunc: JWildfire variation,
//  *  JWildfire variation, ported from "stwin" Apophysis7X plugin, plus added extra user-configurable parameters
//  *  original Apophysis7X plugin author xyrus02 ?
//  *  ported to JWildfire varation by CozyG
//  */
// public class STwinFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_DISTORT = "distort";
//   private static final String PARAM_OFFSET_XY = "offset_xy";
//   private static final String PARAM_OFFSET_X2 = "offset_x2";
//   private static final String PARAM_OFFSET_Y2 = "offset_y2";
//   private static final String[] paramNames = {PARAM_DISTORT, PARAM_OFFSET_XY, PARAM_OFFSET_X2, PARAM_OFFSET_Y2};
// 
//   private double distort = 1.0;
//   private double offset_xy = 0.0;
//   private double offset_x2 = 0.0;
//   private double offset_y2 = 0.0;
//   private double multiplier = 0.05;
//   private double multiplier2 = 0.0001;
//   private double multiplier3 = 0.1;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// 
//     double x = pAffineTP.x * pAmount * multiplier;
//     double y = pAffineTP.y * pAmount * multiplier;
//     double x2 = x * x + (offset_x2 * multiplier2);
//     double y2 = y * y + (offset_y2 * multiplier2);
// 
//     double result = (x2 - y2) * sin(M_2PI * distort * (x + y + (offset_xy * multiplier3)));
//     double divident = x2 + y2;
//     if (divident == 0) {
//       divident = 1.0;
//     }
// 
//     result = result / divident;
// 
//     pVarTP.x += (pAmount * pAffineTP.x) + result;
//     pVarTP.y += (pAmount * pAffineTP.y) + result;
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
//     return new Object[]{distort, offset_xy, offset_x2, offset_y2};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_DISTORT.equalsIgnoreCase(pName))
//       distort = pValue;
//     else if (PARAM_OFFSET_XY.equalsIgnoreCase(pName))
//       offset_xy = pValue;
//     else if (PARAM_OFFSET_X2.equalsIgnoreCase(pName))
//       offset_x2 = pValue;
//     else if (PARAM_OFFSET_Y2.equalsIgnoreCase(pName))
//       offset_y2 = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "stwin";
//   }
// 
// }
// 
