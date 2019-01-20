#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: disc2

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Disc2Func.java

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
	double rot;
	double twist;
	double _timespi = 0.0;
	double _sinadd = 0.0;
	double _cosadd = 0.0;

} Variables;

#define APO_VARIABLE_PREFIX "disc2_"
#include "plugin.h"

APO_PLUGIN("disc2");
APO_VARIABLES(
	VAR_REAL(rot, 2.0),
	VAR_REAL(twist, 0.50)

);



int PluginVarPrepare(Variation* vp)
{
   VAR(_timespi) = 0.0;
   VAR(_sinadd) = 0.0;
   VAR(_cosadd) = 0.0;
    double add = VAR(twist);
    VAR(_timespi) = VAR(rot) * M_PI;
    VAR(_sinadd) = sin(add);
    VAR(_cosadd) = cos(add);
    VAR(_cosadd) -= 1;
    double k;
    if (add > 2.0 * M_PI) {
      k = (1 + add - 2.0 * M_PI);
      VAR(_cosadd) *= k;
      VAR(_sinadd) *= k;
    }
    if (add < -2.0 * M_PI) {
      k = (1 + add + 2.0 * M_PI);
      VAR(_cosadd) *= k;
      VAR(_sinadd) *= k;
    }

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* Z+ variation Jan 07 */
    double t = VAR(_timespi) * (FTx + FTy);
    double sinr = sin(t);
    double cosr = cos(t);
    double r = VVAR * atan2(FTx, FTy) / M_PI;

    FPx += (sinr + VAR(_cosadd)) * r;
    FPy += (cosr + VAR(_sinadd)) * r;

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
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class Disc2Func extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_ROT = "rot";
//   private static final String PARAM_TWIST = "twist";
// 
//   private static final String[] paramNames = {PARAM_ROT, PARAM_TWIST};
// 
//   private double rot = 2.0;
//   private double twist = 0.50;
//   // precalculated
//   private double timespi = 0.0;
//   private double sinadd = 0.0;
//   private double cosadd = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* Z+ variation Jan 07 */
//     double t = timespi * (pAffineTP.x + pAffineTP.y);
//     double sinr = sin(t);
//     double cosr = cos(t);
//     double r = pAmount * pAffineTP.getPrecalcAtan() / M_PI;
// 
//     pVarTP.x += (sinr + cosadd) * r;
//     pVarTP.y += (cosr + sinadd) * r;
// 
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
// 
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{rot, twist};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_ROT.equalsIgnoreCase(pName))
//       rot = pValue;
//     else if (PARAM_TWIST.equalsIgnoreCase(pName))
//       twist = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "disc2";
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     double add = twist;
//     timespi = rot * M_PI;
//     sinadd = sin(add);
//     cosadd = cos(add);
//     cosadd -= 1;
//     double k;
//     if (add > 2.0 * M_PI) {
//       k = (1 + add - 2.0 * M_PI);
//       cosadd *= k;
//       sinadd *= k;
//     }
//     if (add < -2.0 * M_PI) {
//       k = (1 + add + 2.0 * M_PI);
//       cosadd *= k;
//       sinadd *= k;
//     }
//   }
// 
// }
// 
