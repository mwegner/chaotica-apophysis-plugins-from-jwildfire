#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: pre_rect_wf

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PreRectWFFunc.java

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
	double x0; // -0.5
	double x1;
	double y0; // -0.5
	double y1;
	double _dx;
	double _dy;

} Variables;

#define APO_VARIABLE_PREFIX "pre_rect_wf_"
#include "plugin.h"

APO_PLUGIN("pre_rect_wf");
APO_VARIABLES(
	VAR_REAL(x0, -0.5),
	VAR_REAL(x1, 0.5),
	VAR_REAL(y0, -0.5),
	VAR_REAL(y1, 0.5)

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_dx) = VAR(x1) - VAR(x0);
    VAR(_dy) = VAR(y1) - VAR(y0);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    FTx = VVAR * (VAR(x0) + VAR(_dx) * GOODRAND_01());
    FTy = VVAR * (VAR(y0) + VAR(_dy) * GOODRAND_01());


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
// public class PreRectWFFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_X0 = "x0";
//   private static final String PARAM_X1 = "x1";
//   private static final String PARAM_Y0 = "y0";
//   private static final String PARAM_Y1 = "y1";
// 
//   private static final String[] paramNames = {PARAM_X0, PARAM_X1, PARAM_Y0, PARAM_Y1};
// 
//   private double x0 = -0.5;
//   private double x1 = 0.5;
//   private double y0 = -0.5;
//   private double y1 = 0.5;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     pAffineTP.x = pAmount * (x0 + dx * pContext.random());
//     pAffineTP.y = pAmount * (y0 + dy * pContext.random());
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{x0, x1, y0, y1};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_X0.equalsIgnoreCase(pName))
//       x0 = pValue;
//     else if (PARAM_X1.equalsIgnoreCase(pName))
//       x1 = pValue;
//     else if (PARAM_Y0.equalsIgnoreCase(pName))
//       y0 = pValue;
//     else if (PARAM_Y1.equalsIgnoreCase(pName))
//       y1 = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "pre_rect_wf";
//   }
// 
//   @Override
//   public int getPriority() {
//     return -1;
//   }
// 
//   double dx, dy;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     dx = x1 - x0;
//     dy = y1 - y0;
//   }
// 
// }
// 
