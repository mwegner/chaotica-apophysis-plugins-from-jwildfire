/*
    Apophysis Plugin: jac_asn

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/JacAsnFunc.java

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
	double kr;
	double ki;
	int type;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "jac_asn_"
#include "plugin.h"

APO_PLUGIN("jac_asn");
APO_VARIABLES(
	VAR_REAL(kr, 0.5),
	VAR_REAL(ki, 0.0),
	VAR_INTEGER(type, 1),

    { "WARNING_this_plugin_does_nothing", INTEGER, OFFSET(___warning), 0, 1, 0 },
);


int PluginVarPrepare(Variation* vp)
{
    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// 
// import hehl.gl.Complex;
// import hehl.gl.Msg;
// import org.jwildfire.base.mathlib.MathLib;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// 
// public class JacAsnFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_KR = "kr";
//   private static final String PARAM_KI = "ki";
//   private static final String PARAM_TYPE = "type";
// 
// 
//   private static final String[] paramNames = {PARAM_KR, PARAM_KI, PARAM_TYPE};
// 
//   private double jac_asn_kr = 0.5, jac_asn_ki = 0.0;
//   private int jac_asn_type = 1;
// 
// 
//   // JS added Complex Inverse hyperbolic sin (ref. http://www.suitcaseofdreams.net/Inverse__Hyperbolic_Functions.htm)
//   public static Complex asinh(Complex zz) throws Msg {
//     Complex z = new Complex(1.0, 0.0).plus(zz.times(zz));
//     z = Complex.sqrt(z);
//     z = zz.plus(z);
//     z = Complex.ln(z);
//     return z;
//   }
// 
//   // JS  added function complex inverse sin (ref http://www.suitcaseofdreams.net/Inverse_Functions.htm)
//   public static Complex asin(Complex z) {
//     Complex zz = new Complex(1., 0.0).minus(z.times(z));
//     zz = Complex.sqrt(zz);
//     zz = zz.plus(Complex.j.times(z));
//     zz = Complex.j.times(Complex.ln(zz)).times(-1.);
//     return zz;
//   }
// 
//   //JS added norm complex (ref  http://www.cplusplus.com/reference/complex/norm/)
//   public static double norm(Complex z) {
//     double u = z.re();
//     double v = z.im();
//     return (u * u + v * v);
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // Jacobi-elliptic-CN by dark-beam, http://dark-beam.deviantart.com/art/Jacobi-elliptic-sn-cn-and-dn-Apoplugins-460783612
// 
//     Complex geo1 = new Complex(0.0, 0.0);
//     Complex phi = new Complex(pAffineTP.x, pAffineTP.y);
//     Complex modul = new Complex(jac_asn_kr, jac_asn_ki);
// 
// 
//     Complex t1 = new Complex(1.0, 0);
// 
//     switch (jac_asn_type) {
//       case 0:
//       case 4: {
//         phi = (phi.plus(asin(modul.times(Complex.sin(phi))))).times(0.5);
//         break;
//       }
//       case 1:
//       case 5: {
//         phi = (asin(phi).plus(asin(modul.times(phi)))).times(0.5);
//         break;
//       }
//       case 2:
//       case 6: {
//         (Complex.acos(phi).plus(asin(modul.times(Complex.sqrt(t1.minus(phi.times(phi))))))).times(0.5);
//         break;
//       }
//       case 3:
//       case 7: {
//         try {
//           phi = Complex.j.times(asinh(phi));
//         } catch (Msg e) {
//           // TODO Auto-generated catch block
//           e.printStackTrace();
//         }
//         phi = phi.plus(asin(modul.times(Complex.sin(phi)))).times(0.5);
//         break;
//       }
//     }
//     if (jac_asn_type > 3) { // SWAP modul & phi
//       geo1 = phi;
//       phi = modul;
//       modul = geo1;
//     }
// 
//     Complex geo = new Complex(pAmount, 0.0);
// 
//     // Method from Norbert Rosch, described in the paper:
//     // The derivation of algorithms to compute
//     // elliptic integrals of the first and second kind
//     // by Landen transformation. (2011)
// 
//     for (int j = 0; j < 10; j++) {
// 
//       if (norm(t1.minus(modul)) < MathLib.SMALL_EPSILON) {
//         break; // enough iters.
//       }
//       if (j > 0)
//         phi = ((phi.plus(asin(modul.times(Complex.sin(phi)))))).times(0.5);
// 
//       try {
//         geo1 = new Complex(2.0, 0).divideBy((t1.plus(modul)));
//       } catch (Msg e) {
//         // TODO Auto-generated catch block
//         e.printStackTrace();
//       }
//       geo = geo.times(geo1);
//       modul = geo1.times(Complex.sqrt(modul));
//     }
// 
//     phi = geo.times(Complex.ln(Complex.tan((phi.times(0.5)).plus(MathLib.M_PI_4))));
// 
//     pVarTP.x += phi.re();
//     pVarTP.y += phi.im();
// 
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{jac_asn_kr, jac_asn_ki, jac_asn_type};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_KR.equalsIgnoreCase(pName))
//       jac_asn_kr = pValue;
//     else if (PARAM_KI.equalsIgnoreCase(pName))
//       jac_asn_ki = pValue;
//     else if (PARAM_TYPE.equalsIgnoreCase(pName))
//       jac_asn_type = (int) limitVal(pValue, 0, 7);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "jac_asn";
//   }
// }
// 
