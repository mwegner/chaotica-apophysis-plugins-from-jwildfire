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
    double oscope_separation;
    double oscope_frequency;
    double oscope_amplitude;
    double oscope_damping;
    double TWO_PI_freq;

} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("oscilloscope");

// Define the Variables
APO_VARIABLES(
    VAR_REAL(oscope_separation, 1.0),
    VAR_REAL(oscope_frequency, M_PI),
    VAR_REAL(oscope_amplitude, 1.0),
    VAR_REAL(oscope_damping, 0.0)
);


int PluginVarPrepare(Variation* vp)
{
    VAR(TWO_PI_freq) = VAR(oscope_frequency) * M_PI*2;
    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    double t;

    if(VAR(oscope_damping) == 0)
    {
        t = VAR(oscope_amplitude)*cos(VAR(TWO_PI_freq)*FTx) + VAR(oscope_separation);
    }
    else
    {
        t = VAR(oscope_amplitude)*exp(-abs(FTx)*VAR(oscope_damping))*cos(VAR(TWO_PI_freq)*FTx) + VAR(oscope_separation);
    }

    if(abs(FTy) <= t)
    {
        FPx += VVAR*FTx;
        FPy -= VVAR*FTy;
    }
    else
    {
        FPx += VVAR*FTx;
        FPy += VVAR*FTy;
    }
    return TRUE;
}
