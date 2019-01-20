#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: hyperbolicellipse

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/HyperbolicEllipseFunc.java

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
	double _a = 1.0;

} Variables;

#define APO_VARIABLE_PREFIX "hyperbolicellipse_"
#include "plugin.h"

APO_PLUGIN("hyperbolicellipse");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_a) = 1.0;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /*

     */
    double u;
    double v;
    u = FTx;
    v = FTy;

    double xt = a * (y + b) * cos(k * x);
    double yt = a * (y + b) * sin(k * x);

    FPx = xt * VVAR;
    FPy = xy * VVAR;



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
// public class HyperbolicEllipseFunc extends VariationFunc {
//   /**
//    *
//    */
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
// 
// 
//   private static final String[] paramNames = {PARAM_A};
// 
// 
//   double a = 1.0;
// 
// 
//   XY Eval(double x, double y) {
//     XY p;
//     double xt, yt;
// 
//     xt = ((Math.exp(x) - Math.exp(-x)) / 2) * Math.cos(a * y);
//     yt = ((Math.exp(x) + Math.exp(-x)) / 2) * Math.sin(a * y);
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
//     return "hyperbolicellipse";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   public Object[] getParameterValues() {
//     return new Object[]{a};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_A)) {
//       a = pValue;
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// }
// 
