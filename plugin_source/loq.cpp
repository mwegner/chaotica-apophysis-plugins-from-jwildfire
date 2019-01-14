/*
    Apophysis Plugin: loq

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/LoqFunc.java

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
	double base;
	double _denom;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "loq_"
#include "plugin.h"

APO_PLUGIN("loq");
APO_VARIABLES(
	VAR_REAL(base, M_E),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
    VAR(_denom) = 0.5 * VVAR / log(VAR(base));

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Loq by zephyrtronium http://zephyrtronium.deviantart.com/art/Quaternion-Apo-Plugin-Pack-165451482 */

    double abs_v = hypot(FTy, FTz);
    double C = VVAR * atan2(abs_v, FTx) / abs_v;
    FPx += log(sqr(FTx) + sqr(abs_v)) * VAR(_denom);
    FPy += C * FTy;
    FPz += C * FTz;


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
// import odk.lang.FastMath;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class LoqFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_BASE = "base";
// 
//   private static final String[] paramNames = {PARAM_BASE};
// 
//   private double base = M_E;
//   private double denom;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     denom = 0.5 * pAmount / log(base);
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Loq by zephyrtronium http://zephyrtronium.deviantart.com/art/Quaternion-Apo-Plugin-Pack-165451482 */
// 
//     double abs_v = FastMath.hypot(pAffineTP.y, pAffineTP.z);
//     double C = pAmount * atan2(abs_v, pAffineTP.x) / abs_v;
//     pVarTP.x += log(sqr(pAffineTP.x) + sqr(abs_v)) * denom;
//     pVarTP.y += C * pAffineTP.y;
//     pVarTP.z += C * pAffineTP.z;
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{base};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_BASE.equalsIgnoreCase(pName))
//       base = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "loq";
//   }
// 
// }
// 
