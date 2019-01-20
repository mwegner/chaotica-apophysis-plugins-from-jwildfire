#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: lissajous

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/LissajousFunc.java

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
	double tmin; // -M_PI
	double tmax; // M_PI
	double a;
	double b;
	double c;
	double d;
	double e;

} Variables;

#define APO_VARIABLE_PREFIX "lissajous_"
#include "plugin.h"

APO_PLUGIN("lissajous");
APO_VARIABLES(
	VAR_REAL(tmin, -M_PI),
	VAR_REAL(tmax, M_PI),
	VAR_REAL(a, 3.0),
	VAR_REAL(b, 2.0),
	VAR_REAL(c, 0.0),
	VAR_REAL(d, 0.0),
	VAR_REAL(e, 0.0)

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // Lissajous plugin by Jed Kelsey, http://lu-kout.deviantart.com/art/Apophysis-Plugin-Pack-1-v0-4-59907275
    double t = (VAR(tmax) - VAR(tmin)) * GOODRAND_01() + VAR(tmin);
    double y = GOODRAND_01() - 0.5;
    double x1 = sin(VAR(a) * t + VAR(d));
    double y1 = sin(VAR(b) * t);

    FPx += VVAR * (x1 + VAR(c) * t + VAR(e) * y);
    FPy += VVAR * (y1 + VAR(c) * t + VAR(e) * y);

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
// import static org.jwildfire.base.mathlib.MathLib.M_PI;
// import static org.jwildfire.base.mathlib.MathLib.sin;
// 
// public class LissajousFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_TMIN = "tmin";
//   private static final String PARAM_TMAX = "tmax";
//   private static final String PARAM_A = "a";
//   private static final String PARAM_B = "b";
//   private static final String PARAM_C = "c";
//   private static final String PARAM_D = "d";
//   private static final String PARAM_E = "e";
// 
//   private static final String[] paramNames = {PARAM_TMIN, PARAM_TMAX, PARAM_A, PARAM_B, PARAM_C, PARAM_D, PARAM_E};
// 
//   private double tmin = -M_PI;
//   private double tmax = M_PI;
//   private double a = 3.0;
//   private double b = 2.0;
//   private double c = 0.0;
//   private double d = 0.0;
//   private double e = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // Lissajous plugin by Jed Kelsey, http://lu-kout.deviantart.com/art/Apophysis-Plugin-Pack-1-v0-4-59907275
//     double t = (tmax - tmin) * pContext.random() + tmin;
//     double y = pContext.random() - 0.5;
//     double x1 = sin(a * t + d);
//     double y1 = sin(b * t);
// 
//     pVarTP.x += pAmount * (x1 + c * t + e * y);
//     pVarTP.y += pAmount * (y1 + c * t + e * y);
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
//     return new Object[]{tmin, tmax, a, b, c, d, e};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_TMIN.equalsIgnoreCase(pName))
//       tmin = pValue;
//     else if (PARAM_TMAX.equalsIgnoreCase(pName))
//       tmax = pValue;
//     else if (PARAM_A.equalsIgnoreCase(pName))
//       a = pValue;
//     else if (PARAM_B.equalsIgnoreCase(pName))
//       b = pValue;
//     else if (PARAM_C.equalsIgnoreCase(pName))
//       c = pValue;
//     else if (PARAM_D.equalsIgnoreCase(pName))
//       d = pValue;
//     else if (PARAM_E.equalsIgnoreCase(pName))
//       e = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "lissajous";
//   }
// 
// }
// 
