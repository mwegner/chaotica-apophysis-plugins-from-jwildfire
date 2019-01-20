#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: pre_crop

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PreCropFunc.java

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
	double left; // -1.0
	double top; // -1.0
	double right;
	double bottom;
	double scatter_area;
	int zero;
	double _xmin;
	double _xmax;
	double _ymin;
	double _ymax;
	double _w;
	double _h;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "pre_crop_"
#include "plugin.h"

APO_PLUGIN("pre_crop");
APO_VARIABLES(
	VAR_REAL(left, -1.0),
	VAR_REAL(top, -1.0),
	VAR_REAL(right, 1.0),
	VAR_REAL(bottom, 1.0),
	VAR_REAL(scatter_area, 0.0),
	VAR_INTEGER(zero, 0),

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_xmin) = MIN(VAR(left), VAR(right));
    VAR(_ymin) = MIN(VAR(top), VAR(bottom));
    VAR(_xmax) =  MAX(VAR(left), VAR(right));
    VAR(_ymax) =  MAX(VAR(top), VAR(bottom));
    VAR(_w) = (VAR(_xmax) - VAR(_xmin)) * 0.5 * VAR(scatter_area);
    VAR(_h) = (VAR(_ymax) - VAR(_ymin)) * 0.5 * VAR(scatter_area);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // pre_crop by Xyrus02, http://xyrus02.deviantart.com/art/Crop-Plugin-Updated-169958881
    double x = FTx;
    double y = FTy;
    if (((x < VAR(_xmin)) || (x > VAR(_xmax)) || (y < VAR(_ymin)) || (y > VAR(_ymax))) && (VAR(zero) != 0)) {
      FTx = FTy = 0;
      /* pAffineTP.doHide = true; */
      return TRUE;
    } else {
      /* pAffineTP.doHide = false; */
      if (x < VAR(_xmin))
        x = VAR(_xmin) + GOODRAND_01() * VAR(_w);
      else if (x > VAR(_xmax))
        x = VAR(_xmax) - GOODRAND_01() * VAR(_w);
      if (y < VAR(_ymin))
        y = VAR(_ymin) + GOODRAND_01() * VAR(_h);
      else if (y > VAR(_ymax))
        y = VAR(_ymax) - GOODRAND_01() * VAR(_h);
    }
    FTx = VVAR * x;
    FTy = VVAR * y;


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
// import static org.jwildfire.base.mathlib.MathLib.max;
// import static org.jwildfire.base.mathlib.MathLib.min;
// 
// public class PreCropFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_LEFT = "left";
//   private static final String PARAM_RIGHT = "right";
//   private static final String PARAM_TOP = "top";
//   private static final String PARAM_BOTTOM = "bottom";
//   private static final String PARAM_SCATTER_AREA = "scatter_area";
//   private static final String PARAM_ZERO = "zero";
// 
//   private static final String[] paramNames = {PARAM_LEFT, PARAM_RIGHT, PARAM_TOP, PARAM_BOTTOM, PARAM_SCATTER_AREA, PARAM_ZERO};
// 
//   private double left = -1.0;
//   private double top = -1.0;
//   private double right = 1.0;
//   private double bottom = 1.0;
//   private double scatter_area = 0.0;
//   private int zero = 0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // pre_crop by Xyrus02, http://xyrus02.deviantart.com/art/Crop-Plugin-Updated-169958881
//     double x = pAffineTP.x;
//     double y = pAffineTP.y;
//     if (((x < xmin) || (x > xmax) || (y < ymin) || (y > ymax)) && (zero != 0)) {
//       pAffineTP.x = pAffineTP.y = 0;
//       pAffineTP.doHide = true;
//       return;
//     } else {
//       pAffineTP.doHide = false;
//       if (x < xmin)
//         x = xmin + pContext.random() * w;
//       else if (x > xmax)
//         x = xmax - pContext.random() * w;
//       if (y < ymin)
//         y = ymin + pContext.random() * h;
//       else if (y > ymax)
//         y = ymax - pContext.random() * h;
//     }
//     pAffineTP.x = pAmount * x;
//     pAffineTP.y = pAmount * y;
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{left, right, top, bottom, scatter_area, zero};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_LEFT.equalsIgnoreCase(pName))
//       left = pValue;
//     else if (PARAM_RIGHT.equalsIgnoreCase(pName))
//       right = pValue;
//     else if (PARAM_TOP.equalsIgnoreCase(pName))
//       top = pValue;
//     else if (PARAM_BOTTOM.equalsIgnoreCase(pName))
//       bottom = pValue;
//     else if (PARAM_SCATTER_AREA.equalsIgnoreCase(pName))
//       scatter_area = limitVal(pValue, -1.0, 1.0);
//     else if (PARAM_ZERO.equalsIgnoreCase(pName))
//       zero = limitIntVal(Tools.FTOI(pValue), 0, 1);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "pre_crop";
//   }
// 
//   private double xmin, xmax, ymin, ymax, w, h;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     xmin = min(left, right);
//     ymin = min(top, bottom);
//     xmax = max(left, right);
//     ymax = max(top, bottom);
//     w = (xmax - xmin) * 0.5 * scatter_area;
//     h = (ymax - ymin) * 0.5 * scatter_area;
//   }
// 
//   @Override
//   public int getPriority() {
//     return -1;
//   }
// 
// }
// 
