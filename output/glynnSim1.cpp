#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: glynnSim1

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/GlynnSim1Func.java

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
	double radius;
	double radius1;
	double phi1;
	double thickness;
	double pow;
	double contrast;
	double _x1;
	double _y1;
	double _absPow;
	Point _toolPoint; // POINT(0,0,0)

} Variables;

#define APO_VARIABLE_PREFIX "glynnSim1_"
#include "plugin.h"

APO_PLUGIN("glynnSim1");
APO_VARIABLES(
	VAR_REAL(radius, 1.0),
	VAR_REAL(radius1, 0.1),
	VAR_REAL(phi1, 110.0),
	VAR_REAL(thickness, 0.1),
	VAR_REAL(pow, 1.5),
	VAR_REAL(contrast, 0.5)

);


void circle (Variation* vp, Point p) {

    double r = VAR(radius1) * (VAR(thickness) + (1.0 - VAR(thickness)) * GOODRAND_01());
    double Phi = 2.0 * M_PI * GOODRAND_01();
    double sinPhi = sin(Phi);
    double cosPhi = cos(Phi);
    p.x = r * cosPhi + VAR(_x1);
    p.y = r * sinPhi + VAR(_y1);
}


int PluginVarPrepare(Variation* vp)
{
    double a = M_PI * VAR(phi1) / 180.0;
    double sinPhi1 = sin(a);
    double cosPhi1 = cos(a);
    VAR(_x1) = VAR(radius) * cosPhi1;
    VAR(_y1) = VAR(radius) * sinPhi1;
    VAR(_absPow) = fabs(VAR(pow));

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* GlynnSim1 by eralex61, http://eralex61.deviantart.com/art/GlynnSim-plugin-112621621 */
    double r = sqrt(FTx * FTx + FTy * FTy);
    double Alpha = VAR(radius) / r;
    if (r < VAR(radius)) { //object generation
      circle(vp, VAR(_toolPoint));
      FPx += VVAR * VAR(_toolPoint).x;
      FPy += VVAR * VAR(_toolPoint).y;
    } else {
      if (GOODRAND_01() > VAR(contrast) * pow(Alpha, VAR(_absPow))) {
        VAR(_toolPoint).x = FTx;
        VAR(_toolPoint).y = FTy;
      } else {
        VAR(_toolPoint).x = Alpha * Alpha * FTx;
        VAR(_toolPoint).y = Alpha * Alpha * FTy;
      }
      double Z = sqr(VAR(_toolPoint).x - VAR(_x1)) + sqr(VAR(_toolPoint).y - VAR(_y1));
      if (Z < VAR(radius1) * VAR(radius1)) { //object generation
        circle(vp, VAR(_toolPoint));
        FPx += VVAR * VAR(_toolPoint).x;
        FPy += VVAR * VAR(_toolPoint).y;
      } else {
        FPx += VVAR * VAR(_toolPoint).x;
        FPy += VVAR * VAR(_toolPoint).y;
      }
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
// import java.io.Serializable;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class GlynnSim1Func extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_RADIUS = "radius";
//   private static final String PARAM_RADIUS1 = "radius1";
//   private static final String PARAM_PHI1 = "phi1";
//   private static final String PARAM_THICKNESS = "thickness";
//   private static final String PARAM_POW = "pow";
//   private static final String PARAM_CONTRAST = "contrast";
// 
//   private static final String[] paramNames = {PARAM_RADIUS, PARAM_RADIUS1, PARAM_PHI1, PARAM_THICKNESS, PARAM_POW, PARAM_CONTRAST};
// 
//   private double radius = 1.0;
//   private double radius1 = 0.1;
//   private double phi1 = 110.0;
//   private double thickness = 0.1;
//   private double pow = 1.5;
//   private double contrast = 0.5;
// 
//   private static class Point implements Serializable {
//     private static final long serialVersionUID = 1L;
//     private double x, y;
//   }
// 
//   private void circle(FlameTransformationContext pContext, Point p) {
//     double r = this.radius1 * (this.thickness + (1.0 - this.thickness) * pContext.random());
//     double Phi = 2.0 * M_PI * pContext.random();
//     double sinPhi = sin(Phi);
//     double cosPhi = cos(Phi);
//     p.x = r * cosPhi + this._x1;
//     p.y = r * sinPhi + this._y1;
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* GlynnSim1 by eralex61, http://eralex61.deviantart.com/art/GlynnSim-plugin-112621621 */
//     double r = sqrt(pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y);
//     double Alpha = this.radius / r;
//     if (r < this.radius) { //object generation
//       circle(pContext, toolPoint);
//       pVarTP.x += pAmount * toolPoint.x;
//       pVarTP.y += pAmount * toolPoint.y;
//     } else {
//       if (pContext.random() > this.contrast * pow(Alpha, this._absPow)) {
//         toolPoint.x = pAffineTP.x;
//         toolPoint.y = pAffineTP.y;
//       } else {
//         toolPoint.x = Alpha * Alpha * pAffineTP.x;
//         toolPoint.y = Alpha * Alpha * pAffineTP.y;
//       }
//       double Z = sqr(toolPoint.x - this._x1) + sqr(toolPoint.y - this._y1);
//       if (Z < this.radius1 * this.radius1) { //object generation
//         circle(pContext, toolPoint);
//         pVarTP.x += pAmount * toolPoint.x;
//         pVarTP.y += pAmount * toolPoint.y;
//       } else {
//         pVarTP.x += pAmount * toolPoint.x;
//         pVarTP.y += pAmount * toolPoint.y;
//       }
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
//     return new Object[]{radius, radius1, phi1, thickness, pow, contrast};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_RADIUS.equalsIgnoreCase(pName))
//       radius = pValue;
//     else if (PARAM_RADIUS1.equalsIgnoreCase(pName))
//       radius1 = pValue;
//     else if (PARAM_PHI1.equalsIgnoreCase(pName))
//       phi1 = pValue;
//     else if (PARAM_THICKNESS.equalsIgnoreCase(pName))
//       thickness = limitVal(pValue, 0.0, 1.0);
//     else if (PARAM_POW.equalsIgnoreCase(pName))
//       pow = pValue;
//     else if (PARAM_CONTRAST.equalsIgnoreCase(pName))
//       contrast = limitVal(pValue, 0.0, 1.0);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "glynnSim1";
//   }
// 
//   private double _x1, _y1, _absPow;
//   private Point toolPoint = new Point();
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     double a = M_PI * phi1 / 180.0;
//     double sinPhi1 = sin(a);
//     double cosPhi1 = cos(a);
//     this._x1 = this.radius * cosPhi1;
//     this._y1 = this.radius * sinPhi1;
//     this._absPow = fabs(this.pow);
//   }
// 
//   @Override
//   public String[] getParameterAlternativeNames() {
//     return new String[]{"GlynnSim1_radius", "GlynnSim1_radius1", "GlynnSim1_Phi1", "GlynnSim1_thickness", "GlynnSim1_pow", "GlynnSim1_contrast"};
//   }
// 
// }
// 
