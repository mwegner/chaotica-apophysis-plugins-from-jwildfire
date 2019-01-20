#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: pre_blur

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PreBlurFunc.java

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

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "pre_blur_"
#include "plugin.h"

APO_PLUGIN("pre_blur");
APO_VARIABLES(

);



int PluginVarPrepare(Variation* vp)
{
    VAR(_gauss_rnd)[0] = GOODRAND_01();
    VAR(_gauss_rnd)[1] = GOODRAND_01();
    VAR(_gauss_rnd)[2] = GOODRAND_01();
    VAR(_gauss_rnd)[3] = GOODRAND_01();
    VAR(_gauss_rnd)[4] = GOODRAND_01();
    VAR(_gauss_rnd)[5] = GOODRAND_01();
    VAR(_gauss_N) = 0;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double r = GOODRAND_01() * 2 * M_PI;
    double sina = sin(r);
    double cosa = cos(r);
    r = VVAR * (VAR(_gauss_rnd)[0] + VAR(_gauss_rnd)[1] + VAR(_gauss_rnd)[2] + VAR(_gauss_rnd)[3] + VAR(_gauss_rnd)[4] + VAR(_gauss_rnd)[5] - 3);
    VAR(_gauss_rnd)[VAR(_gauss_N)] = GOODRAND_01();
    VAR(_gauss_N) = (VAR(_gauss_N) + 1) & 5;
    FTx += r * cosa;
    FTy += r * sina;


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
// public class PreBlurFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private final double gauss_rnd[] = new double[6];
//   private int gauss_N;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double r = pContext.random() * 2 * M_PI;
//     double sina = sin(r);
//     double cosa = cos(r);
//     r = pAmount * (gauss_rnd[0] + gauss_rnd[1] + gauss_rnd[2] + gauss_rnd[3] + gauss_rnd[4] + gauss_rnd[5] - 3);
//     gauss_rnd[gauss_N] = pContext.random();
//     gauss_N = (gauss_N + 1) & 5;
//     pAffineTP.x += r * cosa;
//     pAffineTP.y += r * sina;
//   }
// 
//   @Override
//   public String getName() {
//     return "pre_blur";
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
// 
// }
// 
