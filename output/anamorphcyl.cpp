#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: anamorphcyl

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/AnamorphCylFunc.java

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
	double a = 1.0;
	double b = 1.3;
	double k = 3.0;

} Variables;

#define APO_VARIABLE_PREFIX "anamorphcyl_"
#include "plugin.h"

APO_PLUGIN("anamorphcyl");
APO_VARIABLES(
    VAR_REAL(a, 1.0),
    VAR_REAL(b, 1.3),
    VAR_REAL(k, 3.0),
);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /*

     */

    double xt = VAR(a) * (FTy + VAR(b)) * cos(VAR(k) * FTx);
    double yt = VAR(a) * (FTy + VAR(b)) * sin(VAR(k) * FTx);

    FPx = xt * VVAR;
    FPy = yt * VVAR;

    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// 
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class AnamorphCylFunc extends VariationFunc {
//   /**
//    * @author Jesus Sosa
//    * @date July 11, 2018
//    * anamorphcyl transformation
//    * x1=a*(y+b)*cos(c*x)
//    * y1=a*(y+b)*sin(c*x)
//    * Parameters
//    * a: scaling Factor of the anamorphic image
//    * b: Affect displacement of anamorphic image out to a finite radius
//    * c: Constant to spread the range of x values in the original image
//    * over an angle in the anamorphic image.
//    **/
// 
//   static public class XY {
//     public double x;
//     public double y;
// 
//     public XY(double x, double y) {
//       this.x = x;
//       this.y = y;
//     }
//   }
// 
//   private static final long serialVersionUID = 1L;
// 
// 
//   private static final String PARAM_A = "a";
//   private static final String PARAM_B = "b";
//   private static final String PARAM_K = "k";
// 
//   private static final String[] paramNames = {PARAM_A, PARAM_B, PARAM_K};
// 
// 
//   double a = 1.0;
//   double b = 1.3;
//   double k = 3.0;
// 
// 
//   XY Eval(double x, double y) {
//     XY p;
//     double xt, yt;
// 
//     xt = a * (y + b) * Math.cos(k * x);
//     yt = a * (y + b) * Math.sin(k * x);
// 
//     p = new XY(xt, yt);
//     return (p);
//   }
// 
// 
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /*
// 
//      */
//     double u;
//     double v;
//     u = pAffineTP.x;
//     v = pAffineTP.y;
// 
//     XY p = Eval(u, v);
// 
//     pVarTP.x = p.x * pAmount;
//     pVarTP.y = p.y * pAmount;
// 
//   }
// 
//   public String getName() {
//     return "anamorphcyl";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   public Object[] getParameterValues() {
//     return new Object[]{a, b, k};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_A)) {
//       a = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_B)) {
//       b = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_K)) {
//       k = pValue;
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// }
// 
