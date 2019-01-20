#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: pre_curl

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PreCurlFunc.java

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
	double c1;
	double c2;
	double _c2x2;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "pre_curl_"
#include "plugin.h"

APO_PLUGIN("pre_curl");
APO_VARIABLES(
	VAR_REAL(c1, 0),
	VAR_REAL(c2, 0),

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_c2x2) = 2.0 * VAR(c2);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // pre_curl by Xyrus02, http://xyrus-02.deviantart.com/art/pre-curl-Plugin-for-Apophysis-451146819 
    double x = FTx;
    double y = FTy;

    double re = 1 + VAR(c1) * x + VAR(c2) * (x * x - y * y);
    double im = VAR(c1) * y + VAR(_c2x2) * x * y;

    double r = VVAR / (re * re + im * im);

    FTx = (x * re + y * im) * r;
    FTy = (y * re - x * im) * r;


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
// public class PreCurlFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_C1 = "c1";
//   private static final String PARAM_C2 = "c2";
//   private static final String[] paramNames = {PARAM_C1, PARAM_C2};
// 
//   private double c1 = 0;
//   private double c2 = 0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // pre_curl by Xyrus02, http://xyrus-02.deviantart.com/art/pre-curl-Plugin-for-Apophysis-451146819 
//     double x = pAffineTP.x;
//     double y = pAffineTP.y;
// 
//     double re = 1 + c1 * x + c2 * (x * x - y * y);
//     double im = c1 * y + c2x2 * x * y;
// 
//     double r = pAmount / (re * re + im * im);
// 
//     pAffineTP.x = (x * re + y * im) * r;
//     pAffineTP.y = (y * re - x * im) * r;
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{c1, c2};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_C1.equalsIgnoreCase(pName))
//       c1 = pValue;
//     else if (PARAM_C2.equalsIgnoreCase(pName))
//       c2 = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "pre_curl";
//   }
// 
//   private double c2x2;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     c2x2 = 2.0 * c2;
//   }
// 
//   @Override
//   public int getPriority() {
//     return -1;
//   }
// 
// }
// 
