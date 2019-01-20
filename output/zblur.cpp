#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: zblur

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ZBlurFunc.java

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

} Variables;

#define APO_VARIABLE_PREFIX "zblur_"
#include "plugin.h"

APO_PLUGIN("zblur");
APO_VARIABLES(


);



int PluginVarPrepare(Variation* vp)
{
    VAR(_gauss_rnd)[0] = GOODRAND_01();
    VAR(_gauss_rnd)[1] = GOODRAND_01();
    VAR(_gauss_rnd)[2] = GOODRAND_01();
    VAR(_gauss_rnd)[3] = GOODRAND_01();
    VAR(_gauss_N) = 0;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    FPz += VVAR * (VAR(_gauss_rnd)[0] + VAR(_gauss_rnd)[1] + VAR(_gauss_rnd)[2] + VAR(_gauss_rnd)[3] - 2);
    VAR(_gauss_rnd)[VAR(_gauss_N)] = GOODRAND_01();
    VAR(_gauss_N) = (VAR(_gauss_N) + 1) & 3;


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
// public class ZBlurFunc extends SimpleVariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private double gauss_rnd[] = new double[4];
//   int gauss_N;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     pVarTP.z += pAmount * (gauss_rnd[0] + gauss_rnd[1] + gauss_rnd[2] + gauss_rnd[3] - 2);
//     gauss_rnd[gauss_N] = pContext.random();
//     gauss_N = (gauss_N + 1) & 3;
//   }
// 
//   @Override
//   public String getName() {
//     return "zblur";
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
