/*
    Apophysis Plugin

    Copyright (C) 2007-2009 Joel Faber
    Copyright (C) 2007-2009 Michael Faber

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
    double vvar2;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("glynnia");

// Define the Variables
APO_VARIABLES(
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(vvar2) = VVAR * sqrt(2.0) / 2.0;
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double r = sqrt(sqr(FTx) + sqr(FTy));
    double d;

    
    if( r >= 1.0)
    {
        if( random01() > 0.5)
        {
            d = sqrt(r + FTx);
            FPx += VAR(vvar2) * d;
            FPy -= VAR(vvar2) / d * FTy; //+= VAR(vvar2) / d * FTy;
        }
        else
        {
            d = r + FTx;
            r = VVAR / sqrt(r * ( sqr(FTy) + sqr(d)));
            FPx += r * d;
            FPy += r * FTy; //-= r * FTy; 
        }
    }
    else
    {
        if( random01() > 0.5)
        {
            d = sqrt(r + FTx);
            FPx -= VAR(vvar2) * d;
            FPy -= VAR(vvar2) / d * FTy;
        }
        else
        {
            d = r + FTx;
            r = VVAR / sqrt(r * ( sqr(FTy) + sqr(d)));
            FPx -= r * d;
            FPy += r * FTy;
        }
    }

            

    return TRUE;
}
