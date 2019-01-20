#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: d_spherical

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/DSphericalFunc.java

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
	double d_spher_weight;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "d_spherical_"
#include "plugin.h"

APO_PLUGIN("d_spherical");
APO_VARIABLES(
	VAR_REAL(d_spher_weight, 0.5),

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // d_spherical by Tatyana Zabanova, https://tatasz.deviantart.com/art/Utilities-Plugin-Pack-684337906
    {
      if (GOODRAND_01() < (VAR(d_spher_weight))) {
        double r = VVAR / (sqr(FTx) + sqr(FTy));
        FPx += FTx * r;
        FPy += FTy * r;
        if (true /* pContext\.isPreserveZCoordinate() */) {
          FPz += VVAR * FTz;
        }
      } else {
        FPx += FTx * VVAR;
        FPy += FTy * VVAR;
        if (true /* pContext\.isPreserveZCoordinate() */) {
          FPz += VVAR * FTz;
        }
      }
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
// import static org.jwildfire.base.mathlib.MathLib.sqr;
// 
// //import org.jwildfire.create.tina.base.Layer;
// 
// public class DSphericalFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_D_SPHER_WEIGHT = "d_spher_weight";
//   private static final String[] paramNames = {PARAM_D_SPHER_WEIGHT};
// 
//   private double d_spher_weight = 0.5;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // d_spherical by Tatyana Zabanova, https://tatasz.deviantart.com/art/Utilities-Plugin-Pack-684337906
//     {
//       if (Math.random() < (d_spher_weight)) {
//         double r = pAmount / (sqr(pAffineTP.x) + sqr(pAffineTP.y));
//         pVarTP.x += pAffineTP.x * r;
//         pVarTP.y += pAffineTP.y * r;
//         if (pContext.isPreserveZCoordinate()) {
//           pVarTP.z += pAmount * pAffineTP.z;
//         }
//       } else {
//         pVarTP.x += pAffineTP.x * pAmount;
//         pVarTP.y += pAffineTP.y * pAmount;
//         if (pContext.isPreserveZCoordinate()) {
//           pVarTP.z += pAmount * pAffineTP.z;
//         }
//       }
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
//     return new Object[]{d_spher_weight};
//   }
// 
//   @Override
//   public String[] getParameterAlternativeNames() {
//     return new String[]{"d_spher_weight"};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_D_SPHER_WEIGHT.equalsIgnoreCase(pName))
//       d_spher_weight = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "d_spherical";
//   }
// 
// 
// }
// 
