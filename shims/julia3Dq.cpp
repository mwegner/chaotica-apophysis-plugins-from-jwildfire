/*
    Apophysis Plugin: julia3Dq

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Julia3DQFunc.java

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
	int power; // genRandomPower()
	int divisor;
	double _inv_power;
	double _abs_inv_power;
	double _half_inv_power;
	double _inv_power_2pi;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "julia3Dq_"
#include "plugin.h"

APO_PLUGIN("julia3Dq");
APO_VARIABLES(
	VAR_INTEGER(power, 0),
	VAR_INTEGER(divisor, 2),

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
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class Julia3DQFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_POWER = "power";
//   private static final String PARAM_DIVISOR = "divisor";
//   private static final String[] paramNames = {PARAM_POWER, PARAM_DIVISOR};
// 
//   private int power = genRandomPower();
//   private int divisor = 2;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // julia3Dq by Zueuk, http://zueuk.deviantart.com/art/juliaq-Apophysis-plugins-340813357
//     double a = atan2(pAffineTP.y, pAffineTP.x) * inv_power + pContext.random(Integer.MAX_VALUE) * inv_power_2pi;
//     double sina = sin(a);
//     double cosa = cos(a);
//     double z = pAffineTP.z * abs_inv_power;
//     double r2d = sqr(pAffineTP.x) + sqr(pAffineTP.y);
//     double r = pAmount * pow(r2d + sqr(z), half_inv_power);
//     pVarTP.z += r * z;
//     r *= sqrt(r2d);
//     pVarTP.x += r * cosa;
//     pVarTP.y += r * sina;
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{power, divisor};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_POWER.equalsIgnoreCase(pName)) {
//       power = Tools.FTOI(pValue);
//     } else if (PARAM_DIVISOR.equalsIgnoreCase(pName))
//       divisor = Tools.FTOI(pValue);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "julia3Dq";
//   }
// 
//   private int genRandomPower() {
//     int res = (int) (Math.random() * 5.0 + 2.5);
//     return Math.random() < 0.5 ? res : -res;
//   }
// 
//   private double inv_power, abs_inv_power, half_inv_power, inv_power_2pi;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     inv_power = (double) divisor / (double) power;
//     abs_inv_power = fabs(inv_power);
//     half_inv_power = 0.5 * inv_power - 0.5;
//     inv_power_2pi = M_2PI / (double) power;
//   }
// 
// }
// 
