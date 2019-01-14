/*
    Apophysis Plugin: arch

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ArchFunc.java

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
	double _sinr = 0.0;
	double _cosr = 0.0;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "arch_"
#include "plugin.h"

APO_PLUGIN("arch");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
   VAR(_sinr) = 0.0;
   VAR(_cosr) = 0.0;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double ang = GOODRAND_01() * VVAR * M_PI;
    fsincos(ang, &VAR(_sinr), &VAR(_cosr));
    if (VAR(_cosr) == 0) {
      return TRUE;
    }
    FPx += VVAR * VAR(_sinr);
    FPy += VVAR * (VAR(_sinr) * VAR(_sinr)) / VAR(_cosr);
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
// import odk.lang.double;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.M_PI;
// import static org.jwildfire.base.mathlib.MathLib.sinAndCos;
// 
// public class ArchFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private double sinr = 0.0;
//   private double cosr = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double ang = pContext.random() * pAmount * M_PI;
//     sinAndCos(ang, sinr, cosr);
//     if (cosr.value == 0) {
//       return;
//     }
//     pVarTP.x += pAmount * sinr.value;
//     pVarTP.y += pAmount * (sinr.value * sinr.value) / cosr.value;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String getName() {
//     return "arch";
//   }
// 
// }
// 
