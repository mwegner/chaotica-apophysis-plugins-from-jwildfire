/*
    Apophysis Plugin: murl2

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Murl2Func.java

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
	double _p2;
	double _invp;
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

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "murl2_"
#include "plugin.h"

APO_PLUGIN("murl2");
APO_VARIABLES(
	VAR_REAL(c, 0.1),
	VAR_INTEGER(power, 3),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{

    VAR(_p2) = (double) VAR(power) / 2.0;

    if (VAR(power) != 0) {
      VAR(_invp) = 1.0 / (double) VAR(power);
      if (VAR(c) == -1) {
        VAR(_vp) = 0;
      } else {
        VAR(_vp) = VVAR * pow(VAR(c) + 1, 2.0 / ((double) VAR(power)));
      }
    } else {
      VAR(_invp) = 100000000000.0;
      VAR(_vp) = VVAR * pow(VAR(c) + 1, 4 /*Normally infinity, but we let this be a special case*/);
    }

    VAR(_a) = atan2(FTy, FTx) * (double) VAR(power);
    VAR(_sina) = sin(VAR(_a));
    VAR(_cosa) = cos(VAR(_a));

    VAR(_r) = VAR(c) * pow(sqr(FTx) + sqr(FTy), VAR(_p2));

    VAR(_re) = VAR(_r) * VAR(_cosa) + 1;
    VAR(_im) = VAR(_r) * VAR(_sina);

    VAR(_r) = pow(sqr(VAR(_re)) + sqr(VAR(_im)), VAR(_invp));
    VAR(_a) = atan2(VAR(_im), VAR(_re)) * 2.0 * VAR(_invp);
    VAR(_re) = VAR(_r) * cos(VAR(_a));
    VAR(_im) = VAR(_r) * sin(VAR(_a));

    VAR(_rl) = VAR(_vp) / sqr(VAR(_r));

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
// public class Murl2Func extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   /*
//    Original function written in C by Peter Sdobnov (Zueuk).
//    Transcribed into Java by Nic Anderson (chronologicaldot)
//    */
// 
//   private double _p2, _invp, _vp;
// 
//   // temp variables (instantiated here to speed up processing)
//   private double _sina, _cosa, _a, _r, _re, _im, _rl;
// 
//   private static final String PARAM_C = "c";
//   public static final String PARAM_POWER = "power";
// 
//   private static final String[] paramNames = {PARAM_C, PARAM_POWER};
// 
//   private double c = 0.1;
//   private int power = 3;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// 
//     _p2 = (double) power / 2.0;
// 
//     if (power != 0) {
//       _invp = 1.0 / (double) power;
//       if (c == -1) {
//         _vp = 0;
//       } else {
//         _vp = pAmount * pow(c + 1, 2.0 / ((double) power));
//       }
//     } else {
//       _invp = 100000000000.0;
//       _vp = pAmount * pow(c + 1, 4 /*Normally infinity, but we let this be a special case*/);
//     }
// 
//     _a = atan2(pAffineTP.y, pAffineTP.x) * (double) power;
//     _sina = sin(_a);
//     _cosa = cos(_a);
// 
//     _r = c * pow(sqr(pAffineTP.x) + sqr(pAffineTP.y), _p2);
// 
//     _re = _r * _cosa + 1;
//     _im = _r * _sina;
// 
//     _r = pow(sqr(_re) + sqr(_im), _invp);
//     _a = atan2(_im, _re) * 2.0 * _invp;
//     _re = _r * cos(_a);
//     _im = _r * sin(_a);
// 
//     _rl = _vp / sqr(_r);
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
//     return "murl2";
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
// 
