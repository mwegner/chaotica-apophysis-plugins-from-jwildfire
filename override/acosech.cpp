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

} Variables;

#include "apoplugin.h"
#include "complexhelpers.h"

// Set the name of this plugin
APO_PLUGIN("acosech");


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
    Complex z(FTx, FTy);
    
    z = complexAcosecH(z);
    z = complexFlip(z);
    z = complexScale(z, VVAR * M_2_PI);

    if (GOODRAND_01() < 0.5) {
      FPx += z.real();
      FPy += z.imag();
    } else {
      FPx += -z.real();
      FPy += -z.imag();
    }
    
    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }

    return TRUE;
}
