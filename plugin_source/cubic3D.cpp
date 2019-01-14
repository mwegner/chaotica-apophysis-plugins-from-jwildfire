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
	http://apophysisrevealed.com/
	http://aporev.deviantart.com/
	This is a modification of the CubicLattice_3D intended to smooth behaviors 
    for animations. It provides the same results but allows smooth transitions 
    into and out of the variation and the two styles.
*/

typedef struct
{                       
  
   // User Input Values
    double cubic3D_xpand;
	double cubic3D_style;
	  
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("cubic3D");

// Define the Variables
APO_VARIABLES(
    
	VAR_REAL(cubic3D_xpand,  0.25),
	VAR_REAL(cubic3D_style,  0.0),
	
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{	
	
	//  Any pre-calc operations


  return TRUE; // Always return TRUE.    

}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double fill, exnze, wynze, znxy;
	double smooth = 1.0;
    double smoothStyle = 1.0;	
	int useNode = 0;	
	double rchoice = trunc(random01() * 8.0 );	
	double lattd = VVAR*0.5;      	
	
	if(fabs(VAR(cubic3D_xpand))<=1.0)
	{
	    fill = VAR(cubic3D_xpand)*0.5;  // values up to 0.5
	}
	else
	{
	    fill = sqrt(VAR(cubic3D_xpand))*0.5;  // values above 0.5
	}

	if(fabs(VVAR)<=0.5)
	{
	    smooth = VVAR*2.0;  // Causes full effect above VVAR=0.5
	}
	else
	{
	    smooth = 1.0;
	}	
	
	if(fabs(VAR(cubic3D_style))<=1.0)
	{
	    smoothStyle = VAR(cubic3D_style);
	}
	else
	{
	    if(VAR(cubic3D_style)>1.0)
		{
		    smoothStyle = 1.0+(VAR(cubic3D_style)-1.0)*0.25;
		}
		else
		{
		    smoothStyle = (VAR(cubic3D_style)+1.0)*0.25-1.0;
		}	    
	}	
	
	exnze = 1.0 - (smoothStyle * (1.0-(cos(atan2(FTx, FTz))))); 
	wynze = 1.0 - (smoothStyle * (1.0-(sin(atan2(FTy, FTz)))));
	if(smoothStyle > 1.0)
	{
	    znxy  = 1.0 - (smoothStyle * (1.0-((exnze+wynze)/2.0 * smoothStyle)));
	}
	else
	{
	    znxy  = 1.0 - (smoothStyle * (1.0-((exnze+wynze)/2.0)));
	}
	
	useNode = rchoice;	
	if (useNode == 0)
	{
	    FPx =((FPx-(smooth*(1.0-fill)*FPx * exnze))+(FTx*smooth*fill * exnze)) + lattd;
		FPy =((FPy-(smooth*(1.0-fill)*FPy * wynze))+(FTy*smooth*fill * wynze)) + lattd;
		FPz =((FPz-(smooth*(1.0-fill)*FPz * znxy)) +(FTz*smooth*fill * znxy))  + lattd;
	}
	if (useNode == 1)
	{
	    FPx =((FPx-(smooth*(1.0-fill)*FPx * exnze))+(FTx*smooth*fill * exnze)) + lattd;
		FPy =((FPy-(smooth*(1.0-fill)*FPy * wynze))+(FTy*smooth*fill * wynze)) - lattd;
		FPz =((FPz-(smooth*(1.0-fill)*FPz * znxy)) +(FTz*smooth*fill * znxy))  + lattd;
	}
	if (useNode == 2)
	{
	    FPx =((FPx-(smooth*(1.0-fill)*FPx * exnze))+(FTx*smooth*fill * exnze)) + lattd;
		FPy =((FPy-(smooth*(1.0-fill)*FPy * wynze))+(FTy*smooth*fill * wynze)) + lattd;
		FPz =((FPz-(smooth*(1.0-fill)*FPz * znxy)) +(FTz*smooth*fill * znxy))  - lattd;
	}
	if (useNode == 3)
	{
	    FPx =((FPx-(smooth*(1.0-fill)*FPx * exnze))+(FTx*smooth*fill * exnze)) + lattd;
		FPy =((FPy-(smooth*(1.0-fill)*FPy * wynze))+(FTy*smooth*fill * wynze)) - lattd;
		FPz =((FPz-(smooth*(1.0-fill)*FPz * znxy)) +(FTz*smooth*fill * znxy))  - lattd;
	}
	if (useNode == 4)
	{
	    FPx =((FPx-(smooth*(1.0-fill)*FPx * exnze))+(FTx*smooth*fill * exnze)) - lattd;
		FPy =((FPy-(smooth*(1.0-fill)*FPy * wynze))+(FTy*smooth*fill * wynze)) + lattd;
		FPz =((FPz-(smooth*(1.0-fill)*FPz * znxy)) +(FTz*smooth*fill * znxy))  + lattd;
	}
	if (useNode == 5)
	{
	    FPx =((FPx-(smooth*(1.0-fill)*FPx * exnze))+(FTx*smooth*fill * exnze)) - lattd;
		FPy =((FPy-(smooth*(1.0-fill)*FPy * wynze))+(FTy*smooth*fill * wynze)) - lattd;
		FPz =((FPz-(smooth*(1.0-fill)*FPz * znxy)) +(FTz*smooth*fill * znxy))  + lattd;
	}
	if (useNode == 6)
	{
	    FPx =((FPx-(smooth*(1.0-fill)*FPx * exnze))+(FTx*smooth*fill * exnze)) - lattd;
		FPy =((FPy-(smooth*(1.0-fill)*FPy * wynze))+(FTy*smooth*fill * wynze)) + lattd;
		FPz =((FPz-(smooth*(1.0-fill)*FPz * znxy)) +(FTz*smooth*fill * znxy))  - lattd;
	}
	if (useNode == 7)
	{
	    FPx =((FPx-(smooth*(1.0-fill)*FPx * exnze))+(FTx*smooth*fill * exnze)) - lattd;
		FPy =((FPy-(smooth*(1.0-fill)*FPy * wynze))+(FTy*smooth*fill * wynze)) - lattd;
		FPz =((FPz-(smooth*(1.0-fill)*FPz * znxy)) +(FTz*smooth*fill * znxy))  - lattd;
	}

  return TRUE; // Always return TRUE.    

}









