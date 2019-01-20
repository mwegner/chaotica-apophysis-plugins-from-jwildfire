#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: helicoid

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/HelicoidFunc.java

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
	double frequency;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "helicoid_"
#include "plugin.h"

APO_PLUGIN("helicoid");
APO_VARIABLES(
	VAR_REAL(frequency, 1.0),

);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* helicoid by zy0rg, http://zy0rg.deviantart.com/art/Helix-Helicoid-687956099 converted by Brad Stefanov */
    double range = sqrt(FTx * FTx + FTy * FTy);
    double s = sin(FTz * M_2PI * VAR(frequency) + atan2(FTy, FTx));
    double c = cos(FTz * M_2PI * VAR(frequency) + atan2(FTy, FTx));


    FPx += VVAR * c * range;
    FPy += VVAR * s * range;
    FPz += VVAR * FTz;


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
// public class HelicoidFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
//   private static final String PARAM_FREQUENCY = "frequency";
// 
//   private static final String[] paramNames = {PARAM_FREQUENCY};
// 
//   private double frequency = 1.0;
// 
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* helicoid by zy0rg, http://zy0rg.deviantart.com/art/Helix-Helicoid-687956099 converted by Brad Stefanov */
//     double range = sqrt(pAffineTP.x * pAffineTP.x + pAffineTP.y * pAffineTP.y);
//     double s = sin(pAffineTP.z * M_2PI * frequency + atan2(pAffineTP.y, pAffineTP.x));
//     double c = cos(pAffineTP.z * M_2PI * frequency + atan2(pAffineTP.y, pAffineTP.x));
// 
// 
//     pVarTP.x += pAmount * c * range;
//     pVarTP.y += pAmount * s * range;
//     pVarTP.z += pAmount * pAffineTP.z;
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{frequency};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_FREQUENCY.equalsIgnoreCase(pName))
//       frequency = pValue;
// 
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "helicoid";
//   }
// 
// }
// 
