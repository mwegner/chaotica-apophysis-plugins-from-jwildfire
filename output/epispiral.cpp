#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: epispiral

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/EpispiralFunc.java

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
	double n;
	double thickness;
	double holes;

} Variables;

#define APO_VARIABLE_PREFIX "epispiral_"
#include "plugin.h"

APO_PLUGIN("epispiral");
APO_VARIABLES(
	VAR_REAL(n, 6.0),
	VAR_REAL(thickness, 0.0),
	VAR_REAL(holes, 1.0)

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // epispiral by cyberxaos, http://cyberxaos.deviantart.com/journal/Epispiral-Plugin-240086108   
    double theta = atan2(FTy, FTx);
    double t = -VAR(holes);
    if (fabs(VAR(thickness)) > EPSILON) {
      double d = cos(VAR(n) * theta);
      if (d == 0) {
        return TRUE;
      }
      t += (GOODRAND_01() * VAR(thickness)) * (1.0 / d);
    } else {
      double d = cos(VAR(n) * theta);
      if (d == 0) {
        return TRUE;
      }
      t += 1.0 / d;
    }
    FPx += VVAR * t * cos(theta);
    FPy += VVAR * t * sin(theta);
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
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class EpispiralFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_N = "n";
//   private static final String PARAM_THICKNESS = "thickness";
//   private static final String PARAM_HOLES = "holes";
//   private static final String[] paramNames = {PARAM_N, PARAM_THICKNESS, PARAM_HOLES};
// 
//   private double n = 6.0;
//   private double thickness = 0.0;
//   private double holes = 1.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // epispiral by cyberxaos, http://cyberxaos.deviantart.com/journal/Epispiral-Plugin-240086108   
//     double theta = atan2(pAffineTP.y, pAffineTP.x);
//     double t = -holes;
//     if (fabs(thickness) > EPSILON) {
//       double d = cos(n * theta);
//       if (d == 0) {
//         return;
//       }
//       t += (pContext.random() * thickness) * (1.0 / d);
//     } else {
//       double d = cos(n * theta);
//       if (d == 0) {
//         return;
//       }
//       t += 1.0 / d;
//     }
//     pVarTP.x += pAmount * t * cos(theta);
//     pVarTP.y += pAmount * t * sin(theta);
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
//     return new Object[]{n, thickness, holes};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_N.equalsIgnoreCase(pName))
//       n = pValue;
//     else if (PARAM_THICKNESS.equalsIgnoreCase(pName))
//       thickness = pValue;
//     else if (PARAM_HOLES.equalsIgnoreCase(pName))
//       holes = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "epispiral";
//   }
// 
// }
// 
