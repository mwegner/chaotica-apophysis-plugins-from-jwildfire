#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: npolar

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/NPolarFunc.java

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
	int parity;
	int n;
	double _vvar;
	double _vvar_2;
	int _nnz;
	int _isodd;
	double _cn;
	double _absn;

} Variables;

#define APO_VARIABLE_PREFIX "npolar_"
#include "plugin.h"

APO_PLUGIN("npolar");
APO_VARIABLES(
	VAR_INTEGER(parity, 0),
	VAR_INTEGER(n, 1)

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_nnz) = (VAR(n) == 0) ? 1 : VAR(n);
    VAR(_vvar) = VVAR / M_PI;
    VAR(_vvar_2) = VAR(_vvar) * 0.5;
    VAR(_absn) = fabs(VAR(_nnz));
    VAR(_cn) = 1.0 / VAR(_nnz) / 2.0;
    VAR(_isodd) = iabs(VAR(parity)) % 2;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double x = (VAR(_isodd) != 0) ? FTx : VAR(_vvar) * atan2(FTx, FTy);
    double y = (VAR(_isodd) != 0) ? FTy : VAR(_vvar_2) * log(FTx * FTx + FTy * FTy);
    double angle = (atan2(y, x) + M_2PI * (GOODRAND_0X(INT_MAX) % (int) VAR(_absn))) / VAR(_nnz);
    double r = VVAR * pow(sqr(x) + sqr(y), VAR(_cn)) * ((VAR(_isodd) == 0) ? 1.0 : VAR(parity));
    double sina = sin(angle);
    double cosa = cos(angle);
    cosa *= r;
    sina *= r;
    x = (VAR(_isodd) != 0) ? cosa : (VAR(_vvar_2) * log(cosa * cosa + sina * sina));
    y = (VAR(_isodd) != 0) ? sina : (VAR(_vvar) * atan2(cosa, sina));
    FPx += x;
    FPy += y;
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
// public class NPolarFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_PARITY = "parity";
//   private static final String PARAM_N = "n";
// 
//   private static final String[] paramNames = {PARAM_PARITY, PARAM_N};
// 
//   private int parity = 0;
//   private int n = 1;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double x = (this._isodd != 0) ? pAffineTP.x : this._vvar * atan2(pAffineTP.x, pAffineTP.y);
//     double y = (this._isodd != 0) ? pAffineTP.y : this._vvar_2 * log(pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y);
//     double angle = (atan2(y, x) + M_2PI * (pContext.random(Integer.MAX_VALUE) % (int) this._absn)) / this._nnz;
//     double r = pAmount * pow(sqr(x) + sqr(y), this._cn) * ((this._isodd == 0) ? 1.0 : this.parity);
//     double sina = sin(angle);
//     double cosa = cos(angle);
//     cosa *= r;
//     sina *= r;
//     x = (this._isodd != 0) ? cosa : (this._vvar_2 * log(cosa * cosa + sina * sina));
//     y = (this._isodd != 0) ? sina : (this._vvar * atan2(cosa, sina));
//     pVarTP.x += x;
//     pVarTP.y += y;
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
//     return new Object[]{parity, n};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_PARITY.equalsIgnoreCase(pName))
//       parity = Tools.FTOI(pValue);
//     else if (PARAM_N.equalsIgnoreCase(pName))
//       n = Tools.FTOI(pValue);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "npolar";
//   }
// 
//   private double _vvar;
//   private double _vvar_2;
// 
//   private int _nnz;
//   private int _isodd;
// 
//   private double _cn;
//   private double _absn;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     this._nnz = (this.n == 0) ? 1 : this.n;
//     this._vvar = pAmount / M_PI;
//     this._vvar_2 = this._vvar * 0.5;
//     this._absn = fabs(this._nnz);
//     this._cn = 1.0 / this._nnz / 2.0;
//     this._isodd = iabs(parity) % 2;
//   }
// 
// }
// 
