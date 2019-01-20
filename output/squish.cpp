#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: squish

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/SquishFunc.java

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
	int power;
	double _inv_power;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "squish_"
#include "plugin.h"

APO_PLUGIN("squish");
APO_VARIABLES(
	VAR_INTEGER(power, 2),

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_inv_power) = 1.0 / (double) VAR(power);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // squish by MichaelFaber - The angle pack: http://michaelfaber.deviantart.com/art/The-Angle-Pack-277718538
    double x = fabs(FTx);
    double y = fabs(FTy);
    double s;
    double p;

    if (x > y) {
      s = x;

      if (FTx > 0.0) {
        p = FTy;
      } else {
        p = 4.0 * s - FTy;
      }
    } else {
      s = y;
      if (FTy > 0.0) {
        p = 2.0 * s - FTx;
      } else {
        p = 6.0 * s + FTx;
      }
    }

    p = VAR(_inv_power) * (p + 8.0 * s * floor(VAR(power) * GOODRAND_01()));

    if (p <= 1.0 * s) {
      FPx += VVAR * s;
      FPy += VVAR * p;
    } else if (p <= 3.0 * s) {
      FPx += VVAR * (2.0 * s - p);
      FPy += VVAR * (s);
    } else if (p <= 5.0 * s) {
      FPx -= VVAR * (s);
      FPy += VVAR * (4.0 * s - p);
    } else if (p <= 7.0 * s) {
      FPx -= VVAR * (6.0 * s - p);
      FPy -= VVAR * (s);
    } else {
      FPx += VVAR * (s);
      FPy -= VVAR * (8.0 * s - p);
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
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.fabs;
// import static org.jwildfire.base.mathlib.MathLib.floor;
// 
// public class SquishFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_POWER = "power";
// 
//   private static final String[] paramNames = {PARAM_POWER};
// 
//   private int power = 2;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // squish by MichaelFaber - The angle pack: http://michaelfaber.deviantart.com/art/The-Angle-Pack-277718538
//     double x = fabs(pAffineTP.x);
//     double y = fabs(pAffineTP.y);
//     double s;
//     double p;
// 
//     if (x > y) {
//       s = x;
// 
//       if (pAffineTP.x > 0.0) {
//         p = pAffineTP.y;
//       } else {
//         p = 4.0 * s - pAffineTP.y;
//       }
//     } else {
//       s = y;
//       if (pAffineTP.y > 0.0) {
//         p = 2.0 * s - pAffineTP.x;
//       } else {
//         p = 6.0 * s + pAffineTP.x;
//       }
//     }
// 
//     p = _inv_power * (p + 8.0 * s * floor(power * pContext.random()));
// 
//     if (p <= 1.0 * s) {
//       pVarTP.x += pAmount * s;
//       pVarTP.y += pAmount * p;
//     } else if (p <= 3.0 * s) {
//       pVarTP.x += pAmount * (2.0 * s - p);
//       pVarTP.y += pAmount * (s);
//     } else if (p <= 5.0 * s) {
//       pVarTP.x -= pAmount * (s);
//       pVarTP.y += pAmount * (4.0 * s - p);
//     } else if (p <= 7.0 * s) {
//       pVarTP.x -= pAmount * (6.0 * s - p);
//       pVarTP.y -= pAmount * (s);
//     } else {
//       pVarTP.x += pAmount * (s);
//       pVarTP.y -= pAmount * (8.0 * s - p);
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
//     return new Object[]{power};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_POWER.equalsIgnoreCase(pName))
//       power = limitIntVal(Tools.FTOI(pValue), 2, Integer.MAX_VALUE);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "squish";
//   }
// 
//   private double _inv_power;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _inv_power = 1.0 / (double) power;
//   }
// 
// }
// 
