#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: minkowskope

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/MinkowskopeFunc.java

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
	double frequencyx;
	double frequencyy;
	double amplitude;
	double perturbation;
	double damping;
	double _tpf;
	double _tpf2;
	bool _noDamping;
	bool _altWave;

} Variables;

#define APO_VARIABLE_PREFIX "minkowskope_"
#include "plugin.h"

APO_PLUGIN("minkowskope");
APO_VARIABLES(
	VAR_REAL(separation, 0.5),
	VAR_REAL(frequencyx, -2.0),
	VAR_REAL(frequencyy, 2.0),
	VAR_REAL(amplitude, 0.5),
	VAR_REAL(perturbation, 1.0),
	VAR_REAL(damping, 0.0),

);


double minkowski (Variation* vp, double x) {

    /* double p=(long)x;
    if (p>x) p = p - 1.0; */
    double p = 0.0; // d'oh
    double q = 1.0, r = p + 1.0, s = 1.0, m = 0.0, n = 0.0;
    double d = 1.0, y = p;
    for (int it = 0; it < 20; it++) // precision 1e-6
    {
        d = d * 0.5; //if (d<1e-10) break;
        m = p + r;
        n = q + s;
        if (x < (m / n)) {
            r = m;
            s = n;
        } else {
            y += d;
            p = m;
            q = n;
        }
    }
    return y + d;
}

double minkosine (Variation* vp, double x) {

    double lp = fmod(fabs(x), 4.0);
    double p = fmod(fabs(x), 2.0);
    double mink = 0;
    if (p > 1.0) p = 2.0 - p; // sawtooth wave
    if (VAR(_altWave))
      mink = minkowski(vp, p) - p; // cool looking (uses a different waveform)
    else
      mink = minkowski(vp, p); // normal :P
    if ((lp < 2.0) ^ (x > 0)) return mink; // lol!!! xor
    else return -mink;
}

double minkocosine (Variation* vp, double x) {

    return minkosine(vp, x - 1.0);
}


