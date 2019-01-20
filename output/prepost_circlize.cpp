#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: prepost_circlize

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PrePostCirclizeFunc.java

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
	int n;
	double rotation;
	double _rot_rad = 0.0; // M_PI_4
	int reverse;
	double _pi_n;
	double _cospi_n;

} Variables;

#define APO_VARIABLE_PREFIX "prepost_circlize_"
#include "plugin.h"

APO_PLUGIN("prepost_circlize");
APO_VARIABLES(
	VAR_INTEGER(n, 4),
	VAR_REAL(rotation, 45),
	VAR_INTEGER(reverse, 0)

);


void circlize (Variation* vp double pAmount) {

    double theta = atan2(FTx, FTy);
    double r = (sqrt(FTx * FTx + FTy * FTy) + SMALL_EPSILON);
    double factor = VAR(_cospi_n) / cos((theta - VAR(_rot_rad)) - VAR(_pi_n) * (2 * floor((VAR(n) * (theta - VAR(_rot_rad))) / M_2PI) + 1));

    FPx = lerp(vp, r, r / factor, VVAR) * cos(theta);
    FPy = lerp(vp, r, r / factor, VVAR) * sin(theta);
}

void uncirclize (Variation* vp double pAmount) {

    double theta = atan2(FTx, FTy);
    double r = (sqrt(FTx * FTx + FTy * FTy) + SMALL_EPSILON);
    double factor = VAR(_cospi_n) / cos((theta - VAR(_rot_rad)) - VAR(_pi_n) * (2 * floor((VAR(n) * (theta - VAR(_rot_rad))) / M_2PI) + 1));

    FPx = lerp(vp, r, r * factor, VVAR) * cos(theta);
    FPy = lerp(vp, r, r * factor, VVAR) * sin(theta);
}

void invtransform (Variation* vp) {

    if (VAR(reverse) == 0) {
      circlize(vp, VVAR);
    } else {
      uncirclize(vp, vp, VVAR);
    }
}

double lerp (Variation* vp, double v0, double v1, double t) {

    return (1 - t) * v0 + t * v1;
}


int PluginVarPrepare(Variation* vp)
{
   VAR(_rot_rad) = 0.0;
    VAR(_pi_n) = M_PI / VAR(n);
    VAR(_cospi_n) = cos(VAR(_pi_n));

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    if (VAR(reverse) == 0) {
      uncirclize(vp, vp, pVarTP, pVarTP, VVAR);
    } else {
      circlize(vp, pVarTP, pVarTP, VVAR);
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
// public class PrePostCirclizeFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_N = "n";
//   private static final String PARAM_ROTATION = "rotation";
//   private static final String PARAM_REVERSE = "reverse";
// 
//   private static final String[] paramNames = {PARAM_N, PARAM_ROTATION, PARAM_REVERSE};
// 
//   private int n = 4;
//   private double rotation = 45;
//   private double rot_rad = M_PI_4;
//   private int reverse = 0;
// 
//   private double pi_n, cospi_n;
// 
//   private void circlize(XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double theta = pAffineTP.getPrecalcAtanYX();
//     double r = pAffineTP.getPrecalcSqrt();
//     double factor = cospi_n / cos((theta - rot_rad) - pi_n * (2 * floor((n * (theta - rot_rad)) / M_2PI) + 1));
// 
//     pVarTP.x = lerp(r, r / factor, pAmount) * cos(theta);
//     pVarTP.y = lerp(r, r / factor, pAmount) * sin(theta);
//   }
// 
//   private void uncirclize(XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double theta = pAffineTP.getPrecalcAtanYX();
//     double r = pAffineTP.getPrecalcSqrt();
//     double factor = cospi_n / cos((theta - rot_rad) - pi_n * (2 * floor((n * (theta - rot_rad)) / M_2PI) + 1));
// 
//     pVarTP.x = lerp(r, r * factor, pAmount) * cos(theta);
//     pVarTP.y = lerp(r, r * factor, pAmount) * sin(theta);
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     pi_n = M_PI / n;
//     cospi_n = cos(pi_n);
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     if (reverse == 0) {
//       uncirclize(pVarTP, pVarTP, pAmount);
//     } else {
//       circlize(pVarTP, pVarTP, pAmount);
//     }
//   }
// 
//   @Override
//   public void invtransform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     if (reverse == 0) {
//       circlize(pAffineTP, pAffineTP, pAmount);
//     } else {
//       uncirclize(pAffineTP, pAffineTP, pAmount);
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
//     return new Object[]{n, rotation, reverse};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_N.equalsIgnoreCase(pName))
//       n = limitIntVal(Tools.FTOI(pValue), 3, 50);
//     else if (PARAM_ROTATION.equalsIgnoreCase(pName)) {
//       rotation = pValue;
//       rot_rad = rotation * M_PI / 180;
//     } else if (PARAM_REVERSE.equalsIgnoreCase(pName))
//       reverse = limitIntVal(Tools.FTOI(pValue), 0, 1);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "prepost_circlize";
//   }
// 
//   @Override
//   public int getPriority() {
//     return 2;
//   }
// 
//   private double lerp(double v0, double v1, double t) {
//     return (1 - t) * v0 + t * v1;
//   }
// 
// }
// 
