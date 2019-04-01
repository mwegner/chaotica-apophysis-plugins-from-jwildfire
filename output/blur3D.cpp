#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: blur3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Blur3DFunc.java

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
	double _gauss_rnd[4];
	int _gauss_N;
	double _sina = 0.0;
	double _cosa = 0.0;
	double _sinb = 0.0;
	double _cosb = 0.0;

} Variables;

#define APO_VARIABLE_PREFIX "blur3D_"
#include "plugin.h"

APO_PLUGIN("blur3D");
APO_VARIABLES(


);



int PluginVarPrepare(Variation* vp)
{
   VAR(_sina) = 0.0;
   VAR(_cosa) = 0.0;
   VAR(_sinb) = 0.0;
   VAR(_cosb) = 0.0;
    VAR(_gauss_rnd)[0] = GOODRAND_01();
    VAR(_gauss_rnd)[1] = GOODRAND_01();
    VAR(_gauss_rnd)[2] = GOODRAND_01();
    VAR(_gauss_rnd)[3] = GOODRAND_01();
    VAR(_gauss_N) = 0;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double angle = GOODRAND_01() * 2 * M_PI;
    fsincos(angle, &VAR(_sina), &VAR(_cosa));
    double r = VVAR * (VAR(_gauss_rnd)[0] + VAR(_gauss_rnd)[1] + VAR(_gauss_rnd)[2] + VAR(_gauss_rnd)[3] - 2);
    VAR(_gauss_rnd)[VAR(_gauss_N)] = GOODRAND_01();
    VAR(_gauss_N) = (VAR(_gauss_N) + 1) & 3;
    angle = GOODRAND_01() * M_PI;
    fsincos(angle, &VAR(_sinb), &VAR(_cosb));
    FPx += r * VAR(_sinb) * VAR(_cosa);
    FPy += r * VAR(_sinb) * VAR(_sina);
    FPz += r * VAR(_cosb);


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
// import org.jwildfire.base.mathlib.double;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.M_PI;
// import static org.jwildfire.base.mathlib.MathLib.sinAndCos;
// 
// public class Blur3DFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private double gauss_rnd[] = new double[4];
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
//     double r = pAmount * (gauss_rnd[0] + gauss_rnd[1] + gauss_rnd[2] + gauss_rnd[3] - 2);
//     gauss_rnd[gauss_N] = pContext.random();
//     gauss_N = (gauss_N + 1) & 3;
//     angle = pContext.random() * M_PI;
//     sinAndCos(angle, sinb, cosb);
//     pVarTP.x += r * sinb.value * cosa.value;
//     pVarTP.y += r * sinb.value * sina.value;
//     pVarTP.z += r * cosb.value;
//   }
// 
//   @Override
//   public String getName() {
//     return "blur3D";
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     gauss_rnd[0] = pContext.random();
//     gauss_rnd[1] = pContext.random();
//     gauss_rnd[2] = pContext.random();
//     gauss_rnd[3] = pContext.random();
//     gauss_N = 0;
//   }
// 
// }
// 
