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

// Must define this structure before we include apoplugin.h
typedef struct
{
	double epispiral_n;
	double epispiral_thickness;
	double epispiral_holes;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("epispiral");


// Define the Variables
APO_VARIABLES(
    VAR_REAL(epispiral_n,  6.0),
    VAR_REAL(epispiral_thickness,  0.0),
    VAR_REAL(epispiral_holes,  1.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    // converted from JWildfire java version... reduced/fixed a tiny bit the code (DarkBeam)
    // epispiral by cyberxaos, http://cyberxaos.deviantart.com/journal/Epispiral-Plugin-240086108

    double theta = atan2(FTy, FTx);
    double t = -VAR(epispiral_holes);
    double d = cos(VAR(epispiral_n) * theta);
    double s, c;

    fsincos(theta, &s, &c);

    if (fabs(d) < EPS) { // no infinity tx
        d = EPS;
    }

    if (fabs(VAR(epispiral_thickness)) > EPS) {
        t += (random01() * VAR(epispiral_thickness));
    }
    else {
        t += 1.0;
    }

    t *= VVAR / d;

    FPx += t * c;
    FPy += t * s;

    return TRUE;
}
