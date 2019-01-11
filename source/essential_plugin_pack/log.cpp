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
    double base, log_base;
} Variables;

#include "apoplugin.h"

//#include <complex>

//using namespace std;

//typedef complex<double> Complex;

// Set the name of this plugin
APO_PLUGIN("log");


// Define the Variables
APO_VARIABLES(
    VAR_REAL_RANGE(log_base, 0.000001, DBL_MAX, 2.7182818284590452353602874713527)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(base) =  VVAR * 0.5;
    if (fabs(VAR(log_base) - 1.) > 0.000001 && VAR(log_base) > 0.000001 )  VAR(base) /= log(VAR(log_base));
    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    FPx += (VAR(base) * log(FTx * FTx + FTy * FTy + 0.000001));
    FPy += VVAR * (atan2(FTy, FTx));

    return TRUE;
}
