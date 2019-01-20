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
    int hypertile2_p, hypertile2_q;

    double pa;
    double r;
} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("hypertile2");


// Define the Variables
APO_VARIABLES(
    VAR_INTEGER_RANGE(hypertile2_p, 3, 0x7fffffff, 3),
    VAR_INTEGER_RANGE(hypertile2_q, 3, 0x7fffffff, 7),
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(pa) = 2*M_PI / VAR(hypertile2_p);

    double r2 = 1 - (cos(2*M_PI/VAR(hypertile2_p)) - 1) /
        (cos(2*M_PI/VAR(hypertile2_p)) + cos(2*M_PI/VAR(hypertile2_q)));
    if(r2 > 0)
        VAR(r) = 1 / sqrt(r2);
    else
        VAR(r) = 1.0;

    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double a = FTx + VAR(r),
           b = FTy;

    double c = VAR(r)*FTx + 1,
           d = VAR(r)*FTy;

    double x = (a*c + b*d),
           y = (b*c - a*d);

    double vr = VVAR / (sqr(c) + sqr(d));

    double sina, cosa;
    fsincos(GOODRAND_01() * VAR(pa), &sina, &cosa);

    FPx += vr * (x*cosa + y*sina);
    FPy += vr * (y*cosa - x*sina);

    return TRUE;
}
