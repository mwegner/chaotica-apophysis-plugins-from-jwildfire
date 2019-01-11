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
    double db_power, db_range, db_blur, db_radius;
    double db_alpha, db_length;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("depth_blur");


// Define the Variables
APO_VARIABLES(
    VAR_REAL(db_power, 5.0),
    VAR_REAL(db_range,  0.401623),
    VAR_REAL(db_blur, 1.0),
    VAR_REAL(db_radius, 1.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(db_alpha) = M_PI / VAR(db_power);
    VAR(db_length) = sqrt(1.0 + sqr(VAR(db_range)) - 2.0 * VAR(db_range) * cos(VAR(db_alpha)));
    VAR(db_alpha) = asin(sin(VAR(db_alpha)) * VAR(db_range) / VAR(db_length));
    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double rad = sqrt(sqr(FTx) + sqr(FTy));
    double bx = 0;
    double by = 0;
    if (rad > VAR(db_radius)) {
        double f = random01() * VAR(db_power) * 2.0;
        double int_angle = trunc(f);
        f = f - int_angle;
        double x = f * VAR(db_length);
        double z = sqrt(1.0 + sqr(x) - 2.0 * x * cos(VAR(db_alpha)));
        if (((int) int_angle) % 2)
            int_angle = M_2PI / VAR(db_power) * (((int) int_angle) / 2) + asin(sin(VAR(db_alpha)) * x / z);
        else
            int_angle = M_2PI / VAR(db_power) * (((int) int_angle) / 2) - asin(sin(VAR(db_alpha)) * x / z);
        z = z * sqrt(random01());
        fsincos(int_angle - M_PI_2, &by, &bx);
        double aux = z * VAR(db_blur) * 0.1 * (rad - VAR(db_radius));
        by = aux * by;
        bx = aux * bx;
    }
    FPx += VVAR * (FTx + bx);
    FPy += VVAR * (FTy + by);

    return TRUE;
}