int PluginVarPrepare(Variation* vp)
{
    VAR(_tpf) = 0.5 * VAR(frequencyx);
    VAR(_tpf2) = 0.5 * VAR(frequencyy);
    VAR(_noDamping) = fabs(VAR(damping)) <= EPSILON;
    VAR(_altWave) = VAR(frequencyx) <= 0.0;


    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* oscilloscope from the apophysis plugin pack tweak darkbeam 2017
    using Minkowski's Question Mark, periodicized function using modulus */
    double t;
    double pt = VAR(perturbation) * minkosine(vp, VAR(_tpf2) * FTy);
    if (VAR(_noDamping)) {
      t = VAR(amplitude) * (minkocosine(vp, VAR(_tpf) * FTx + pt)) + VAR(separation);
    } else {
      t = VAR(amplitude) * exp(-fabs(FTx) * VAR(damping)) * (minkocosine(vp, VAR(_tpf) * FTx + pt)) + VAR(separation);
    }

    if (fabs(FTy) <= t) {
      FPx -= VVAR * FTx;
      FPy -= VVAR * FTy;
    } else {
      FPx += VVAR * FTx;
      FPy += VVAR * FTy;
    }
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
//   This is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser 
//   General Public License as published by the Free Software Foundation; either version 2.1 of the 
//   License, or (at your option) any later version.
//  
//   This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
//   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
//   Lesser General Public License for more details.
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
// public class MinkowskopeFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
//   private static final String PARAM_SEPARATION = "separation";
//   private static final String PARAM_FREQUENCYX = "frequencyx";
//   private static final String PARAM_FREQUENCYY = "frequencyy";
//   private static final String PARAM_AMPLITUDE = "amplitude";
//   private static final String PARAM_PTB = "perturbation";
//   private static final String PARAM_DAMPING = "damping";
// 
//   private static final String[] paramNames = {PARAM_SEPARATION, PARAM_FREQUENCYX, PARAM_FREQUENCYY, PARAM_AMPLITUDE, PARAM_PTB, PARAM_DAMPING};
// 
//   private double separation = 0.5d;
//   private double frequencyx = -2.d;
//   private double frequencyy = 2.d;
//   private double amplitude = 0.5d;
//   private double perturbation = 1.0d;
//   private double damping = 0.0d;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* oscilloscope from the apophysis plugin pack tweak darkbeam 2017
//     using Minkowski's Question Mark, periodicized function using modulus */
//     double t;
//     double pt = perturbation * minkosine(_tpf2 * pAffineTP.y);
//     if (_noDamping) {
//       t = amplitude * (minkocosine(_tpf * pAffineTP.x + pt)) + separation;
//     } else {
//       t = amplitude * exp(-fabs(pAffineTP.x) * damping) * (minkocosine(_tpf * pAffineTP.x + pt)) + separation;
//     }
// 
//     if (fabs(pAffineTP.y) <= t) {
//       pVarTP.x -= pAmount * pAffineTP.x;
//       pVarTP.y -= pAmount * pAffineTP.y;
//     } else {
//       pVarTP.x += pAmount * pAffineTP.x;
//       pVarTP.y += pAmount * pAffineTP.y;
//     }
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   private double minkosine(double x) {
//     double lp = fabs(x) % 4.d;
//     double p = fabs(x) % 2.d;
//     double mink = 0;
//     if (p > 1.d) p = 2.d - p; // sawtooth wave
//     if (_altWave)
//       mink = minkowski(p) - p; // cool looking (uses a different waveform)
//     else
//       mink = minkowski(p); // normal :P
//     if ((lp < 2.d) ^ (x > 0)) return mink; // lol!!! xor
//     else return -mink;
//   }
// 
//   private double minkocosine(double x) {
//     return minkosine(x - 1.d);
//   }
// 
//   /* Minkowski's question mark function from Wikipedia, adapted
//   DO NOT! call it directly it is ... weird, use minkosine or minkocosine thanks!
//    */
//   private double minkowski(double x) {
//     /* double p=(long)x;
//     if (p>x) p = p - 1.; */
//     double p = 0.d; // d'oh
//     double q = 1.d, r = p + 1., s = 1.d, m = 0.d, n = 0.d;
//     double d = 1.d, y = p;
//     for (int it = 0; it < 20; it++) // precision 1e-6
//     {
//       d = d * 0.5d; //if (d<1e-10) break;
//       m = p + r;
//       n = q + s;
//       if (x < (m / n)) {
//         r = m;
//         s = n;
//       } else {
//         y += d;
//         p = m;
//         q = n;
//       }
//     }
//     return y + d;
//   }
// 
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{separation, frequencyx, frequencyy, amplitude, perturbation, damping};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_SEPARATION.equalsIgnoreCase(pName))
//       separation = pValue;
//     else if (PARAM_FREQUENCYX.equalsIgnoreCase(pName))
//       frequencyx = pValue;
//     else if (PARAM_FREQUENCYY.equalsIgnoreCase(pName))
//       frequencyy = pValue;
//     else if (PARAM_AMPLITUDE.equalsIgnoreCase(pName))
//       amplitude = pValue;
//     else if (PARAM_PTB.equalsIgnoreCase(pName))
//       perturbation = pValue;
//     else if (PARAM_DAMPING.equalsIgnoreCase(pName))
//       damping = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "minkowskope";
//   }
// 
//   private double _tpf;
//   private double _tpf2;
//   private boolean _noDamping;
//   private boolean _altWave;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _tpf = 0.5d * frequencyx;
//     _tpf2 = 0.5d * frequencyy;
//     _noDamping = fabs(damping) <= EPSILON;
//     _altWave = frequencyx <= 0.0d;
//   }
// 
//   @Override
//   public String[] getParameterAlternativeNames() {
//     return new String[]{"mskope_separation", "mskope_frequencyx", "mskope_frequencyy", "mskope_amplitude", "mskope_perturbation", "mskope_damping"};
//   }
// 
// }
// 
// 
