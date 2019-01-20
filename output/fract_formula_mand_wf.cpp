#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: fract_formula_mand_wf

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/FractFormulaMandWFFunc.java

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
	int power;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "fract_formula_mand_wf_"
#include "plugin.h"

APO_PLUGIN("fract_formula_mand_wf");
APO_VARIABLES(
	VAR_INTEGER(power, 0),

);


void setRessource (Variation* vp, String pName, byte[] pValue) {

    if (RESSOURCE_FORMULA.equalsIgnoreCase(pName)) {
      formula = pValue != null ? new String(pValue) : "";
    } else
      throw new IllegalArgumentException(pName);
}


int PluginVarPrepare(Variation* vp)
{
    prepare_formula(formula);

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
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// 
// import java.util.List;
// 
// public class FractFormulaMandWFFunc extends AbstractFractFormulaWFFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_POWER = "power";
//   private static final String RESSOURCE_FORMULA = "formula";
// 
//   private static final String[] ressourceNames = {RESSOURCE_FORMULA};
// 
//   private int power;
//   private String formula = "((z^n)+c)";
// 
//   @Override
//   public String getName() {
//     return "fract_formula_mand_wf";
//   }
// 
//   @Override
//   protected void initParams() {
//     xmin = -2.35;
//     xmax = 0.75;
//     ymin = -1.2;
//     ymax = 1.2;
//     max_iter = 30;
//     clip_iter_min = 1;
//     scale = 3.8;
//     power = 2;
//   }
// 
//   @Override
//   protected boolean setCustomParameter(String pName, double pValue) {
//     if (PARAM_POWER.equalsIgnoreCase(pName)) {
//       power = Tools.FTOI(pValue);
//       if (power < 2)
//         power = 2;
//       return true;
//     }
//     return false;
//   }
// 
//   @Override
//   protected void addCustomParameterNames(List<String> pList) {
//     pList.add(PARAM_POWER);
//   }
// 
//   @Override
//   protected void addCustomParameterValues(List<Object> pList) {
//     pList.add(power);
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     super.init(pContext, pLayer, pXForm, pAmount);
//     prepare_formula(formula);
//   }
// 
//   public class FormulaMandIterator extends Iterator {
//     private static final long serialVersionUID = 1L;
// 
//     @Override
//     protected void nextIteration() {
//       double x1 = this.currX;
//       double y1 = this.currY;
//       this.xs = x1 * x1;
//       this.ys = y1 * y1;
//       Complex z = perform_formula(power, x1, y1, this.startX, this.startY);
//       x1 = z.re;
//       y1 = z.im;
//       setCurrPoint(x1, y1);
//     }
// 
//   }
// 
//   private FormulaMandIterator iterator = new FormulaMandIterator();
// 
//   @Override
//   protected Iterator getIterator() {
//     return iterator;
//   }
// 
//   @Override
//   public String[] getRessourceNames() {
//     return ressourceNames;
//   }
// 
//   @Override
//   public byte[][] getRessourceValues() {
//     return new byte[][]{(formula != null ? formula.getBytes() : null)};
//   }
// 
//   @Override
//   public void setRessource(String pName, byte[] pValue) {
//     if (RESSOURCE_FORMULA.equalsIgnoreCase(pName)) {
//       formula = pValue != null ? new String(pValue) : "";
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public RessourceType getRessourceType(String pName) {
//     if (RESSOURCE_FORMULA.equalsIgnoreCase(pName)) {
//       return RessourceType.BYTEARRAY;
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// 
// }
// 
