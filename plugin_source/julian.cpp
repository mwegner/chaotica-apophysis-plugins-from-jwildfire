/*
    Apophysis Plugin: julian

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/JuliaNFunc.java

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
	double dist;
	int _absPower;
	double _cPower;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "julian_"
#include "plugin.h"

APO_PLUGIN("julian");
APO_VARIABLES(
	VAR_INTEGER(power, 0),
	VAR_REAL(dist, 1),

);


int genRandomPower (Variation* vp) {

    int res = (int) (GOODRAND_01() * 5.0 + 2.5);
    return GOODRAND_01() < 0.5 ? res : -res;
}


int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
    VAR(_absPower) = iabs((VAR(power)));
    VAR(_cPower) = VAR(dist) / VAR(power) * 0.5;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double a = (atan2(FTy, FTx) + 2 * M_PI * GOODRAND_0X(VAR(_absPower))) / VAR(power);
    double sina = sin(a);
    double cosa = cos(a);
    double r = VVAR * pow(sqr(FTx) + sqr(FTy), VAR(_cPower));

    FPx = FPx + r * cosa;
    FPy = FPy + r * sina;
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
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class JuliaNFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_POWER = "power";
//   private static final String PARAM_DIST = "dist";
//   private static final String[] paramNames = {PARAM_POWER, PARAM_DIST};
// 
//   private int power = genRandomPower();
//   private double dist = 1;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double a = (atan2(pAffineTP.y, pAffineTP.x) + 2 * M_PI * pContext.random(absPower)) / power;
//     double sina = sin(a);
//     double cosa = cos(a);
//     double r = pAmount * pow(sqr(pAffineTP.x) + sqr(pAffineTP.y), cPower);
// 
//     pVarTP.x = pVarTP.x + r * cosa;
//     pVarTP.y = pVarTP.y + r * sina;
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
//     return new Object[]{power, dist};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_POWER.equalsIgnoreCase(pName))
//       power = Tools.FTOI(pValue);
//     else if (PARAM_DIST.equalsIgnoreCase(pName))
//       dist = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "julian";
//   }
// 
//   private int genRandomPower() {
//     int res = (int) (Math.random() * 5.0 + 2.5);
//     return Math.random() < 0.5 ? res : -res;
//   }
// 
//   private int absPower;
//   private double cPower;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     absPower = iabs(Tools.FTOI(power));
//     cPower = dist / power * 0.5;
//   }
// 
// }
// 
