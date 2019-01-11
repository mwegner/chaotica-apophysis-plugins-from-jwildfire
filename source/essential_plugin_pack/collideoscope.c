/*
    Apophysis Plugin

    Copyright (C) 2007-2011 Joel Faber
    Copyright (C) 2007-2011 Michael Faber

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
    double collideoscope_a;
    int collideoscope_num;
    double ka;
    double kn_pi;
    double ka_kn;
    double pi_kn;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("collideoscope");

// Define the Variables
APO_VARIABLES(
    VAR_REAL_CYCLE(collideoscope_a, 0.0, 1.0, 0.0),
    VAR_INTEGER_RANGE(collideoscope_num, 1, INT_MAX, 1)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(kn_pi) = (double) VAR(collideoscope_num) * M_1_PI;
    VAR(pi_kn) = M_PI / (double) VAR(collideoscope_num);;
    VAR(ka) = M_PI * VAR(collideoscope_a);
    VAR(ka_kn) = VAR(ka) / (double) VAR(collideoscope_num);
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double a = atan2(FTy, FTx);
    double r = VVAR * sqrt(sqr(FTx) + sqr(FTy));
    double s, c;
    int alt; 


    if(a >= 0.0)
    {
        alt = (int)( a * VAR(kn_pi));
        if ( alt % 2 == 0)
        {
            a = alt * VAR(pi_kn) + fmod(VAR(ka_kn) + a, VAR(pi_kn));
        }
        else
        {
            a = alt * VAR(pi_kn) + fmod(-VAR(ka_kn) + a, VAR(pi_kn));
        }
    }
    else
    {
        alt = (int)( -a * VAR(kn_pi));
        if ( alt % 2 == 1)
        {
            a = -( alt * VAR(pi_kn) + fmod(-VAR(ka_kn) - a, VAR(pi_kn)));
        }
        else
        {
            a = -( alt * VAR(pi_kn) + fmod(VAR(ka_kn) - a, VAR(pi_kn)));
        }
    }           

    fsincos(a, &s, &c);

    FPx += r * c;
    FPy += r * s;
    
    return TRUE;
}
