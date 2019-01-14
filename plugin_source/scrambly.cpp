/*
    Apophysis Plugin: scrambly

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ScramblyFunc.java

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

const int MX_L = 25;
const int MX_L2 = 626;

typedef struct
{
	int l;
	int seed;
	int byrows;
	double cellsize;
	int _current_l;
	double _cella;
	double _cellainv;
	double _mzcella;
	int _mx_rd;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "scrambly_"
#include "plugin.h"

APO_PLUGIN("scrambly");
APO_VARIABLES(
	VAR_INTEGER(l, 3),
	VAR_INTEGER(seed, 51),
	VAR_INTEGER(byrows, 0),
	VAR_REAL(cellsize, 0.1),

);


void mx_randflip (Variation* vp, int idxmin, int idxmax, int seed, int[] mxrdp) {

    int i, j, prn, ridx;
    prn = 1;

    for (j = idxmin; ; j++) { // 1 means that I used a custom cycle break rule.
      prn = prn * 1103515245 + 12345; // jwildfire source code :D
      prn = prn & 0xFFFF0000 |
              ((prn << 8) & 0xFF00) | ((prn >> 8) & 0x00FF); // flippy bytes
      prn = (prn & 4) != 0 ? prn - VAR(seed) : prn ^ VAR(seed);
      prn = (prn < 0) ? -prn : prn; // neg are troubleful
      ridx = 1 + j;
      if (idxmax > ridx) {
        ridx += prn % (idxmax - ridx);
      } else {
        //printf("STOP> %i %i %i\n",ridx, idxmin , idxmax);
        break;
      }
      //printf("!! %i ",ridx);
      i = mxrdp[ridx];
      mxrdp[ridx] = mxrdp[j];
      mxrdp[j] = i;
      //printf("-> %i\n",mx_rd[j]);
    }
    //printf("rflip end-> %i\n",mx_rd[j]);
}

int SGN (Variation* vp, int x) {

    if (x < 0) {
      return -1;
    } else if (x > 0) {
      return 1;
    } else {
      return 0;
    }
}


int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
    VAR(_mx_rd) = new int[MX_L2];
    int curL = VAR(l);
    int VAR(seed) = VAR(seed);
    int VAR(byrows) = VAR(byrows);
    int j;
    int LL, LL2;

    LL = curL * SGN(vp, curL);

    if (LL < 3)
      LL = 3; // min
    else if (LL > MX_L)
      LL = MX_L; // max

    LL2 = LL * LL;
    VAR(_current_l) = LL;

    if (VAR(seed) >= 0 && VAR(seed) <= 50) {
      for (j = 0; j < LL2; j++) {
        VAR(_mx_rd)[j] = (VAR(seed) + j + 1) % LL2; // shifts the matrix (interesting effect)
      }
    } else {
      for (j = 0; j < LL2; j++) {
        VAR(_mx_rd)[j] = j;
      }

      if (VAR(byrows) == 0) {
        mx_randflip(vp, 0, LL2, VAR(seed), VAR(_mx_rd)); // scrambles the whole matrix
      } else {
        for (j = 0; j < LL; j++) {
          mx_randflip(vp, LL * j, LL * (1 + j), VAR(seed) + j, VAR(_mx_rd)); // scrambles row by row
        }
      }
    }

    VAR(_cella) = VAR(cellsize) / VAR(_current_l);
    VAR(_mzcella) = 0.5 * VAR(cellsize);
    VAR(_cellainv) = 1.0 / VAR(_cella);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    /* scrambly by dark-beam, http://dark-beam.deviantart.com/art/Scrambly-463910011 */
    double Vx = FTx;
    double Vy = FTy;
    int Ix;
    int Iy;
    int swp;

    Vx += VAR(_mzcella);
    Vy += VAR(_mzcella);
    Vx *= VAR(_cellainv);
    Vy *= VAR(_cellainv);
    Ix = (int) floor(Vx);
    Iy = (int) floor(Vy);

    if (VAR(_current_l) <= 0 || Ix < 0 || Ix >= VAR(_current_l) || Iy < 0 || Iy >= VAR(_current_l)) {
      FPx += VVAR * FTx;
      FPy += VVAR * FTy;
    } else {
      Vx -= Ix;
      Vy -= Iy;
      // randomizing int parts:
      swp = Ix + VAR(_current_l) * Iy;
      swp = (int) VAR(_mx_rd)[swp];
      Iy = swp / VAR(_current_l);
      Ix = swp % VAR(_current_l);

      // add int parts to fractional:
      Vx += Ix;
      Vy += Iy;
      Vx *= VAR(_cella);
      Vy *= VAR(_cella);
      Vx -= VAR(_mzcella);
      Vy -= VAR(_mzcella);
      FPx += VVAR * Vx;
      FPy += VVAR * Vy;
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
// import static org.jwildfire.base.mathlib.MathLib.floor;
// 
// public class ScramblyFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_L = "l";
//   private static final String PARAM_SEED = "seed";
//   private static final String PARAM_BYROWS = "byrows";
//   private static final String PARAM_CELLSIZE = "cellsize";
//   private static final String[] paramNames = {PARAM_L, PARAM_SEED, PARAM_BYROWS, PARAM_CELLSIZE};
// 
//   private int l = 3;
//   private int seed = 51;
//   private int byrows = 0;
//   private double cellsize = 0.1;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     /* scrambly by dark-beam, http://dark-beam.deviantart.com/art/Scrambly-463910011 */
//     double Vx = pAffineTP.x;
//     double Vy = pAffineTP.y;
//     int Ix;
//     int Iy;
//     int swp;
// 
//     Vx += _mzcella;
//     Vy += _mzcella;
//     Vx *= _cellainv;
//     Vy *= _cellainv;
//     Ix = (int) floor(Vx);
//     Iy = (int) floor(Vy);
// 
//     if (_current_l <= 0 || Ix < 0 || Ix >= _current_l || Iy < 0 || Iy >= _current_l) {
//       pVarTP.x += pAmount * pAffineTP.x;
//       pVarTP.y += pAmount * pAffineTP.y;
//     } else {
//       Vx -= Ix;
//       Vy -= Iy;
//       // randomizing int parts:
//       swp = Ix + _current_l * Iy;
//       swp = (int) _mx_rd[swp];
//       Iy = swp / _current_l;
//       Ix = swp % _current_l;
// 
//       // add int parts to fractional:
//       Vx += Ix;
//       Vy += Iy;
//       Vx *= _cella;
//       Vy *= _cella;
//       Vx -= _mzcella;
//       Vy -= _mzcella;
//       pVarTP.x += pAmount * Vx;
//       pVarTP.y += pAmount * Vy;
//     }
// 
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
//     return new Object[]{l, seed, byrows, cellsize};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_L.equalsIgnoreCase(pName))
//       l = Tools.FTOI(pValue);
//     else if (PARAM_SEED.equalsIgnoreCase(pName))
//       seed = Tools.FTOI(pValue);
//     else if (PARAM_BYROWS.equalsIgnoreCase(pName))
//       byrows = Tools.FTOI(pValue);
//     else if (PARAM_CELLSIZE.equalsIgnoreCase(pName))
//       cellsize = limitVal(pValue, 1.0e-20, 1.0e20);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "scrambly";
//   }
// 
//   private static final int MX_L = 25; // set it lower on low memory machines
//   private static final int MX_L2 = 626; // set it lower on low memory machines
//   private int _current_l;
//   private double _cella;
//   private double _cellainv;
//   private double _mzcella;
//   private int _mx_rd[];
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     _mx_rd = new int[MX_L2];
//     int curL = this.l;
//     int seed = this.seed;
//     int byrows = this.byrows;
//     int j;
//     int LL, LL2;
// 
//     LL = curL * SGN(curL);
// 
//     if (LL < 3)
//       LL = 3; // min
//     else if (LL > MX_L)
//       LL = MX_L; // max
// 
//     LL2 = LL * LL;
//     _current_l = LL;
// 
//     if (seed >= 0 && seed <= 50) {
//       for (j = 0; j < LL2; j++) {
//         _mx_rd[j] = (seed + j + 1) % LL2; // shifts the matrix (interesting effect)
//       }
//     } else {
//       for (j = 0; j < LL2; j++) {
//         _mx_rd[j] = j;
//       }
// 
//       if (byrows == 0) {
//         mx_randflip(0, LL2, seed, _mx_rd); // scrambles the whole matrix
//       } else {
//         for (j = 0; j < LL; j++) {
//           mx_randflip(LL * j, LL * (1 + j), seed + j, _mx_rd); // scrambles row by row
//         }
//       }
//     }
// 
//     _cella = this.cellsize / _current_l;
//     _mzcella = 0.5 * this.cellsize;
//     _cellainv = 1.0 / _cella;
//   }
// 
//   private void mx_randflip(int idxmin, int idxmax, int seed, int[] mxrdp) {
//     int i, j, prn, ridx;
//     prn = 1;
// 
//     for (j = idxmin; ; j++) { // 1 means that I used a custom cycle break rule.
//       prn = prn * 1103515245 + 12345; // jwildfire source code :D
//       prn = prn & 0xFFFF0000 |
//               ((prn << 8) & 0xFF00) | ((prn >> 8) & 0x00FF); // flippy bytes
//       prn = (prn & 4) != 0 ? prn - seed : prn ^ seed;
//       prn = (prn < 0) ? -prn : prn; // neg are troubleful
//       ridx = 1 + j;
//       if (idxmax > ridx) {
//         ridx += prn % (idxmax - ridx);
//       } else {
//         //printf("STOP> %i %i %i\n",ridx, idxmin , idxmax);
//         break;
//       }
//       //printf("!! %i ",ridx);
//       i = mxrdp[ridx];
//       mxrdp[ridx] = mxrdp[j];
//       mxrdp[j] = i;
//       //printf("-> %i\n",mx_rd[j]);
//     }
//     //printf("rflip end-> %i\n",mx_rd[j]);
//   }
// 
//   private int SGN(int x) {
//     if (x < 0) {
//       return -1;
//     } else if (x > 0) {
//       return 1;
//     } else {
//       return 0;
//     }
//   }
// }
// 
