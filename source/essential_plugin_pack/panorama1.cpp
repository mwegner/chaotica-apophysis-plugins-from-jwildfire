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

} Variables;

#include "apoplugin.h"

//#include <complex>

using namespace std;

//typedef complex<double> Complex;

// Set the name of this plugin
APO_PLUGIN("panorama1");


// Define the Variables
APO_VARIABLES(

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
    double aux = 1.0 / sqrt(FTx * FTx + FTy * FTy + 1);
    double x1 = FTx * aux;
    double y1 = FTy * aux;
    aux = sqrt(x1 * x1 + y1 * y1);
    FPx += VVAR * (atan2(x1,y1)) * M_1_PI;
    FPy += VVAR * (aux - 0.5);

    return TRUE;
}
