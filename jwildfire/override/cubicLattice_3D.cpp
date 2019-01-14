/*
    Apophysis 3D Plugin

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

/*
    This 3D plugin written by
	Larry Berlin
	September 2009
	http://apophysisrevealed.com
*/

typedef struct
{                       
  
   // User Input Values
    double cubicLattice_3D_xpand;
	double cubicLattice_3D_style;
	int style;
	  
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("cubicLattice_3D");

// Define the Variables
APO_VARIABLES(
    
	VAR_REAL(cubicLattice_3D_xpand,  0.2),
	VAR_REAL(cubicLattice_3D_style,  1.0),
	
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{	
	
	//  Any pre-calc operations
	if(fabs(VAR(cubicLattice_3D_style))>=2.0)
	{
	    VAR(style) = 2;
	}
	else
	{
	    VAR(style) = 1;
	}

  return TRUE; // Always return TRUE.    

}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double fill, exnze, wynze, znxy;
	if(fabs(VAR(cubicLattice_3D_xpand))<=1.0)
	{
	    fill = VAR(cubicLattice_3D_xpand)*0.5;  // values up to 0.5
	}
	else
	{
	    fill = sqrt(VAR(cubicLattice_3D_xpand))*0.5;  // values above 0.5
	}
	if(VAR(style)==2)
	{
	    exnze = cos(atan2(FTx, FTz));
	    wynze = sin(atan2(FTy, FTz));
	    znxy = (exnze+wynze)/2.0;
    }	
	else
	{
	    exnze = 1.0;
	    wynze = 1.0;
	    znxy = 1.0;
	}
		
	double lattd = VVAR;     // optionally * 0.5;   
	int useNode = 0;	
	double rchoice = trunc(random01() * 8.0 );		
	useNode = rchoice;	
	if (useNode == 0)
	{
	    FPx = (FPx+FTx) * fill * exnze + lattd;
		FPy = (FPy+FTy) * fill * wynze + lattd;
		FPz = (FPz+FTz) * fill * znxy  + lattd;		
	}
	if (useNode == 1)
	{
	    FPx = (FPx+FTx) * fill * exnze + lattd;
		FPy = (FPy+FTy) * fill * wynze - lattd;
		FPz = (FPz+FTz) * fill * znxy  + lattd;
	}
	if (useNode == 2)
	{
	    FPx = (FPx+FTx) * fill * exnze + lattd;
		FPy = (FPy+FTy) * fill * wynze + lattd;
		FPz = (FPz+FTz) * fill * znxy  - lattd;
	}
	if (useNode == 3)
	{
	    FPx = (FPx+FTx) * fill * exnze + lattd;
		FPy = (FPy+FTy) * fill * wynze - lattd;
		FPz = (FPz+FTz) * fill * znxy  - lattd;
	}
	if (useNode == 4)
	{
	    FPx = (FPx+FTx) * fill * exnze - lattd;
		FPy = (FPy+FTy) * fill * wynze + lattd;
		FPz = (FPz+FTz) * fill * znxy  + lattd;
	}
	if (useNode == 5)
	{
	    FPx = (FPx+FTx) * fill * exnze - lattd;
		FPy = (FPy+FTy) * fill * wynze - lattd;
		FPz = (FPz+FTz) * fill * znxy  + lattd;
	}
	if (useNode == 6)
	{
	    FPx = (FPx+FTx) * fill * exnze - lattd;
		FPy = (FPy+FTy) * fill * wynze + lattd;
		FPz = (FPz+FTz) * fill * znxy  - lattd;
	}
	if (useNode == 7)
	{
	    FPx = (FPx+FTx) * fill * exnze - lattd;
		FPy = (FPy+FTy) * fill * wynze - lattd;
		FPz = (FPz+FTz) * fill * znxy  - lattd;
	}

  return TRUE; // Always return TRUE.    

}









