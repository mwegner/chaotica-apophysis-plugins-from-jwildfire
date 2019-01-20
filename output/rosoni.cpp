#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: rosoni

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/RosoniFunc.java

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
	int maxiter;
	int sweetiter;
	int altshapes;
	double cutoff;
	double radius;
	double dx;
	double dy;
	double _sina;
	double _cosa;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "rosoni_"
#include "plugin.h"

APO_PLUGIN("rosoni");
APO_VARIABLES(
	VAR_INTEGER(maxiter, 25),
	VAR_INTEGER(sweetiter, 3),
	VAR_INTEGER(altshapes, 0),
	VAR_REAL(cutoff, 1.0),
	VAR_REAL(radius, 0.4),
	VAR_REAL(dx, 0.6),
	VAR_REAL(dy, 0.0),

);



int PluginVarPrepare(Variation* vp)
{
    double phi = M_2PI / (double) VAR(maxiter);
    VAR(_sina) = sin(phi);
    VAR(_cosa) = cos(phi);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double x = FTx;
    double y = FTy;
    double r = sqrt(sqr(x) + sqr(y)) - VAR(cutoff);
    if (VAR(cutoff) < 0.0)
      r = MAX(fabs(x), fabs(y)) + VAR(cutoff);
    bool cerc = r > 0.0;

    if (cerc) {
      FPx += VVAR * x;
      FPy += VVAR * y;
      if (true /* pContext\.isPreserveZCoordinate() */) {
        FPz += VVAR * FTz;
      }
      return TRUE;
    }

    cerc = (VAR(dx) > 0.0);
    int i;
    double xrt = x, yrt = y, swp, r2 = xrt;
    double sweetx = xrt, sweety = yrt;

    for (i = 0; i < VAR(maxiter); i++) {
      if (VAR(altshapes) == 0) {
        r2 = sqr(xrt - VAR(dx)) + sqr(yrt - VAR(dy)) - sqr(VAR(radius)); // circle
        if (VAR(radius) < 0.0)
          r2 = MAX(fabs(xrt - VAR(dx)), fabs(y - VAR(dy))) + VAR(radius); // square
      } else {
        r2 = ((xrt - VAR(dx)) < 0.0) ? -(xrt - VAR(dx)) : ((sqr(yrt - VAR(dy))) - sqr(xrt - VAR(dx)) * (sqr(VAR(radius)) - sqr(xrt - VAR(dx)))); // lemniscate
        if (VAR(radius) < 0.0)
          r2 = fabs(atan2(y - VAR(dy), xrt - VAR(dx))) * M_1_PI + VAR(radius); // angle
      }
      cerc ^= (r2 <= 0.0);
      // rotate around to get the the sides!!! :D
      if (i == VAR(sweetiter)) {
        sweetx = xrt;
        sweety = yrt;
      }
      swp = xrt * VAR(_cosa) - yrt * VAR(_sina);
      yrt = xrt * VAR(_sina) + yrt * VAR(_cosa);
      xrt = swp;
    }

    if (cerc) {
      if (VAR(sweetiter) == 0) {
        if (VAR(dy) != 0)
          FPx -= VVAR * sweetx;
        else
          FPx += VVAR * sweetx;
        FPy -= VVAR * sweety;
      } else {
        FPx += VVAR * sweetx;
        FPy += VVAR * sweety;
      }
      if (true /* pContext\.isPreserveZCoordinate() */) {
        FPz += VVAR * FTz;
      }
      return TRUE;
    }
    FPx += VVAR * x;
    FPy += VVAR * y;
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
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// // Rosoni JWildfire variation by DarkBeam, July 2014
// // (for more details, see JWildfire forum post: http://jwildfire.org/forum/viewtopic.php?f=23&t=1449)
// // From dark-beam's post:
// //      In some situations (if you mangle with values a bit and sweetiter is = 0) some pixels will turn black.
// //      It's not a common situation and I think it's ok. It should never happen if you choose a correct sweetiter value.
// //      Commonly sweetiter should be = maxiter / 2. But different ones can be tried.
// //
// // minor changes by CozyG
// public class RosoniFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_MAXITER = "maxiter";
//   private static final String PARAM_SWEETITER = "sweetiter";
//   private static final String PARAM_ALTSHAPES = "altshapes";
//   private static final String PARAM_CUTOFF = "cutoff";
//   private static final String PARAM_RADIUS = "radius";
//   private static final String PARAM_DX = "dx";
//   private static final String PARAM_DY = "dy";
//   private static final String[] paramNames = {PARAM_MAXITER, PARAM_SWEETITER, PARAM_ALTSHAPES, PARAM_CUTOFF, PARAM_RADIUS, PARAM_DX, PARAM_DY};
// 
//   private int maxiter = 25;
//   private int sweetiter = 3;
//   private int altshapes = 0;
//   private double cutoff = 1.0;
//   private double radius = 0.4;
//   private double dx = 0.6;
//   private double dy = 0.0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     double x = pAffineTP.x;
//     double y = pAffineTP.y;
//     double r = sqrt(sqr(x) + sqr(y)) - cutoff;
//     if (cutoff < 0.0)
//       r = Math.max(fabs(x), fabs(y)) + cutoff;
//     boolean cerc = r > 0.0;
// 
//     if (cerc) {
//       pVarTP.x += pAmount * x;
//       pVarTP.y += pAmount * y;
//       if (pContext.isPreserveZCoordinate()) {
//         pVarTP.z += pAmount * pAffineTP.z;
//       }
//       return;
//     }
// 
//     cerc = (dx > 0.0);
//     int i;
//     double xrt = x, yrt = y, swp, r2 = xrt;
//     double sweetx = xrt, sweety = yrt;
// 
//     for (i = 0; i < maxiter; i++) {
//       if (altshapes == 0) {
//         r2 = sqr(xrt - dx) + sqr(yrt - dy) - sqr(radius); // circle
//         if (radius < 0.0)
//           r2 = Math.max(fabs(xrt - dx), fabs(y - dy)) + radius; // square
//       } else {
//         r2 = ((xrt - dx) < 0.0) ? -(xrt - dx) : ((sqr(yrt - dy)) - sqr(xrt - dx) * (sqr(radius) - sqr(xrt - dx))); // lemniscate
//         if (radius < 0.0)
//           r2 = fabs(atan2(y - dy, xrt - dx)) * M_1_PI + radius; // angle
//       }
//       cerc ^= (r2 <= 0.0);
//       // rotate around to get the the sides!!! :D
//       if (i == sweetiter) {
//         sweetx = xrt;
//         sweety = yrt;
//       }
//       swp = xrt * _cosa - yrt * _sina;
//       yrt = xrt * _sina + yrt * _cosa;
//       xrt = swp;
//     }
// 
//     if (cerc) {
//       if (sweetiter == 0) {
//         if (dy != 0)
//           pVarTP.x -= pAmount * sweetx;
//         else
//           pVarTP.x += pAmount * sweetx;
//         pVarTP.y -= pAmount * sweety;
//       } else {
//         pVarTP.x += pAmount * sweetx;
//         pVarTP.y += pAmount * sweety;
//       }
//       if (pContext.isPreserveZCoordinate()) {
//         pVarTP.z += pAmount * pAffineTP.z;
//       }
//       return;
//     }
//     pVarTP.x += pAmount * x;
//     pVarTP.y += pAmount * y;
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
//     }
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{maxiter, sweetiter, altshapes, cutoff, radius, dx, dy};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_MAXITER.equalsIgnoreCase(pName))
//       maxiter = limitIntVal(Tools.FTOI(pValue), 1, 1024);
//     else if (PARAM_SWEETITER.equalsIgnoreCase(pName))
//       sweetiter = limitIntVal(Tools.FTOI(pValue), 0, 1023);
//     else if (PARAM_ALTSHAPES.equalsIgnoreCase(pName))
//       altshapes = Tools.FTOI(pValue);
//     else if (PARAM_CUTOFF.equalsIgnoreCase(pName))
//       cutoff = pValue;
//     else if (PARAM_RADIUS.equalsIgnoreCase(pName))
//       radius = pValue;
//     else if (PARAM_DX.equalsIgnoreCase(pName))
//       dx = pValue;
//     else if (PARAM_DY.equalsIgnoreCase(pName))
//       dy = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "rosoni";
//   }
// 
//   private double _sina, _cosa;
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     double phi = M_2PI / (double) maxiter;
//     _sina = sin(phi);
//     _cosa = cos(phi);
//   }
// 
// }
// 
