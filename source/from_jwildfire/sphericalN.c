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
    double sphericalN_power,sphericalN_dist;
    

} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("sphericalN");


// Define the Variables
APO_VARIABLES(
    VAR_REAL(sphericalN_power,  1.0),
    VAR_REAL(sphericalN_dist,  1.0)
    
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    //VAR(spher_rad2) = VAR(spher_rad)*VAR(spher_rad);
    return TRUE; // Always return TRUE.
}



// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    
    double sina, cosa;
    //R=sqrt(sqr(FTx)+sqr(FTy));
    double R=pow(sqrt(sqr(FTx)+sqr(FTy)),VAR(sphericalN_dist));
    int N=floor(VAR(sphericalN_power)*random01());
    double alpha=atan2(FTy,FTx)+N*M_2PI/floor(VAR(sphericalN_power));
    fsincos(alpha,&sina,&cosa);
    
    FPx+=VVAR*cosa/R;
    FPy+=VVAR*sina/R;    
    

    

    return TRUE;
}
