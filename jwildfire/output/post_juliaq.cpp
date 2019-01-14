/*
    Apophysis Plugin: post_juliaq

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PostJuliaQFunc.java

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
	double _half_inv_power;
	double _inv_power;
	double _inv_power_2pi;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "post_juliaq_"
#include "plugin.h"

APO_PLUGIN("post_juliaq");
APO_VARIABLES(
	VAR_INTEGER(power, 0),
	VAR_INTEGER(divisor, 2),

);


int genRandomPower (Variation* vp) {

    int res = (int) (GOODRAND_01() * 5.0 + 2.5);
    return GOODRAND_01() < 0.5 ? res : -res;
}


int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
    VAR(_half_inv_power) = 0.5 * VAR(divisor) / (double) VAR(power);
    VAR(_inv_power) = VAR(divisor) / (double) VAR(power);
    VAR(_inv_power_2pi) = M_2PI / (double) VAR(power);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // post_juliaq by Zueuk, http://zueuk.deviantart.com/art/juliaq-Apophysis-plugins-340813357
    double a = atan2(FPy, FPx) * VAR(_inv_power) + GOODRAND_0X(INT_MAX) * VAR(_inv_power_2pi);
    double sina = sin(a);
    double cosa = cos(a);
    double r = VVAR * pow(sqr(FPx) + sqr(FPy), VAR(_half_inv_power));
    FPx = r * cosa;
    FPy = r * sina;


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
// public class PostJuliaQFunc extends VariationFunc {
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
//     // post_juliaq by Zueuk, http://zueuk.deviantart.com/art/juliaq-Apophysis-plugins-340813357
//     double a = atan2(pVarTP.y, pVarTP.x) * inv_power + pContext.random(Integer.MAX_VALUE) * inv_power_2pi;
//     double sina = sin(a);
//     double cosa = cos(a);
//     double r = pAmount * pow(sqr(pVarTP.x) + sqr(pVarTP.y), half_inv_power);
//     pVarTP.x = r * cosa;
//     pVarTP.y = r * sina;
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
//     return "post_juliaq";
//   }
// 
//   private int genRandomPower() {
//     int res = (int) (Math.random() * 5.0 + 2.5);
//     return Math.random() < 0.5 ? res : -res;
//   }
// 
//   private double half_inv_power, inv_power, inv_power_2pi;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     half_inv_power = 0.5 * divisor / (double) power;
//     inv_power = divisor / (double) power;
//     inv_power_2pi = M_2PI / (double) power;
//   }
// 
//   @Override
//   public int getPriority() {
//     return 1;
//   }
// 
// }
// 
