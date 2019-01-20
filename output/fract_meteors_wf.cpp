#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: fract_meteors_wf

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/FractMeteorsWFFunc.java

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

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "fract_meteors_wf_"
#include "plugin.h"

APO_PLUGIN("fract_meteors_wf");
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
// 
// package org.jwildfire.create.tina.variation;
// 
// import java.util.List;
// 
// public class FractMeteorsWFFunc extends AbstractFractWFFunc {
//   private static final long serialVersionUID = 1L;
// 
//   @Override
//   public String getName() {
//     return "fract_meteors_wf";
//   }
// 
//   @Override
//   protected void initParams() {
//     xmin = -1.7;
//     xmax = 1.7;
//     ymin = -1.1;
//     ymax = 1.1;
//     clip_iter_min = 3;
//     scale = 5.7;
//   }
// 
//   @Override
//   protected boolean setCustomParameter(String pName, double pValue) {
//     return false;
//   }
// 
//   @Override
//   protected void addCustomParameterNames(List<String> pList) {
//     // no op
//   }
// 
//   @Override
//   protected void addCustomParameterValues(List<Object> pList) {
//     // no op
//   }
// 
//   public class MeteorsIterator extends Iterator {
// 
//     @Override
//     protected void nextIteration() {
//       double x1 = this.currX;
//       double y1 = this.currY;
//       this.xs = x1 * x1;
//       this.ys = y1 * y1;
//       double x2 = (this.startX * x1 - this.startY * y1) - (this.startX * x1 + this.startY * y1) / (this.xs + this.ys);
//       y1 = (this.startX * y1 + this.startY * x1) + (this.startX * y1 - this.startY * x1) / (this.xs + this.ys);
//       x1 = x2;
//       setCurrPoint(x1, y1);
//     }
//   }
// 
//   private MeteorsIterator iterator = new MeteorsIterator();
// 
//   @Override
//   protected Iterator getIterator() {
//     return iterator;
//   }
// 
// }
// 
