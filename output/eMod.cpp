#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: eMod

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/EModFunc.java

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
	double radius;
	double distance;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "eMod_"
#include "plugin.h"

APO_PLUGIN("eMod");
APO_VARIABLES(
	VAR_REAL(radius, 1.0),
	VAR_REAL(distance, 0.0),

);


double sqrt_safe (Variation* vp, double x) {

    if (x <= 0.0)
      return 0.0;
    return sqrt(x);
}


int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // eMod by Michael Faber, http://michaelfaber.deviantart.com/art/eSeries-306044892
    double tmp = FTy * FTy + FTx * FTx + 1.0;
    double tmp2 = 2.0 * FTx;
    double xmax = (sqrt_safe(vp, tmp + tmp2) + sqrt_safe(vp, tmp - tmp2)) * 0.5;
    if (xmax < 1.0)
      xmax = 1.0;
    double sinhmu, coshmu;

    double mu = acosh(xmax); //  mu > 0
    double t = FTx / xmax;
    if (t > 1.0)
      t = 1.0;
    else if (t < -1.0)
      t = -1.0;

    double nu = acos(t); // -Pi < nu < Pi
    if (FTy < 0)
      nu *= -1.0;

    if (mu < VAR(radius) && -mu < VAR(radius)) {
      if (nu > 0.0)
        mu = fmod(mu + VAR(radius) + VAR(distance) * VAR(radius), 2.0 * VAR(radius)) - VAR(radius);
      else
        mu = fmod(mu - VAR(radius) - VAR(distance) * VAR(radius), 2.0 * VAR(radius)) + VAR(radius);
    }

    sinhmu = sinh(mu);
    coshmu = cosh(mu);

    FPx += VVAR * coshmu * cos(nu);
    FPy += VVAR * sinhmu * sin(nu);
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
// public class EModFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_RADIUS = "radius";
//   private static final String PARAM_DISTANCE = "distance";
// 
//   private static final String[] paramNames = {PARAM_RADIUS, PARAM_DISTANCE};
// 
//   private double radius = 1.0;
//   private double distance = 0.0;
// 
//   //Taking the square root of numbers close to zero is dangerous.  If x is negative
//   //due to floating point errors we get NaN results.
//   private double sqrt_safe(double x) {
//     if (x <= 0.0)
//       return 0.0;
//     return sqrt(x);
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // eMod by Michael Faber, http://michaelfaber.deviantart.com/art/eSeries-306044892
//     double tmp = pAffineTP.y * pAffineTP.y + pAffineTP.x * pAffineTP.x + 1.0;
//     double tmp2 = 2.0 * pAffineTP.x;
//     double xmax = (sqrt_safe(tmp + tmp2) + sqrt_safe(tmp - tmp2)) * 0.5;
//     if (xmax < 1.0)
//       xmax = 1.0;
//     double sinhmu, coshmu;
// 
//     double mu = acosh(xmax); //  mu > 0
//     double t = pAffineTP.x / xmax;
//     if (t > 1.0)
//       t = 1.0;
//     else if (t < -1.0)
//       t = -1.0;
// 
//     double nu = acos(t); // -Pi < nu < Pi
//     if (pAffineTP.y < 0)
//       nu *= -1.0;
// 
//     if (mu < radius && -mu < radius) {
//       if (nu > 0.0)
//         mu = fmod(mu + radius + distance * radius, 2.0 * radius) - radius;
//       else
//         mu = fmod(mu - radius - distance * radius, 2.0 * radius) + radius;
//     }
// 
//     sinhmu = sinh(mu);
//     coshmu = cosh(mu);
// 
//     pVarTP.x += pAmount * coshmu * cos(nu);
//     pVarTP.y += pAmount * sinhmu * sin(nu);
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
//     return new Object[]{radius, distance};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_RADIUS.equalsIgnoreCase(pName))
//       radius = limitVal(pValue, 0.0, Double.MAX_VALUE);
//     else if (PARAM_DISTANCE.equalsIgnoreCase(pName))
//       distance = limitVal(pValue, 0.0, 2.0);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "eMod";
//   }
// 
// }
// 
