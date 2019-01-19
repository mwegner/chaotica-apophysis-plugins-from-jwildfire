/*
    Apophysis Plugin: jac_dn

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/JacDnFunc.java

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
	double k;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "jac_dn_"
#include "plugin.h"

APO_PLUGIN("jac_dn");
APO_VARIABLES(
	VAR_REAL(k, 0.5),

    { "WARNING_this_plugin_does_nothing", INTEGER, OFFSET(___warning), 0, 1, 0 },
);


int PluginVarPrepare(Variation* vp)
{
    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    return TRUE;
}





// original java file embedded here:
//
// /*
//   JWildfire - an image and animation processor written in Java 
//   Copyright (C) 1995-2014 Andreas Maschke
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
// import org.jwildfire.create.tina.variation.JacCnFunc.Jacobi_elliptic_result;
// 
// import static org.jwildfire.base.mathlib.MathLib.SMALL_EPSILON;
// import static org.jwildfire.base.mathlib.MathLib.sqr;
// import static org.jwildfire.create.tina.variation.JacCnFunc.Jacobi_elliptic;
// 
// public class JacDnFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_K = "k";
// 
//   private static final String[] paramNames = {PARAM_K};
// 
//   private double k = 0.5;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // Jacobi-elliptic-DN by dark-beam, http://dark-beam.deviantart.com/art/Jacobi-elliptic-sn-cn-and-dn-Apoplugins-460783612
//     double NumX, NumY, Denom;
//     Jacobi_elliptic_result jac_x = new Jacobi_elliptic_result();
//     Jacobi_elliptic(pAffineTP.x, k, jac_x);
//     Jacobi_elliptic_result jac_y = new Jacobi_elliptic_result();
//     Jacobi_elliptic(pAffineTP.y, 1.0 - k, jac_y);
// 
//     NumX = jac_x.dn * jac_y.cn * jac_y.dn;
//     NumY = -jac_x.cn * jac_x.sn * jac_y.sn * k;
//     Denom = sqr(jac_x.sn) * sqr(jac_y.sn) * k + sqr(jac_y.cn);
//     Denom = pAmount / (SMALL_EPSILON + Denom);
//     pVarTP.x += Denom * NumX;
//     pVarTP.y += Denom * NumY;
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
//     return new Object[]{k};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_K.equalsIgnoreCase(pName))
//       k = limitVal(pValue, -1.0, 1.0);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "jac_dn";
//   }
// 
// }
// 
