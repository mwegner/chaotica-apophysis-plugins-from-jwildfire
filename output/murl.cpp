#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: murl

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/MurlFunc.java

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
	double _c;
	double _p2;
	double _vp;
	double _sina;
	double _cosa;
	double _a;
	double _r;
	double _re;
	double _im;
	double _rl;
	double c;
	int power;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "murl_"
#include "plugin.h"

APO_PLUGIN("murl");
APO_VARIABLES(
	VAR_REAL(c, 0.1),
	VAR_INTEGER(power, 1),

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    VAR(_c) = VAR(c);
    if (VAR(power) != 1) {
      VAR(_c) /= ((double) VAR(power) - 1);
    }
    VAR(_p2) = (double) VAR(power) / 2.0;
    VAR(_vp) = VVAR * (VAR(_c) + 1);

    VAR(_a) = atan2(FTy, FTx) * (double) VAR(power);
    VAR(_sina) = sin(VAR(_a));
    VAR(_cosa) = cos(VAR(_a));

    VAR(_r) = VAR(_c) * pow(sqr(FTx) + sqr(FTy), VAR(_p2));

    VAR(_re) = VAR(_r) * VAR(_cosa) + 1;
    VAR(_im) = VAR(_r) * VAR(_sina);
    VAR(_rl) = VAR(_vp) / (sqr(VAR(_re)) + sqr(VAR(_im)));

    FPx += VAR(_rl) * (FTx * VAR(_re) + FTy * VAR(_im));
    FPy += VAR(_rl) * (FTy * VAR(_re) - FTx * VAR(_im));
    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }


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
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class MurlFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   /*
//    Original function written in C by Peter Sdobnov (Zueuk).
//    Transcribed into Java by Nic Anderson (chronologicaldot)
//    */
// 
//   private double _c, _p2, _vp;
// 
//   // temp variables (instantiated here to speed up processing)
//   private double _sina, _cosa, _a, _r, _re, _im, _rl;
// 
//   private static final String PARAM_C = "c";
//   private static final String PARAM_POWER = "power";
// 
//   private static final String[] paramNames = {PARAM_C, PARAM_POWER};
// 
//   private double c = 0.1;
//   private int power = 1;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     _c = c;
//     if (power != 1) {
//       _c /= ((double) power - 1);
//     }
//     _p2 = (double) power / 2.0;
//     _vp = pAmount * (_c + 1);
// 
//     _a = atan2(pAffineTP.y, pAffineTP.x) * (double) power;
//     _sina = sin(_a);
//     _cosa = cos(_a);
// 
//     _r = _c * pow(sqr(pAffineTP.x) + sqr(pAffineTP.y), _p2);
// 
//     _re = _r * _cosa + 1;
//     _im = _r * _sina;
//     _rl = _vp / (sqr(_re) + sqr(_im));
// 
//     pVarTP.x += _rl * (pAffineTP.x * _re + pAffineTP.y * _im);
//     pVarTP.y += _rl * (pAffineTP.y * _re - pAffineTP.x * _im);
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "murl";
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{c, power};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_POWER.equalsIgnoreCase(pName))
//       power = (int) pValue;
//     else if (PARAM_C.equalsIgnoreCase(pName))
//       c = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
// }
