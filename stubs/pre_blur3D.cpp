#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: pre_blur3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PreBlur3DFunc.java

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
	double _gauss_rnd[6];
	int _gauss_N;
	double _sina = 0.0;
	double _cosa = 0.0;
	double _sinb = 0.0;
	double _cosb = 0.0;

} Variables;

#define APO_VARIABLE_PREFIX "pre_blur3D_"
#include "plugin.h"

APO_PLUGIN("pre_blur3D");
APO_VARIABLES(

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
// import odk.lang.double;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.M_PI;
// import static org.jwildfire.base.mathlib.MathLib.sinAndCos;
// 
// public class PreBlur3DFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private double gauss_rnd[] = new double[6];
//   private int gauss_N;
// 
//   private double sina = 0.0;
//   private double cosa = 0.0;
//   private double sinb = 0.0;
//   private double cosb = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double angle = pContext.random() * 2 * M_PI;
//     sinAndCos(angle, sina, cosa);
//     double r = pAmount * (gauss_rnd[0] + gauss_rnd[1] + gauss_rnd[2] + gauss_rnd[3] + gauss_rnd[4] + gauss_rnd[5] - 3);
//     gauss_rnd[gauss_N] = pContext.random();
//     gauss_N = (gauss_N + 1) & 5;
//     angle = pContext.random() * M_PI;
//     sinAndCos(angle, sinb, cosb);
//     pAffineTP.x += r * sinb.value * cosa.value;
//     pAffineTP.y += r * sinb.value * sina.value;
//     pAffineTP.z += r * cosb.value;
//   }
// 
//   @Override
//   public String getName() {
//     return "pre_blur3D";
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     gauss_rnd[0] = pContext.random();
//     gauss_rnd[1] = pContext.random();
//     gauss_rnd[2] = pContext.random();
//     gauss_rnd[3] = pContext.random();
//     gauss_rnd[4] = pContext.random();
//     gauss_rnd[5] = pContext.random();
//     gauss_N = 0;
//   }
// 
//   @Override
//   public int getPriority() {
//     return -1;
//   }
// }
// 
