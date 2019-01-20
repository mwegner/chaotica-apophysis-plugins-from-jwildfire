#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: layered_spiral

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/LayeredSpiralFunc.java

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

} Variables;

#define APO_VARIABLE_PREFIX "layered_spiral_"
#include "plugin.h"

APO_PLUGIN("layered_spiral");
APO_VARIABLES(
	VAR_REAL(radius, 1.0)

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* layered_spiral by Will Evans, http://eevans1.deviantart.com/art/kaleidoscope-plugin-122185469  */
    double a = FTx * VAR(radius); // adjusts the layered_spiral VAR(radius).
    double t = sqr(FTx) + sqr(FTy) + EPSILON;
    FPx += VVAR * a * cos(t);
    FPy += VVAR * a * sin(t);

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
// public class LayeredSpiralFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_RADIUS = "radius";
// 
//   private static final String[] paramNames = {PARAM_RADIUS};
// 
//   private double radius = 1.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* layered_spiral by Will Evans, http://eevans1.deviantart.com/art/kaleidoscope-plugin-122185469  */
//     double a = pAffineTP.x * this.radius; // adjusts the layered_spiral radius.
//     double t = sqr(pAffineTP.x) + sqr(pAffineTP.y) + EPSILON;
//     pVarTP.x += pAmount * a * cos(t);
//     pVarTP.y += pAmount * a * sin(t);
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
//     return new Object[]{radius};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_RADIUS.equalsIgnoreCase(pName))
//       radius = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "layered_spiral";
//   }
// 
// }
// 
