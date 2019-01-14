/*
    Apophysis Plugin: ztwister

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ZTwisterFunc.java

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
	double twist;
	double base; // random01()

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "ztwister_"
#include "plugin.h"

APO_PLUGIN("ztwister");
APO_VARIABLES(
	VAR_REAL(twist, 4.2),
	VAR_REAL(base, 0),

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // ztwister by dark-beam, http://jwildfire.org/forum/viewtopic.php?f=23&t=1500&p=2891#p2891
    double ez = VAR(twist) * FPz;
    if (VAR(base) != 1.0) {
      ez = pow(VAR(base), ez) - 1;
    }
    double sinz = sin(ez);
    double cosz = cos(ez);
    double nx = FTx * cosz - FTy * sinz;
    double ny = FTx * sinz + FTy * cosz;

    FPx += VVAR * nx;
    FPy += VVAR * ny;
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
// public class ZTwisterFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_TWIST = "twist";
//   private static final String PARAM_BASE = "base";
//   private static final String[] paramNames = {PARAM_TWIST, PARAM_BASE};
// 
//   private double twist = 4.2;
//   private double base = Math.E;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // ztwister by dark-beam, http://jwildfire.org/forum/viewtopic.php?f=23&t=1500&p=2891#p2891
//     double ez = twist * pVarTP.z;
//     if (base != 1.0) {
//       ez = pow(base, ez) - 1;
//     }
//     double sinz = sin(ez);
//     double cosz = cos(ez);
//     double nx = pAffineTP.x * cosz - pAffineTP.y * sinz;
//     double ny = pAffineTP.x * sinz + pAffineTP.y * cosz;
// 
//     pVarTP.x += pAmount * nx;
//     pVarTP.y += pAmount * ny;
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
//     return new Object[]{twist, base};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_TWIST.equalsIgnoreCase(pName))
//       twist = pValue;
//     else if (PARAM_BASE.equalsIgnoreCase(pName))
//       base = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "ztwister";
//   }
// 
// }
// 