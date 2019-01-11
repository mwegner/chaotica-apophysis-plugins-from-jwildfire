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
    double lazyTravis_spin_in;
    double lazyTravis_spin_out;
    double lazyTravis_space;
    double spin_in;
    double spin_out;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("lazyTravis");

// Define the Variables
APO_VARIABLES(
    VAR_REAL_CYCLE(lazyTravis_spin_in, 0.0, 2.0, 1.0),
    VAR_REAL_CYCLE(lazyTravis_spin_out, 0.0, 2.0, 0.0),
    VAR_REAL(lazyTravis_space, 0.0)

);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    VAR(spin_in) = 4.0 * VAR(lazyTravis_spin_in);
    VAR(spin_out) = 4.0 * VAR(lazyTravis_spin_out);
    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double x = fabs(FTx);
    double y = fabs(FTy);
    double s;
    double p;
    double x2, y2;


    
    if( x > VVAR || y > VVAR)
    {
        if ( x > y)
        {
            s = x;

            if( FTx > 0.0)
            {
                p = s + FTy + s * VAR(spin_out);
            }
            else
            {
                p = 5.0 * s - FTy + s * VAR(spin_out);
            }
        }
        else
        {
            s = y;
            if( FTy > 0.0)
            {
                p = 3.0 * s - FTx + s * VAR(spin_out);
            }
            else
            {
                p = 7.0 * s + FTx + s * VAR(spin_out);
            }
        }

        p = fmod(p, s * 8.0);

        if( p <= 2.0 * s)
        {
            x2 = s + VAR(lazyTravis_space) ;
            y2 = -(1.0 * s - p);
            y2 = y2 + y2 / s * VAR(lazyTravis_space);
        }
        else if( p <= 4.0 * s)
        {
            
            y2 = s + VAR(lazyTravis_space);
            x2 = ( 3.0 * s - p);
            x2 = x2 + x2 / s * VAR(lazyTravis_space);
        }
        else if( p <= 6.0 * s)
        {
            x2 =  -(s + VAR(lazyTravis_space));
            y2 = ( 5.0 * s - p);
            y2 = y2 + y2 / s * VAR(lazyTravis_space);
        }
        else
        {
            y2 = -(s + VAR(lazyTravis_space));
            x2 = -(7.0 * s - p);
            x2 = x2 + x2 / s * VAR(lazyTravis_space);
        }

        FPx += VVAR *  x2;
        FPy += VVAR *  y2;
    }
    else
    {
        if ( x > y)
        {
            s = x;
    
            if( FTx > 0.0)
            {
                p = s + FTy + s * VAR(spin_in);
            }
            else
            {
                p = 5.0 * s - FTy + s * VAR(spin_in);
            }
        }
        else
        {
            s = y;
            if( FTy > 0.0)
            {
                p = 3.0 * s - FTx + s * VAR(spin_in);
            }
            else
            {
                p = 7.0 * s + FTx + s * VAR(spin_in);
            }
        }
        
        p = fmod(p, s * 8.0);
        
        if( p <= 2.0 * s)
        {
            FPx += VVAR * s;
            FPy -= VVAR * (s - p);
        }
        else if( p <= 4.0 * s)
        {
            FPx += VVAR * ( 3.0 * s - p);
            FPy += VVAR * s;
        }
        else if( p <= 6.0 * s)
        {
            FPx -= VVAR * s;
            FPy += VVAR * ( 5.0 * s - p);
        }
        else
        {
            FPx -= VVAR * (7.0 * s - p);
            FPy -= VVAR * s;
        }
    }
    
    
    return TRUE;
}
