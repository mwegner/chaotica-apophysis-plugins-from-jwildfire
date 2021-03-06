#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: post_heat

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PostHeatFunc.java

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
	double _theta_period = 0.0;
	double _theta_phase = 0.0;
	double _theta_amp = 0.0;
	double _phi_period = 0.0;
	double _phi_phase = 0.0;
	double _phi_amp = 0.0;
	double _r_period = 0.0;
	double _r_phase = 0.0;
	double _r_amp = 0.0;
	double _at;
	double _bt;
	double _ct;
	double _ap;
	double _bp;
	double _cp;
	double _ar;
	double _br;
	double _cr;

} Variables;

#define APO_VARIABLE_PREFIX "post_heat_"
#include "plugin.h"

APO_PLUGIN("post_heat");
APO_VARIABLES(


);



int PluginVarPrepare(Variation* vp)
{
   VAR(_theta_period) = 0.0;
   VAR(_theta_phase) = 0.0;
   VAR(_theta_amp) = 0.0;
   VAR(_phi_period) = 0.0;
   VAR(_phi_phase) = 0.0;
   VAR(_phi_amp) = 0.0;
   VAR(_r_period) = 0.0;
   VAR(_r_phase) = 0.0;
   VAR(_r_amp) = 0.0;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double tx = VAR(_theta_period) == 0 ? 0.0 : 1.0 / VAR(_theta_period);
    double px = VAR(_phi_period) == 0 ? 0.0 : 1.0 / VAR(_phi_period);
    double rx = VAR(_r_period) == 0 ? 0.0 : 1.0 / VAR(_r_period);

    VAR(_at) = VVAR * VAR(_theta_amp);
    VAR(_bt) = M_2PI * tx;
    VAR(_ct) = VAR(_theta_phase) * tx;
    VAR(_ap) = VVAR * VAR(_phi_amp);
    VAR(_bp) = M_2PI * px;
    VAR(_cp) = VAR(_phi_phase) * px;
    VAR(_ar) = VVAR * VAR(_r_amp);
    VAR(_br) = M_2PI * rx;
    VAR(_cr) = VAR(_r_phase) * rx;

    double r = sqrt(sqr(FPx) + sqr(FPy) + sqr(FPz));

    double sint, cost, sinp, cosp, atant, acosp;

    atant = atan2(FPy, FPx);

    r += VAR(_ar) * sin(VAR(_br) * r + VAR(_cr));

    sint = VAR(_at) * sin(VAR(_bt) * r + VAR(_ct)) + atant;
    cost = cos(sint);
    sint = sin(sint);

    if (r != 0) {
      acosp = FPz / r;
    } else {
      acosp = 0; //FPz >= 0? 10000 : -10000;
    }

    sinp = VAR(_ap) * sin(VAR(_bp) * r + VAR(_cp)) + acos(acosp);
    cosp = cos(sinp);
    sinp = sin(sinp);

    FPx = r * cost * sinp;
    FPy = r * sint * sinp;
    FPz = r * cosp;


    return TRUE;
}





// original java file embedded here:
//
// package org.jwildfire.create.tina.variation;
// 
// /*
// JWildfire - an image and animation processor written in Java
// Copyright (C) 1995-2011 Andreas Maschke
// 
// This is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser
// General Public License as published by the Free Software Foundation; either version 2.1 of the
// License, or (at your option) any later version.
// 
// This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
// even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License along with this software;
// if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
// 02110-1301 USA, or see the FSF site: http://www.fsf.org.
// */
// 
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// /**
//  * @author Branden Brown, a.k.a. zephyrtronium, transcribed by Nic Anderson, chronologicaldot
//  * @date July 19, 2014 (transcribe)
//  */
// public class PostHeatFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_THETA_PERIOD = "theta_period";
//   private static final String PARAM_THETA_PHASE = "theta_phase";
//   private static final String PARAM_THETA_AMPLITUDE = "theta_amp";
//   private static final String PARAM_PHI_PERIOD = "phi_period";
//   private static final String PARAM_PHI_PHASE = "phi_phase";
//   private static final String PARAM_PHI_AMPLITUDE = "phi_amp";
//   private static final String PARAM_R_PERIOD = "r_period";
//   private static final String PARAM_R_PHASE = "r_phase";
//   private static final String PARAM_R_AMPLITUDE = "r_amp";
// 
//   private static final String[] paramNames = {PARAM_THETA_PERIOD, PARAM_THETA_PHASE, PARAM_THETA_AMPLITUDE, PARAM_PHI_PERIOD, PARAM_PHI_PHASE, PARAM_PHI_AMPLITUDE, PARAM_R_PERIOD, PARAM_R_PHASE, PARAM_R_AMPLITUDE};
// 
//   double theta_period = 0.0;
//   double theta_phase = 0.0;
//   double theta_amp = 0.0;
//   double phi_period = 0.0;
//   double phi_phase = 0.0;
//   double phi_amp = 0.0;
//   double r_period = 0.0;
//   double r_phase = 0.0;
//   double r_amp = 0.0;
// 
//   double at, bt, ct, ap, bp, cp, ar, br, cr;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double tx = theta_period == 0 ? 0.0 : 1.0 / theta_period;
//     double px = phi_period == 0 ? 0.0 : 1.0 / phi_period;
//     double rx = r_period == 0 ? 0.0 : 1.0 / r_period;
// 
//     at = pAmount * theta_amp;
//     bt = M_2PI * tx;
//     ct = theta_phase * tx;
//     ap = pAmount * phi_amp;
//     bp = M_2PI * px;
//     cp = phi_phase * px;
//     ar = pAmount * r_amp;
//     br = M_2PI * rx;
//     cr = r_phase * rx;
// 
//     double r = sqrt(sqr(pVarTP.x) + sqr(pVarTP.y) + sqr(pVarTP.z));
// 
//     double sint, cost, sinp, cosp, atant, acosp;
// 
//     atant = atan2(pVarTP.y, pVarTP.x);
// 
//     r += ar * sin(br * r + cr);
// 
//     sint = at * sin(bt * r + ct) + atant;
//     cost = cos(sint);
//     sint = sin(sint);
// 
//     if (r != 0) {
//       acosp = pVarTP.z / r;
//     } else {
//       acosp = 0; //pVarTP.z >= 0? 10000 : -10000;
//     }
// 
//     sinp = ap * sin(bp * r + cp) + acos(acosp);
//     cosp = cos(sinp);
//     sinp = sin(sinp);
// 
//     pVarTP.x = r * cost * sinp;
//     pVarTP.y = r * sint * sinp;
//     pVarTP.z = r * cosp;
//   }
// 
//   @Override
//   public String getName() {
//     return "post_heat";
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{
//             theta_period, theta_phase, theta_amp,
//             phi_period, phi_phase, phi_amp,
//             r_period, r_phase, r_amp};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_THETA_PERIOD)) {
//       theta_period = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_THETA_PHASE)) {
//       theta_phase = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_THETA_AMPLITUDE)) {
//       theta_amp = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_PHI_PERIOD)) {
//       phi_period = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_PHI_PHASE)) {
//       phi_phase = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_PHI_AMPLITUDE)) {
//       phi_amp = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_R_PERIOD)) {
//       r_period = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_R_PHASE)) {
//       r_phase = pValue;
//     } else if (pName.equalsIgnoreCase(PARAM_R_AMPLITUDE)) {
//       r_amp = pValue;
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public int getPriority() {
//     return 1;
//   }
// }
