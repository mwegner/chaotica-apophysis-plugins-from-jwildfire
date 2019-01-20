#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: ho

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/HOFunc.java

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
	double xpow;
	double ypow;
	double zpow;

} Variables;

#define APO_VARIABLE_PREFIX "ho_"
#include "plugin.h"

APO_PLUGIN("ho");
APO_VARIABLES(
	VAR_REAL(xpow, 3.0),
	VAR_REAL(ypow, 3.0),
	VAR_REAL(zpow, 3.0),

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
// public class HOFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_XPOW = "xpow";
//   private static final String PARAM_YPOW = "ypow";
//   private static final String PARAM_ZPOW = "zpow";
//   private static final String[] paramNames = {PARAM_XPOW, PARAM_YPOW, PARAM_ZPOW};
// 
//   private double xpow = 3.0;
//   private double ypow = 3.0;
//   private double zpow = 3.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // ho by Larry Berlin, http://aporev.deviantart.com/gallery/#/d2blmhg
//     //    A Hyperbolic Octahedra
//     //    As described in "CRC Concise Encyclopedia of Mathematics" by Weisstein 2nd ed.
//     //
//     //    f[u_, v_] = (Cos[u] * Cos[v])^3
//     //    g[u_, v_] = (Sin[u] * Cos[v])^3
//     //    h[u_, v_] = Sin[v]^3
//     double u = pAffineTP.x;
//     double v = pAffineTP.y;
//     double w = pAffineTP.z;
// 
//     double at_omega_x = atan2(v * v, w * w);
//     double at_omega_y = atan2(u * u, w * w);
//     double sv = sin(v);
//     double cv = cos(v);
// 
//     double su = sin(u);
//     double cu = cos(u);
// 
//     double x = pow((cu * cv), xpow) + ((cu * cv) * xpow) + (0.25 * at_omega_x);
//     double y = pow((su * cv), ypow) + ((su * cv) * ypow) + (0.25 * at_omega_y);
//     double z = pow(sv, zpow) + sv * zpow;
// 
//     double rr = pAmount;
// 
//     pVarTP.x += rr * x;
//     pVarTP.y += rr * y;
//     pVarTP.z += rr * z;
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{xpow, ypow, zpow};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_XPOW.equalsIgnoreCase(pName))
//       xpow = pValue;
//     else if (PARAM_YPOW.equalsIgnoreCase(pName))
//       ypow = pValue;
//     else if (PARAM_ZPOW.equalsIgnoreCase(pName))
//       zpow = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "ho";
//   }
// 
// }
// 
