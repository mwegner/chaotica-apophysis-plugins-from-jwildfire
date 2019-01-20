#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin

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

// Must define this structure before we include apoplugin.h
typedef struct
{
    int hypertile3D2_p, hypertile3D2_q;

    double pa;

    double cx, c2, c2x;
    double s2x, s2y, s2z;
} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("hypertile3D2");


// Define the Variables
APO_VARIABLES(
    VAR_INTEGER_RANGE(hypertile3D2_p, 3, 0x7fffffff, 3),
    VAR_INTEGER_RANGE(hypertile3D2_q, 3, 0x7fffffff, 7),
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    double pa = 2*M_PI / VAR(hypertile3D2_p),
           qa = 2*M_PI / VAR(hypertile3D2_q);

    double r = -(cos(pa) - 1) / (cos(pa) + cos(qa));
    if (r > 0)
        r = 1 / sqrt(1 + r);
    else
        r = 1;

    VAR(pa) = pa;

    VAR(cx) = r;
    VAR(c2) = sqr(VAR(cx));
    VAR(c2x) = 2 * VAR(cx);

    VAR(s2x) = 1 + sqr(VAR(cx));
    VAR(s2y) = 1 - sqr(VAR(cx));
    VAR(s2z) = 1 - sqr(VAR(cx));

    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double r2 = sqr(FTx) + sqr(FTy) + sqr(FTz);

    double x2cx = VAR(c2x)*FTx;

    double x = FTx * VAR(s2x) - VAR(cx) * (-r2 - 1);
    double y = FTy * VAR(s2y);

    double vr = VVAR / (VAR(c2) * r2 + x2cx + 1);

    double sina, cosa;
    fsincos(GOODRAND_01() * VAR(pa), &sina, &cosa);

    FPx += vr * (x*cosa + y*sina);
    FPy += vr * (y*cosa - x*sina);
    FPz += vr * (FTz * VAR(s2z));

    return TRUE;
}
