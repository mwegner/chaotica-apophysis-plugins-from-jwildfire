/*
    Apophysis Plugin: target

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/TargetFunc.java

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
	double even; // -M_PI + random01() + M_2PI
	double odd; // -M_PI + random01() + M_2PI
	double size; // 0.5 + random01() * 0.75
	double _t_size_2;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "target_"
#include "plugin.h"

APO_PLUGIN("target");
APO_VARIABLES(
	VAR_REAL(even, 0),
	VAR_REAL(odd, 0),
	VAR_REAL(size, 0),

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
// public class TargetFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_EVEN = "even";
//   private static final String PARAM_ODD = "odd";
//   private static final String PARAM_SIZE = "size";
//   private static final String[] paramNames = {PARAM_EVEN, PARAM_ODD, PARAM_SIZE};
// 
//   private double even = -M_PI + Math.random() + M_2PI;
//   private double odd = -M_PI + Math.random() + M_2PI;
//   private double size = 0.5 + Math.random() * 0.75;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* target by Michael Faber, http://michaelfaber.deviantart.com/art/Target-362520023?q=gallery%3Afractal-resources%2F24660058&qo=0 */
//     double a = atan2(pAffineTP.y, pAffineTP.x);
//     double r = sqrt(sqr(pAffineTP.x) + sqr(pAffineTP.y));
//     double t = log(r);
//     if (t < 0.0)
//       t -= t_size_2;
// 
//     t = fmod(fabs(t), size);
// 
//     if (t < t_size_2)
//       a += even;
//     else
//       a += odd;
// 
//     double s = sin(a);
//     double c = cos(a);
// 
//     pVarTP.x += r * c;
//     pVarTP.y += r * s;
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
//     return new Object[]{even, odd, size};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_EVEN.equalsIgnoreCase(pName))
//       even = pValue;
//     else if (PARAM_ODD.equalsIgnoreCase(pName))
//       odd = pValue;
//     else if (PARAM_SIZE.equalsIgnoreCase(pName))
//       size = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "target";
//   }
// 
//   private double t_size_2;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     t_size_2 = 0.5 * size;
//   }
// 
// }
// 
