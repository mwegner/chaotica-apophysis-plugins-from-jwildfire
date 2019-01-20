#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: oscilloscope

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/OscilloscopeFunc.java

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
	double separation;
	double frequency; // M_PI
	double amplitude;
	double damping;
	double _tpf;
	bool _noDamping;

} Variables;

#define APO_VARIABLE_PREFIX "oscilloscope_"
#include "plugin.h"

APO_PLUGIN("oscilloscope");
APO_VARIABLES(
	VAR_REAL(separation, 1.00),
	VAR_REAL(frequency, M_PI),
	VAR_REAL(amplitude, 1.0),
	VAR_REAL(damping, 0.0),

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
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class OscilloscopeFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_SEPARATION = "separation";
//   private static final String PARAM_FREQUENCY = "frequency";
//   private static final String PARAM_AMPLITUDE = "amplitude";
//   private static final String PARAM_DAMPING = "damping";
// 
//   private static final String[] paramNames = {PARAM_SEPARATION, PARAM_FREQUENCY, PARAM_AMPLITUDE, PARAM_DAMPING};
// 
//   private double separation = 1.00;
//   private double frequency = M_PI;
//   private double amplitude = 1.0;
//   private double damping = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* oscilloscope from the apophysis plugin pack */
//     double t;
//     if (_noDamping) {
//       t = amplitude * cos(_tpf * pAffineTP.x) + separation;
//     } else {
//       t = amplitude * exp(-fabs(pAffineTP.x) * damping) * cos(_tpf * pAffineTP.x) + separation;
//     }
// 
//     if (fabs(pAffineTP.y) <= t) {
//       pVarTP.x += pAmount * pAffineTP.x;
//       pVarTP.y -= pAmount * pAffineTP.y;
//     } else {
//       pVarTP.x += pAmount * pAffineTP.x;
//       pVarTP.y += pAmount * pAffineTP.y;
//     }
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
// 
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{separation, frequency, amplitude, damping};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_SEPARATION.equalsIgnoreCase(pName))
//       separation = pValue;
//     else if (PARAM_FREQUENCY.equalsIgnoreCase(pName))
//       frequency = pValue;
//     else if (PARAM_AMPLITUDE.equalsIgnoreCase(pName))
//       amplitude = pValue;
//     else if (PARAM_DAMPING.equalsIgnoreCase(pName))
//       damping = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String[] getParameterAlternativeNames() {
//     return new String[]{"oscope_separation", "oscope_frequency", "oscope_amplitude", "oscope_damping"};
//   }
// 
//   @Override
//   public String getName() {
//     return "oscilloscope";
//   }
// 
//   private double _tpf;
//   private boolean _noDamping;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _tpf = 2.0f * M_PI * frequency;
//     _noDamping = fabs(damping) <= EPSILON;
//   }
// 
// }
// 
