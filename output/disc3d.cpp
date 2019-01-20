#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
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
              double disc3d_pi;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("disc3d");

// Define the Variables
APO_VARIABLES(

              VAR_REAL(disc3d_pi, M_PI),
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

        double r = sqrt(FTy*FTy + FTx*FTx + EPS);    
        double sr, cr;
        
        fsincos(VAR(disc3d_pi) * r, &sr, &cr);
        double vv = VVAR * atan2(FTx, FTy) / (VAR(disc3d_pi) + EPS);          
                         
        FPx += vv * sr;
        FPy += vv * cr;
        FPz += vv * (r * cos(FTz));
        
    return TRUE;
}

