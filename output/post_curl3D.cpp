#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: post_curl3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PostCurl3DFunc.java

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
	double cx;
	double cy;
	double cz;
	double _cx;
	double _cy;
	double _cz;
	double _c2x;
	double _c2y;
	double _c2z;
	double _cx2;
	double _cy2;
	double _cz2;
	double _c_2;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "post_curl3D_"
#include "plugin.h"

APO_PLUGIN("post_curl3D");
APO_VARIABLES(
	VAR_REAL(cx, 0),
	VAR_REAL(cy, 0),
	VAR_REAL(cz, 0),

);


double sqr (Variation* vp, double pVal) {

    return pVal * pVal;
}


int PluginVarPrepare(Variation* vp)
{
    VAR(_cx) = VVAR * VAR(cx);
    VAR(_cy) = VVAR * VAR(cy);
    VAR(_cz) = VVAR * VAR(cz);

    VAR(_c2x) = 2 * VAR(_cx);
    VAR(_c2y) = 2 * VAR(_cy);
    VAR(_c2z) = 2 * VAR(_cz);

    VAR(_cx2) = sqr(vp, VAR(_cx));
    VAR(_cy2) = sqr(vp, VAR(_cy));
    VAR(_cz2) = sqr(vp, VAR(_cz));

    VAR(_c_2) = VAR(_cx2) + VAR(_cy2) + VAR(_cz2);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double r2 = sqr(vp, FPx) + sqr(vp, FPy) + sqr(vp, FPz);
    double r = 1.0 / (r2 * VAR(_c_2) + VAR(_c2x) * FPx - VAR(_c2y) * FPy + VAR(_c2z) * FPz + 1.0);
    FPx = r * (FPx + VAR(_cx) * r2);
    FPy = r * (FPy + VAR(_cy) * r2);
    FPz = r * (FPz + VAR(_cz) * r2);


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
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class PostCurl3DFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_CX = "cx";
//   private static final String PARAM_CY = "cy";
//   private static final String PARAM_CZ = "cz";
//   private static final String[] paramNames = {PARAM_CX, PARAM_CY, PARAM_CZ};
// 
//   private double cx = 0;
//   private double cy = 0;
//   private double cz = 0;
// 
//   private double sqr(double pVal) {
//     return pVal * pVal;
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double r2 = sqr(pVarTP.x) + sqr(pVarTP.y) + sqr(pVarTP.z);
//     double r = 1.0 / (r2 * _c_2 + _c2x * pVarTP.x - _c2y * pVarTP.y + _c2z * pVarTP.z + 1.0);
//     pVarTP.x = r * (pVarTP.x + _cx * r2);
//     pVarTP.y = r * (pVarTP.y + _cy * r2);
//     pVarTP.z = r * (pVarTP.z + _cz * r2);
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{cx, cy, cz};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_CX.equalsIgnoreCase(pName))
//       cx = pValue;
//     else if (PARAM_CY.equalsIgnoreCase(pName))
//       cy = pValue;
//     else if (PARAM_CZ.equalsIgnoreCase(pName))
//       cz = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "post_curl3D";
//   }
// 
//   @Override
//   public int getPriority() {
//     return 1;
//   }
// 
//   private double _cx, _cy, _cz, _c2x, _c2y, _c2z, _cx2, _cy2, _cz2, _c_2;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _cx = pAmount * cx;
//     _cy = pAmount * cy;
//     _cz = pAmount * cz;
// 
//     _c2x = 2 * _cx;
//     _c2y = 2 * _cy;
//     _c2z = 2 * _cz;
// 
//     _cx2 = sqr(_cx);
//     _cy2 = sqr(_cy);
//     _cz2 = sqr(_cz);
// 
//     _c_2 = _cx2 + _cy2 + _cz2;
//   }
// 
// }
// 
