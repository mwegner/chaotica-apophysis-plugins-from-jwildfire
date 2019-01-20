#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: post_bwraps2

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PostBWraps2Func.java

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
	double cellsize;
	double space;
	double gain;
	double inner_twist;
	double outer_twist;
	double _g2;
	double _r2;
	double _rfactor;

} Variables;

#define APO_VARIABLE_PREFIX "post_bwraps2_"
#include "plugin.h"

APO_PLUGIN("post_bwraps2");
APO_VARIABLES(
	VAR_REAL(cellsize, 1.0),
	VAR_REAL(space, 0.0),
	VAR_REAL(gain, 2.0),
	VAR_REAL(inner_twist, 0.0),
	VAR_REAL(outer_twist, 0.0)

);



int PluginVarPrepare(Variation* vp)
{
    double radius = 0.5 * (VAR(cellsize) / (1.0 + VAR(space) * VAR(space)));

    // g2 is multiplier for radius
    VAR(_g2) = VAR(gain) * VAR(gain) / VAR(cellsize) + 1.0e-6;

    // Start max_bubble as maximum x or y value before applying bubble
    double max_bubble = VAR(_g2) * radius;

    if (max_bubble > 2.0) {
      // Values greater than 2.0 "recurve" round the back of the bubble
      max_bubble = 1.0;
    } else {
      // Expand smaller bubble to fill the VAR(space)
      max_bubble *= 1.0 / ((max_bubble * max_bubble) / 4.0 + 1.0);
    }

    VAR(_r2) = radius * radius;
    VAR(_rfactor) = radius / max_bubble;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // pre_bwrap2s by Xyrus02, http://xyrus02.deviantart.com/art/Bwraps2-Plugin-for-Apophysis-207955904    
    // Bubble Wrap - WIP Plugin by slobo777
    // http://slobo777.deviantart.com/art/Bubble-Wrap-WIP-Plugin-112370125 
    double Vx, Vy; // V is "global" vector,
    double Cx, Cy; // C is "cell centre" vector
    double Lx, Ly; // L is "local" bubble vector
    double r, theta, s, c;

    Vx = FPx;
    Vy = FPy;

    if (fabs(VAR(cellsize)) < SMALL_EPSILON) {
      // Linear if cells are too small
      FPx = VVAR * Vx;
      FPy = VVAR * Vy;
      return TRUE;
    }

    Cx = (floor(Vx / VAR(cellsize)) + 0.5) * VAR(cellsize);
    Cy = (floor(Vy / VAR(cellsize)) + 0.5) * VAR(cellsize);

    Lx = Vx - Cx;
    Ly = Vy - Cy;

    if ((Lx * Lx + Ly * Ly) > VAR(_r2)) {
      // Linear if outside the bubble
      FPx = VVAR * Vx;
      FPy = VVAR * Vy;
      return TRUE;
    }

    // We're in the bubble!

    // Bubble distortion on local co-ordinates:
    Lx *= VAR(_g2);
    Ly *= VAR(_g2);
    r = VAR(_rfactor) / ((Lx * Lx + Ly * Ly) / 4.0 + 1.0);
    Lx *= r;
    Ly *= r;

    // Spin around the centre:
    r = (Lx * Lx + Ly * Ly) / VAR(_r2); // r should be 0.0 - 1.0
    theta = VAR(inner_twist) * (1.0 - r) + VAR(outer_twist) * r;
    s = sin(theta);
    c = cos(theta);

    // Add rotated local vectors direct to centre (avoids use of temp storage)
    Vx = Cx + c * Lx + s * Ly;
    Vy = Cy - s * Lx + c * Ly;

    // Finally add values in
    FPx = VVAR * Vx;
    FPy = VVAR * Vy;


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
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class PostBWraps2Func extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_CELLSIZE = "cellsize";
//   private static final String PARAM_SPACE = "space";
//   private static final String PARAM_GAIN = "gain";
//   private static final String PARAM_INNER_TWIST = "inner_twist";
//   private static final String PARAM_OUTER_TWIST = "outer_twist";
// 
//   private static final String[] paramNames = {PARAM_CELLSIZE, PARAM_SPACE, PARAM_GAIN, PARAM_INNER_TWIST, PARAM_OUTER_TWIST};
// 
//   private double cellsize = 1.0;
//   private double space = 0.0;
//   private double gain = 2.0;
//   private double inner_twist = 0.0;
//   private double outer_twist = 0.0;
// 
//   // precalculated
//   private double _g2;
//   private double _r2;
//   private double _rfactor;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // pre_bwrap2s by Xyrus02, http://xyrus02.deviantart.com/art/Bwraps2-Plugin-for-Apophysis-207955904    
//     // Bubble Wrap - WIP Plugin by slobo777
//     // http://slobo777.deviantart.com/art/Bubble-Wrap-WIP-Plugin-112370125 
//     double Vx, Vy; // V is "global" vector,
//     double Cx, Cy; // C is "cell centre" vector
//     double Lx, Ly; // L is "local" bubble vector
//     double r, theta, s, c;
// 
//     Vx = pVarTP.x;
//     Vy = pVarTP.y;
// 
//     if (fabs(cellsize) < SMALL_EPSILON) {
//       // Linear if cells are too small
//       pVarTP.x = pAmount * Vx;
//       pVarTP.y = pAmount * Vy;
//       return;
//     }
// 
//     Cx = (floor(Vx / cellsize) + 0.5) * cellsize;
//     Cy = (floor(Vy / cellsize) + 0.5) * cellsize;
// 
//     Lx = Vx - Cx;
//     Ly = Vy - Cy;
// 
//     if ((Lx * Lx + Ly * Ly) > _r2) {
//       // Linear if outside the bubble
//       pVarTP.x = pAmount * Vx;
//       pVarTP.y = pAmount * Vy;
//       return;
//     }
// 
//     // We're in the bubble!
// 
//     // Bubble distortion on local co-ordinates:
//     Lx *= _g2;
//     Ly *= _g2;
//     r = _rfactor / ((Lx * Lx + Ly * Ly) / 4.0 + 1.0);
//     Lx *= r;
//     Ly *= r;
// 
//     // Spin around the centre:
//     r = (Lx * Lx + Ly * Ly) / _r2; // r should be 0.0 - 1.0
//     theta = inner_twist * (1.0 - r) + outer_twist * r;
//     s = sin(theta);
//     c = cos(theta);
// 
//     // Add rotated local vectors direct to centre (avoids use of temp storage)
//     Vx = Cx + c * Lx + s * Ly;
//     Vy = Cy - s * Lx + c * Ly;
// 
//     // Finally add values in
//     pVarTP.x = pAmount * Vx;
//     pVarTP.y = pAmount * Vy;
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{cellsize, space, gain, inner_twist, outer_twist};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_CELLSIZE.equalsIgnoreCase(pName))
//       cellsize = pValue;
//     else if (PARAM_SPACE.equalsIgnoreCase(pName))
//       space = pValue;
//     else if (PARAM_GAIN.equalsIgnoreCase(pName))
//       gain = pValue;
//     else if (PARAM_INNER_TWIST.equalsIgnoreCase(pName))
//       inner_twist = pValue;
//     else if (PARAM_OUTER_TWIST.equalsIgnoreCase(pName))
//       outer_twist = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "post_bwraps2";
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     double radius = 0.5 * (cellsize / (1.0 + space * space));
// 
//     // g2 is multiplier for radius
//     _g2 = gain * gain / cellsize + 1.0e-6;
// 
//     // Start max_bubble as maximum x or y value before applying bubble
//     double max_bubble = _g2 * radius;
// 
//     if (max_bubble > 2.0) {
//       // Values greater than 2.0 "recurve" round the back of the bubble
//       max_bubble = 1.0;
//     } else {
//       // Expand smaller bubble to fill the space
//       max_bubble *= 1.0 / ((max_bubble * max_bubble) / 4.0 + 1.0);
//     }
// 
//     _r2 = radius * radius;
//     _rfactor = radius / max_bubble;
//   }
// 
//   @Override
//   public int getPriority() {
//     return 1;
//   }
// 
// }
// 
