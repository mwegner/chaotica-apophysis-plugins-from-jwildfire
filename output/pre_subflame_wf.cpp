#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: pre_subflame_wf

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PreSubFlameWFFunc.java

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

} Variables;

#define APO_VARIABLE_PREFIX "pre_subflame_wf_"
#include "plugin.h"

APO_PLUGIN("pre_subflame_wf");
APO_VARIABLES(


);



int PluginVarPrepare(Variation* vp)
{

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    subflameIter(vp);
    FTx = q.x;
    FTy = q.y;
    FTz = q.z;

    setColor(pAffineTP);


    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// public class PreSubFlameWFFunc extends SubFlameWFFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public int getPriority() {
//     return -1;
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     subflameIter(pContext);
//     pAffineTP.x = q.x;
//     pAffineTP.y = q.y;
//     pAffineTP.z = q.z;
// 
//     setColor(pAffineTP);
//   }
// 
//   @Override
//   public String getName() {
//     return "pre_subflame_wf";
//   }
// 
// }
// 
