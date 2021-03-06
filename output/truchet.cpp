#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: truchet

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/TruchetFunc.java

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
	int extended;
	double exponent;
	double arc_width;
	double rotation;
	double size;
	double seed;
	int direct_color;

} Variables;

#define APO_VARIABLE_PREFIX "truchet_"
#include "plugin.h"

APO_PLUGIN("truchet");
APO_VARIABLES(
	VAR_INTEGER(extended, 0),
	VAR_REAL(exponent, 2.0),
	VAR_REAL(arc_width, 0.5),
	VAR_REAL(rotation, 0.0),
	VAR_REAL(size, 1.0),
	VAR_REAL(seed, 50.0),
	VAR_INTEGER(direct_color, 0)

);



int PluginVarPrepare(Variation* vp)
{
    if (VAR(extended) < 0) {
      VAR(extended) = 0;
    } else if (VAR(extended) > 1) {
      VAR(extended) = 1;
    }
    if (VAR(exponent) < 0.001) {
      VAR(exponent) = 0.001;
    } else if (VAR(exponent) > 2.0) {
      VAR(exponent) = 2.0;
    }
    if (VAR(arc_width) < 0.001) {
      VAR(arc_width) = 0.001;
    } else if (VAR(arc_width) > 1.0) {
      VAR(arc_width) = 1.0;
    }
    if (VAR(size) < 0.001) {
      VAR(size) = 0.001;
    } else if (VAR(size) > 10.0) {
      VAR(size) = 10.0;
    }

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    //APO VARIABLES
    double n = VAR(exponent);
    double onen = 1.0 / VAR(exponent);
    double tdeg = VAR(rotation);
    double width = VAR(arc_width);
    double VAR(seed) = fabs(VAR(seed));
    double seed2 = sqrt(VAR(seed) + (VAR(seed) / 2) + SMALL_EPSILON) / ((VAR(seed) * 0.5) + SMALL_EPSILON) * 0.25;
    //VARIABLES   
    double x, y;
    int intx = 0;
    int inty = 0;
    double r = -tdeg;
    double r0 = 0.0;
    double r1 = 0.0;
    double rmax = 0.5 * (pow(2.0, 1.0 / n) - 1.0) * width;
    double scale = (cos(r) - sin(r)) / VVAR;
    double tiletype = 0.0;
    double randint = 0.0;
    double modbase = 65535.0;
    double multiplier = 32747.0;//1103515245;
    double offset = 12345.0;
    double niter = 0.0;
    int randiter = 0;
    //INITIALISATION   
    x = FTx * scale;
    y = FTy * scale;
    intx = (int) round(x);
    inty = (int) round(y);

    r = x - intx;
    if (r < 0.0) {
      x = 1.0 + r;
    } else {
      x = r;
    }

    r = y - inty;
    if (r < 0.0) {
      y = 1.0 + r;
    } else {
      y = r;
    }
    //CALCULATE THE TILE TYPE
    if (VAR(seed) == 0.0) {
      tiletype = 0.0;
    } else if (VAR(seed) == 1.0) {
      tiletype = 1.0;
    } else {
      if (VAR(extended) == 0) {
        double xrand = round(FTx);
        double yrand = round(FTy);
        xrand = xrand * seed2;
        yrand = yrand * seed2;
        niter = xrand + yrand + xrand * yrand;
        randint = (niter + VAR(seed)) * seed2 / 2.0;
        randint = fmod((randint * multiplier + offset), modbase);
      } else {
        VAR(seed) = floor(VAR(seed));
        int xrand = (int) round(FTx);
        int yrand = (int) round(FTy);
        niter = fabs(xrand + yrand + xrand * yrand);
        if (niter > 1000)
          niter = 1000;
        randint = VAR(seed) + niter;
        randiter = 0;
        while (randiter < niter) {
          randiter += 1;
          randint = fmod((randint * multiplier + offset), modbase);
        }
      }
      tiletype = fmod(randint, 2.0);//randint%2;
    }
    //DRAWING THE POINTS
    if (VAR(extended) == 0) { //Fast drawmode
      if (tiletype < 1.0) {
        r0 = pow((pow(fabs(x), n) + pow(fabs(y), n)), onen);
        r1 = pow((pow(fabs(x - 1.0), n) + pow(fabs(y - 1.0), n)), onen);
      } else {
        r0 = pow((pow(fabs(x - 1.0), n) + pow(fabs(y), n)), onen);
        r1 = pow((pow(fabs(x), n) + pow(fabs(y - 1.0), n)), onen);
      }
    } else {
      if (tiletype == 1.0) { //Slow drawmode 
        r0 = pow((pow(fabs(x), n) + pow(fabs(y), n)), onen);
        r1 = pow((pow(fabs(x - 1.0), n) + pow(fabs(y - 1.0), n)), onen);
      } else {
        r0 = pow((pow(fabs(x - 1.0), n) + pow(fabs(y), n)), onen);
        r1 = pow((pow(fabs(x), n) + pow(fabs(y - 1.0), n)), onen);
      }
    }

    r = fabs(r0 - 0.5) / rmax;
    if (r < 1.0) {
      if (VAR(direct_color) == 1) {
        TC = limitVal(r0, 0.0, 1.0);
      }
      FPx += VAR(size) * (x + floor(FTx));
      FPy += VAR(size) * (y + floor(FTy));
    }

    r = fabs(r1 - 0.5) / rmax;
    if (r < 1.0) {
      if (VAR(direct_color) == 1) {
        TC = limitVal(1.0 - r1, 0.0, 1.0);
      }
      FPx += VAR(size) * (x + floor(FTx));
      FPy += VAR(size) * (y + floor(FTy));
      if (true /* pContext\.isPreserveZCoordinate() */) {
        FPz += VVAR * FTz;
      }
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
// 
// /*
//  * Truchet Plugin by TyrantWave, see http://tyrantwave.deviantart.com/art/Truchet-Plugin-107982844
//  */
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class TruchetFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_EXTENDED = "extended";
//   private static final String PARAM_EXPONENT = "exponent";
//   private static final String PARAM_ARC_WIDTH = "arc_width";
//   private static final String PARAM_ROTATION = "rotation";
//   private static final String PARAM_SIZE = "size";
//   private static final String PARAM_SEED = "seed";
//   private static final String PARAM_DIRECT_COLOR = "direct_color";
// 
//   private static final String[] paramNames = {PARAM_EXTENDED, PARAM_EXPONENT, PARAM_ARC_WIDTH, PARAM_ROTATION, PARAM_SIZE, PARAM_SEED, PARAM_DIRECT_COLOR};
// 
//   private int extended = 0;
//   private double exponent = 2.0;
//   private double arc_width = 0.5;
//   private double rotation = 0.0;
//   private double size = 1.0;
//   private double seed = 50.0;
//   private int direct_color = 0;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     //APO VARIABLES
//     double n = exponent;
//     double onen = 1.0 / exponent;
//     double tdeg = rotation;
//     double width = arc_width;
//     double seed = fabs(this.seed);
//     double seed2 = sqrt(seed + (seed / 2) + SMALL_EPSILON) / ((seed * 0.5) + SMALL_EPSILON) * 0.25;
//     //VARIABLES   
//     double x, y;
//     int intx = 0;
//     int inty = 0;
//     double r = -tdeg;
//     double r0 = 0.0;
//     double r1 = 0.0;
//     double rmax = 0.5 * (pow(2.0, 1.0 / n) - 1.0) * width;
//     double scale = (cos(r) - sin(r)) / pAmount;
//     double tiletype = 0.0;
//     double randint = 0.0;
//     double modbase = 65535.0;
//     double multiplier = 32747.0;//1103515245;
//     double offset = 12345.0;
//     double niter = 0.0;
//     int randiter = 0;
//     //INITIALISATION   
//     x = pAffineTP.x * scale;
//     y = pAffineTP.y * scale;
//     intx = (int) round(x);
//     inty = (int) round(y);
// 
//     r = x - intx;
//     if (r < 0.0) {
//       x = 1.0 + r;
//     } else {
//       x = r;
//     }
// 
//     r = y - inty;
//     if (r < 0.0) {
//       y = 1.0 + r;
//     } else {
//       y = r;
//     }
//     //CALCULATE THE TILE TYPE
//     if (seed == 0.0) {
//       tiletype = 0.0;
//     } else if (seed == 1.0) {
//       tiletype = 1.0;
//     } else {
//       if (extended == 0) {
//         double xrand = round(pAffineTP.x);
//         double yrand = round(pAffineTP.y);
//         xrand = xrand * seed2;
//         yrand = yrand * seed2;
//         niter = xrand + yrand + xrand * yrand;
//         randint = (niter + seed) * seed2 / 2.0;
//         randint = fmod((randint * multiplier + offset), modbase);
//       } else {
//         seed = floor(seed);
//         int xrand = (int) round(pAffineTP.x);
//         int yrand = (int) round(pAffineTP.y);
//         niter = fabs(xrand + yrand + xrand * yrand);
//         if (niter > 1000)
//           niter = 1000;
//         randint = seed + niter;
//         randiter = 0;
//         while (randiter < niter) {
//           randiter += 1;
//           randint = fmod((randint * multiplier + offset), modbase);
//         }
//       }
//       tiletype = fmod(randint, 2.0);//randint%2;
//     }
//     //DRAWING THE POINTS
//     if (extended == 0) { //Fast drawmode
//       if (tiletype < 1.0) {
//         r0 = pow((pow(fabs(x), n) + pow(fabs(y), n)), onen);
//         r1 = pow((pow(fabs(x - 1.0), n) + pow(fabs(y - 1.0), n)), onen);
//       } else {
//         r0 = pow((pow(fabs(x - 1.0), n) + pow(fabs(y), n)), onen);
//         r1 = pow((pow(fabs(x), n) + pow(fabs(y - 1.0), n)), onen);
//       }
//     } else {
//       if (tiletype == 1.0) { //Slow drawmode 
//         r0 = pow((pow(fabs(x), n) + pow(fabs(y), n)), onen);
//         r1 = pow((pow(fabs(x - 1.0), n) + pow(fabs(y - 1.0), n)), onen);
//       } else {
//         r0 = pow((pow(fabs(x - 1.0), n) + pow(fabs(y), n)), onen);
//         r1 = pow((pow(fabs(x), n) + pow(fabs(y - 1.0), n)), onen);
//       }
//     }
// 
//     r = fabs(r0 - 0.5) / rmax;
//     if (r < 1.0) {
//       if (direct_color == 1) {
//         pVarTP.color = limitVal(r0, 0.0, 1.0);
//       }
//       pVarTP.x += size * (x + floor(pAffineTP.x));
//       pVarTP.y += size * (y + floor(pAffineTP.y));
//     }
// 
//     r = fabs(r1 - 0.5) / rmax;
//     if (r < 1.0) {
//       if (direct_color == 1) {
//         pVarTP.color = limitVal(1.0 - r1, 0.0, 1.0);
//       }
//       pVarTP.x += size * (x + floor(pAffineTP.x));
//       pVarTP.y += size * (y + floor(pAffineTP.y));
//       if (pContext.isPreserveZCoordinate()) {
//         pVarTP.z += pAmount * pAffineTP.z;
//       }
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
//     return new Object[]{extended, exponent, arc_width, rotation, size, seed, direct_color};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_EXTENDED.equalsIgnoreCase(pName))
//       extended = limitIntVal(Tools.FTOI(pValue), 0, 1);
//     else if (PARAM_EXPONENT.equalsIgnoreCase(pName))
//       exponent = pValue;
//     else if (PARAM_ARC_WIDTH.equalsIgnoreCase(pName))
//       arc_width = pValue;
//     else if (PARAM_ROTATION.equalsIgnoreCase(pName))
//       rotation = pValue;
//     else if (PARAM_SIZE.equalsIgnoreCase(pName))
//       size = pValue;
//     else if (PARAM_SEED.equalsIgnoreCase(pName))
//       seed = pValue;
//     else if (PARAM_DIRECT_COLOR.equalsIgnoreCase(pName))
//       direct_color = limitIntVal(Tools.FTOI(pValue), 0, 1);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "truchet";
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     if (extended < 0) {
//       extended = 0;
//     } else if (extended > 1) {
//       extended = 1;
//     }
//     if (exponent < 0.001) {
//       exponent = 0.001;
//     } else if (exponent > 2.0) {
//       exponent = 2.0;
//     }
//     if (arc_width < 0.001) {
//       arc_width = 0.001;
//     } else if (arc_width > 1.0) {
//       arc_width = 1.0;
//     }
//     if (size < 0.001) {
//       size = 0.001;
//     } else if (size > 10.0) {
//       size = 10.0;
//     }
//   }
// 
// }
// 
