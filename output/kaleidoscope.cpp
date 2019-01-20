#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: kaleidoscope

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/KaleidoscopeFunc.java

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
	double pull;
	double rotate;
	double line_up;
	double x;
	double y;
	double _q;
	double _w;
	double _e;
	double _r;
	double _t;
	double _i;

} Variables;

#define APO_VARIABLE_PREFIX "kaleidoscope_"
#include "plugin.h"

APO_PLUGIN("kaleidoscope");
APO_VARIABLES(
	VAR_REAL(pull, 0.0),
	VAR_REAL(rotate, 1.0),
	VAR_REAL(line_up, 1.0),
	VAR_REAL(x, 0.0),
	VAR_REAL(y, 0.0)

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_q) = VAR(pull); // pulls apart the 2 sections of the plugin
    VAR(_w) = VAR(rotate); // rotates both halves of the plugin
    VAR(_e) = VAR(line_up);
    VAR(_r) = VAR(x); // changes VAR(x) co-ordinates
    VAR(_t) = VAR(y); // changes VAR(y) co-ordinates for 1 part of the plugin

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Kaleidoscope by Will Evans, http://eevans1.deviantart.com/art/kaleidoscope-plugin-122185469  */
    FPx += ((VAR(_w) * FTx) * cos(45.0) - FTy * sin(45.0) + VAR(_e)) + VAR(_r);
    // the if function splits the plugin in two.
    if (FTy > 0) {
      FPy += ((VAR(_w) * FTy) * cos(45.0) + FTx * sin(45.0) + VAR(_q) + VAR(_e)) + VAR(_t);
    } else {
      FPy += (VAR(_w) * FTy) * cos(45.0) + FTx * sin(45.0) - VAR(_q) - VAR(_e);
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
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.cos;
// import static org.jwildfire.base.mathlib.MathLib.sin;
// 
// public class KaleidoscopeFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_PULL = "pull";
//   private static final String PARAM_ROTATE = "rotate";
//   private static final String PARAM_LINE_UP = "line_up";
//   private static final String PARAM_X = "x";
//   private static final String PARAM_Y = "y";
// 
//   private static final String[] paramNames = {PARAM_PULL, PARAM_ROTATE, PARAM_LINE_UP, PARAM_X, PARAM_Y};
// 
//   private double pull = 0.0;
//   private double rotate = 1.0;
//   private double line_up = 1.0;
//   private double x = 0.0;
//   private double y = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Kaleidoscope by Will Evans, http://eevans1.deviantart.com/art/kaleidoscope-plugin-122185469  */
//     pVarTP.x += ((_w * pAffineTP.x) * cos(45.0) - pAffineTP.y * sin(45.0) + _e) + _r;
//     // the if function splits the plugin in two.
//     if (pAffineTP.y > 0) {
//       pVarTP.y += ((_w * pAffineTP.y) * cos(45.0) + pAffineTP.x * sin(45.0) + _q + _e) + _t;
//     } else {
//       pVarTP.y += (_w * pAffineTP.y) * cos(45.0) + pAffineTP.x * sin(45.0) - _q - _e;
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
//     return new Object[]{pull, rotate, line_up, x, y};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_PULL.equalsIgnoreCase(pName))
//       pull = pValue;
//     else if (PARAM_ROTATE.equalsIgnoreCase(pName))
//       rotate = pValue;
//     else if (PARAM_LINE_UP.equalsIgnoreCase(pName))
//       line_up = pValue;
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
//     return "kaleidoscope";
//   }
// 
//   double _q, _w, _e, _r, _t, _i;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _q = pull; // pulls apart the 2 sections of the plugin
//     _w = rotate; // rotates both halves of the plugin
//     _e = line_up;
//     _r = x; // changes x co-ordinates
//     _t = y; // changes y co-ordinates for 1 part of the plugin
//   }
// 
// }
// 
