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



typedef struct
{                       
    double rz_sin, rz_cos;

} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("pre_spin_z");

// Define the Variables
APO_VARIABLES(

);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    
  double sina, cosa;   
 
  fsincos((VVAR * M_PI_2), &sina, &cosa);

  VAR(rz_sin) = sina;
  VAR(rz_cos) = cosa;

  return TRUE; // Always return TRUE.    
    
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{

  double y;

    y = VAR(rz_cos) * FTy - VAR(rz_sin) * FTx;
    FTx = VAR(rz_sin) * FTy + VAR(rz_cos) * FTx;
    FTy = y;
  
  return TRUE; // Always return TRUE.    

}
