#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: curl3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Curl3DFunc.java

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
	double _c2x;
	double _c2y;
	double _c2z;
	double _c2;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "curl3D_"
#include "plugin.h"

APO_PLUGIN("curl3D");
APO_VARIABLES(
	VAR_REAL(cx, 0),
	VAR_REAL(cy, 0.05),
	VAR_REAL(cz, 0.05),

);


double sqr (Variation* vp, double pVal) {

    return pVal * pVal;
}


int PluginVarPrepare(Variation* vp)
{
    VAR(_c2x) = 2 * VAR(cx);
    VAR(_c2y) = 2 * VAR(cy);
    VAR(_c2z) = 2 * VAR(cz);

    double cx2 = sqr(vp, VAR(cx));
    double cy2 = sqr(vp, VAR(cy));
    double cz2 = sqr(vp, VAR(cz));

    VAR(_c2) = cx2 + cy2 + cz2;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double r2 = sqr(vp, FTx) + sqr(vp, FTy) + sqr(vp, FTz);
    double r = VVAR / (r2 * VAR(_c2) + VAR(_c2x) * FTx - VAR(_c2y) * FTy + VAR(_c2z) * FTz + 1);

    FPx += r * (FTx + VAR(cx) * r2);
    FPy += r * (FTy - VAR(cy) * r2);
    FPz += r * (FTz + VAR(cz) * r2);


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
// public class Curl3DFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_CX = "cx";
//   private static final String PARAM_CY = "cy";
//   private static final String PARAM_CZ = "cz";
//   private static final String[] paramNames = {PARAM_CX, PARAM_CY, PARAM_CZ};
// 
//   private double cx = 0;
//   private double cy = 0.05;
//   private double cz = 0.05;
// 
//   private double sqr(double pVal) {
//     return pVal * pVal;
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double r2 = sqr(pAffineTP.x) + sqr(pAffineTP.y) + sqr(pAffineTP.z);
//     double r = pAmount / (r2 * c2 + c2x * pAffineTP.x - c2y * pAffineTP.y + c2z * pAffineTP.z + 1);
// 
//     pVarTP.x += r * (pAffineTP.x + cx * r2);
//     pVarTP.y += r * (pAffineTP.y - cy * r2);
//     pVarTP.z += r * (pAffineTP.z + cz * r2);
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
//     return "curl3D";
//   }
// 
//   private double c2x, c2y, c2z, c2;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     c2x = 2 * cx;
//     c2y = 2 * cy;
//     c2z = 2 * cz;
// 
//     double cx2 = sqr(cx);
//     double cy2 = sqr(cy);
//     double cz2 = sqr(cz);
// 
//     c2 = cx2 + cy2 + cz2;
//   }
// 
// }
// 
