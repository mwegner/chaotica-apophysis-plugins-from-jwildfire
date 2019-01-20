#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: radial_blur

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/RadialBlurFunc.java

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
	double _gauss_rnd[4];
	int _gauss_N;
	double angle;

} Variables;

#define APO_VARIABLE_PREFIX "radial_blur_"
#include "plugin.h"

APO_PLUGIN("radial_blur");
APO_VARIABLES(
	VAR_REAL(angle, 0.5)

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_gauss_rnd)[0] = GOODRAND_01();
    VAR(_gauss_rnd)[1] = GOODRAND_01();
    VAR(_gauss_rnd)[2] = GOODRAND_01();
    VAR(_gauss_rnd)[3] = GOODRAND_01();
    VAR(_gauss_N) = 0;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double rndG = (VAR(_gauss_rnd)[0] + VAR(_gauss_rnd)[1] + VAR(_gauss_rnd)[2] + VAR(_gauss_rnd)[3] - 2);
    VAR(_gauss_rnd)[VAR(_gauss_N)] = GOODRAND_01();
    VAR(_gauss_N) = (VAR(_gauss_N) + 1) & 3;

    double spin = VVAR * sin(VAR(angle) * M_PI * 0.5);
    double zoom = VVAR * cos(VAR(angle) * M_PI * 0.5);

    double ra = sqrt(FTx * FTx + FTy * FTy);
    double alpha = atan2(FTy, FTx) + spin * rndG;
    double sina = sin(alpha);
    double cosa = cos(alpha);
    double rz = zoom * rndG - 1;
    FPx += ra * cosa + rz * FTx;
    FPy += ra * sina + rz * FTy;
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
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class RadialBlurFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private final double gauss_rnd[] = new double[4];
//   private int gauss_N;
// 
//   private static final String PARAM_ANGLE = "angle";
//   private static final String[] paramNames = {PARAM_ANGLE};
// 
//   private double angle = 0.5;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double rndG = (gauss_rnd[0] + gauss_rnd[1] + gauss_rnd[2] + gauss_rnd[3] - 2);
//     gauss_rnd[gauss_N] = pContext.random();
//     gauss_N = (gauss_N + 1) & 3;
// 
//     double spin = pAmount * sin(angle * M_PI * 0.5);
//     double zoom = pAmount * cos(angle * M_PI * 0.5);
// 
//     double ra = sqrt(pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y);
//     double alpha = atan2(pAffineTP.y, pAffineTP.x) + spin * rndG;
//     double sina = sin(alpha);
//     double cosa = cos(alpha);
//     double rz = zoom * rndG - 1;
//     pVarTP.x += ra * cosa + rz * pAffineTP.x;
//     pVarTP.y += ra * sina + rz * pAffineTP.y;
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
//     return new Object[]{angle};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_ANGLE.equalsIgnoreCase(pName))
//       angle = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "radial_blur";
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     gauss_rnd[0] = pContext.random();
//     gauss_rnd[1] = pContext.random();
//     gauss_rnd[2] = pContext.random();
//     gauss_rnd[3] = pContext.random();
//     gauss_N = 0;
//   }
// 
// }
// 
