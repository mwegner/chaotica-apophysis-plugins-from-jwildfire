/*
    Apophysis Plugin: post_point_symmetry

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

typedef struct
{
    double radius = 0.5;
	double ang1;
	double ang2;
	int dual_t = 1;
	int outside = 0;

	// not exposed
	double sina, cosa;
	double sinb, cosb;
} Variables;

#include "plugin.h"

APO_PLUGIN("yin_yang");
APO_VARIABLES(
	VAR_REAL(radius, 0.5),
	VAR_REAL(ang1, 0.0),
	VAR_REAL(ang2, 0.0),
	VAR_INTEGER_RANGE(dual_t, 0, 1, 1),
	VAR_INTEGER_RANGE(outside, 0, 1, 0),
);

int PluginVarPrepare(Variation* vp)
{
	VAR(sina) = sin(M_PI * VAR(ang1));
    VAR(cosa) = cos(M_PI * VAR(ang1));
    VAR(sinb) = sin(M_PI * VAR(ang2));
    VAR(cosb) = cos(M_PI * VAR(ang2));

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
	 /* yin_yang by dark-beam */
    double xx = FTx;
    double yy = FTy;
    double inv = 1;
    double RR = VAR(radius);
    double R2 = (xx * xx + yy * yy);

    if (R2 < 1.0) {

      double nx = xx * VAR(cosa) - yy * VAR(sina);
      double ny = xx * VAR(sina) + yy * VAR(cosa);
      if (VAR(dual_t) == 1 && random01() > 0.5) {
        inv = -1;
        RR = 1 - VAR(radius);
        nx = xx * VAR(cosb) - yy * VAR(sinb);
        ny = xx * VAR(sinb) + yy * VAR(cosb);
      }

      xx = nx;
      yy = ny;
      if (yy > 0) {
        double t = sqrt(1 - yy * yy);
        double k = xx / t;
        double t1 = (t - 0.5) * 2;
        double alfa = (1. - k) * 0.5;
        double beta = (1. - alfa);
        double dx = alfa * (RR - 1);
        double k1 = alfa * (RR) + beta * 1;
        FPx += VVAR * (t1 * k1 + dx) * inv;
        FPy += VVAR * sqrt(1 - t1 * t1) * k1 * inv;
      } else {
        FPx += VVAR * (xx * (1 - RR) + RR) * inv;
        FPy += VVAR * (yy * (1 - RR)) * inv;
      }
    } else if (VAR(outside) == 1) {
      FPx += VVAR * FTx;
      FPy += VVAR * FTy;
    } else {
      FPx += 0.0; // out!
      FPy += 0.0; // out!
    }

    FPz += VVAR * FTz;

    return TRUE;
}
