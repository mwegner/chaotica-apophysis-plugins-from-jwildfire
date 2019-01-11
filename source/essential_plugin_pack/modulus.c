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
    double modulus_x;
    double modulus_y;

    double xrange;
    double yrange;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("modulus");

// Define the Variables
APO_VARIABLES(
    VAR_REAL(modulus_x, 1.0),
    VAR_REAL(modulus_y, 1.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(xrange) = 2.0 * VAR(modulus_x);
    VAR(yrange) = 2.0 * VAR(modulus_y);
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    if (FTx > VAR(modulus_x))
    {
        FPx += VVAR * (-VAR(modulus_x) + fmod(FTx + VAR(modulus_x), VAR(xrange)));
    }
    else if (FTx < -VAR(modulus_x))
    {
        FPx += VVAR * (VAR(modulus_x) - fmod(VAR(modulus_x) - FTx, VAR(xrange)));
    }
    else
    {
        FPx += VVAR * FTx;
    }

    if (FTy > VAR(modulus_y))
    {
        FPy += VVAR * (-VAR(modulus_y) + fmod(FTy + VAR(modulus_y), VAR(yrange)));
    }
    else if (FTy < -VAR(modulus_y))
    {
        FPy += VVAR * (VAR(modulus_y) - fmod(VAR(modulus_y) - FTy, VAR(yrange)));
    }
    else
    {
        FPy += VVAR * FTy;
    }

    return TRUE;
}

