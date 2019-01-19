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
	
	This plugin is designed to provide an hexagonal structure 
	for building snowflake designs. They can be built as a 
	single platform or a double platform where the two 
	are separated above and below each other on the Z axis
*/


typedef struct
{                           
	double hexaplay3D_majp;  // establishes 1 or 2 planes, and if 2, the distance between them
	double hexaplay3D_scale; // scales the effect of X and Y
	double hexaplay3D_zlift;  // scales the effect of Z axis within the snowflake
	double seg60x[6];
	double seg60y[6];
	double seg120x[3];
	double seg120y[3];
	int rswtch;      //  A value for choosing between 6 or 3 segments to a plane
	int fcycle;      //  markers to count cycles... 
	int bcycle;
} Variables;

#include "apoplugin.h"


// Set the name of this plugin
APO_PLUGIN("hexaplay3D");

// Define the Variables
APO_VARIABLES(
   	VAR_REAL(hexaplay3D_majp, 1.0),
	VAR_REAL(hexaplay3D_scale, 0.25),
	VAR_REAL(hexaplay3D_zlift, 0.25),
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{	
	
	/*  Any pre-calc operations
	    Set up two major angle systems
	*/
	VAR(rswtch) = trunc(random01()*3.0);  //  Chooses 6 or 3 nodes
	double hlift = sin(M_PI / 3.0);
	VAR(fcycle) = 0;
	VAR(bcycle) = 0;
	VAR(seg60x)[0] =  1.0;    
	VAR(seg60x)[1] =  0.5;
	VAR(seg60x)[2] = -0.5;
	VAR(seg60x)[3] = -1.0;
	VAR(seg60x)[4] = -0.5;
	VAR(seg60x)[5] =  0.5;
	
	VAR(seg60y)[0] =  0.0;     
	VAR(seg60y)[1] =  hlift;
	VAR(seg60y)[2] =  hlift;
	VAR(seg60y)[3] =  0.0;
	VAR(seg60y)[4] = -hlift;
	VAR(seg60y)[5] = -hlift;
	
	VAR(seg120x)[0] =  1.0; 
	VAR(seg120x)[1] = -0.5;
	VAR(seg120x)[2] = -0.5;
	
	VAR(seg120y)[0] =  0.0; 
    VAR(seg120y)[1] =  hlift;
    VAR(seg120y)[2] = -hlift;
	
	
  return TRUE; // Always return TRUE.    

}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    if(VAR(fcycle)>5)
	{
	    VAR(fcycle) = 0;
		VAR(rswtch) = trunc(random01()*3.0);  //  Chooses new 6 or 3 nodes
	}
	if(VAR(bcycle)>2)
	{
	    VAR(bcycle) = 0;
		VAR(rswtch) = trunc(random01()*3.0);  //  Chooses new 6 or 3 nodes
	}
	
	double lrmaj = VVAR;   // Sets hexagon length radius - major plane
	double boost;  //  Boost is the separation distance between the two planes
	int posNeg = 1;
	int loc60;
	int loc120;
	double scale = VAR(hexaplay3D_scale)*0.5;

	if (random01()< 0.5)
	{
	    posNeg = -1;
	}
	
	// Determine whether one or two major planes
	int majplane = 1;
	double abmajp = fabs(VAR(hexaplay3D_majp));
	if (abmajp <= 1.0)
	{
	    majplane = 1; // Want either 1 or 2
	}
	else
	{
	    majplane = 2;
	    boost = (abmajp - 1.0) * 0.5; // distance above and below XY plane
	}

	//  Creating Z factors relative to the planes
	if(majplane == 2)
	{
		FPz += FTz*0.5*VAR(hexaplay3D_zlift) + (posNeg * boost);  
	}
	else
	{
	    FPz += FTz*0.5*VAR(hexaplay3D_zlift);   
	}
	
	// Work out the segments and hexagonal nodes
	if(VAR(rswtch) <= 1)         // Occasion to build using 60 degree segments
	{
	    //loc60 = trunc(random01()*6.0);  // random nodes selection
		loc60 = VAR(fcycle);   // sequential nodes selection
		FPx = ((FPx+FTx) * scale) + (lrmaj * VAR(seg60x)[loc60]);  
		FPy = ((FPy+FTy) * scale) + (lrmaj * VAR(seg60y)[loc60]);
		VAR(fcycle) += 1;
	}
	else         // Occasion to build on 120 degree segments
	{
	    //loc120 = trunc(random01()*3.0);  // random nodes selection
		loc120 = VAR(bcycle);  // sequential nodes selection
		FPx = ((FPx+FTx) * scale) + (lrmaj * VAR(seg120x)[loc120]); 
		FPy = ((FPy+FTy) * scale) + (lrmaj * VAR(seg120y)[loc120]);
		VAR(bcycle) += 1;
	}

  return TRUE; // Always return TRUE.    

}










