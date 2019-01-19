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
    int hypertile1_p, hypertile1_q;

    double pa;
    double r;

} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("hypertile1");


// Define the Variables
APO_VARIABLES(
    VAR_INTEGER_RANGE(hypertile1_p, 3, 0x7fffffff, 3),
    VAR_INTEGER_RANGE(hypertile1_q, 3, 0x7fffffff, 7),
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(pa) = 2*M_PI / VAR(hypertile1_p);

    double r2 = 1 - (cos(2*M_PI/VAR(hypertile1_p)) - 1) /
        (cos(2*M_PI/VAR(hypertile1_p)) + cos(2*M_PI/VAR(hypertile1_q)));
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
    double sina, cosa;
    fsincos(GOODRAND_01() * VAR(pa), &sina, &cosa);

    double re = VAR(r) * cosa,
           im = VAR(r) * sina;

    double a = FTx + re,
           b = FTy - im;

    double c = re*FTx - im*FTy + 1,
           d = re*FTy + im*FTx;

    double vr = VVAR / (sqr(c) + sqr(d));

    FPx += vr * (a*c + b*d);
    FPy += vr * (b*c - a*d);

    return TRUE;
}
