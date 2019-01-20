#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: post_rblur

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PostRBlurFunc.java

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
	double strength;
	double offset;
	double center_x;
	double center_y;
	double _s2;

} Variables;

#define APO_VARIABLE_PREFIX "post_rblur_"
#include "plugin.h"

APO_PLUGIN("post_rblur");
APO_VARIABLES(
	VAR_REAL(strength, 1.0),
	VAR_REAL(offset, 1.0),
	VAR_REAL(center_x, 0.0),
	VAR_REAL(center_y, 1.0),

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
// import static org.jwildfire.base.mathlib.MathLib.sqr;
// import static org.jwildfire.base.mathlib.MathLib.sqrt;
// 
// public class PostRBlurFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_STRENGTH = "strength";
//   private static final String PARAM_OFFSET = "offset";
//   private static final String PARAM_CENTER_X = "center_x";
//   private static final String PARAM_CENTER_Y = "center_y";
//   private static final String[] paramNames = {PARAM_STRENGTH, PARAM_OFFSET, PARAM_CENTER_X, PARAM_CENTER_Y};
// 
//   private double strength = 1.0;
//   private double offset = 1.0;
//   private double center_x = 0.0;
//   private double center_y = 1.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // post_rblur by Xyrus02, http://xyrus-02.deviantart.com/art/post-rblur-Plugin-for-Apo-171185576
//     double r = sqrt(sqr(pVarTP.x - center_x) + sqr(pVarTP.y - center_y)) - offset;
//     r = r < 0 ? 0 : r;
//     r *= s2;
//     pVarTP.x = pAmount * (pVarTP.x + (pContext.random() - 0.5) * r);
//     pVarTP.y = pAmount * (pVarTP.y + (pContext.random() - 0.5) * r);
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{strength, offset, center_x, center_y};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_STRENGTH.equalsIgnoreCase(pName))
//       strength = pValue;
//     else if (PARAM_OFFSET.equalsIgnoreCase(pName))
//       offset = pValue;
//     else if (PARAM_CENTER_X.equalsIgnoreCase(pName))
//       center_x = pValue;
//     else if (PARAM_CENTER_Y.equalsIgnoreCase(pName))
//       center_y = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "post_rblur";
//   }
// 
//   private double s2;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     s2 = 2.0 * strength;
//   }
// 
//   @Override
//   public int getPriority() {
//     return 1;
//   }
// }
// 
