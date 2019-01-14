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
    int hypertile3D1_p, hypertile3D1_q;

    double pa, r, c2, s2z;

GOODRAND_STRUCT;
} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("hypertile3D1");


// Define the Variables
APO_VARIABLES(
    VAR_INTEGER_RANGE(hypertile3D1_p, 3, 0x7fffffff, 3),
    VAR_INTEGER_RANGE(hypertile3D1_q, 3, 0x7fffffff, 7),
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    double pa = 2*M_PI / VAR(hypertile3D1_p),
           qa = 2*M_PI / VAR(hypertile3D1_q);

    double r = -(cos(pa) - 1) / (cos(pa) + cos(qa));
    if (r > 0)
        r = 1 / sqrt(1 + r);
    else
        r = 1;

    VAR(pa) = pa;
    VAR(r) = r;
    VAR(c2) = sqr(r);
    VAR(s2z) = 1 - VAR(c2);

    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double sina, cosa;
    fsincos(GOODRAND_01() * VAR(pa), &sina, &cosa);
    double cx = VAR(r) * cosa;
    double cy = VAR(r) * sina;

    double s2x = 1 + sqr(cx) - sqr(cy);
    double s2y = 1 + sqr(cy) - sqr(cx);

    double r2 = sqr(FTx) + sqr(FTy) + sqr(FTz);

    double x2cx = 2*cx*FTx,
           y2cy = 2*cy*FTy;

    double d = VVAR / (
        VAR(c2) * r2 + x2cx - y2cy + 1
        );

    FPx += d * (
        FTx * s2x - cx * ( y2cy - r2 - 1)
    );
    FPy += d * (
        FTy * s2y + cy * (-x2cx - r2 - 1)
    );
    FPz += d * (
        FTz * VAR(s2z)
    );


    return TRUE;
}
