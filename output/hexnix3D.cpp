#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
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
	
	This plugin provides an hexagonal plate structure 
	for building snowflake designs. They can be built as a 
	single plate or a double plate where the two 
	are separated above and below each other on the Z axis
	This version is modified from hexaplay3D specifically to 
	support animated flame designing!
	Full rotation of the patterns has been added.
*/
/*
    The title of this plugin derives from Johannes Kepler's essay, "On the Six-Cornered Snowflake"
	He wrote in Latin, and the Latin word for "snowflake" is "nix"
    http://www.keplersdiscovery.com/SixCornered.html
*/

typedef struct
{                           
	double hexnix3D_majp;   // establishes 1 or 2 planes, and if 2, the distance between them
	double hexnix3D_scale;  // scales the effect of X and Y
	double hexnix3D_zlift;  // scales the effect of Z axis within the snowflake
	double hexnix3D_3side;  // scales the triangle within the hex - the 120 degree figure
	double seg60x[6];
	double seg60y[6];
	double seg120x[3];
	double seg120y[3];
	int rswtch;      //  for choosing between 6 or 3 segments to a plane
	int fcycle;      //  markers to count cycles... 
	int bcycle;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("hexnix3D");

// Define the Variables
APO_VARIABLES(
   	VAR_REAL(hexnix3D_majp, 1.0),
	VAR_REAL(hexnix3D_scale, 0.25),
	VAR_REAL(hexnix3D_zlift, 0.0),
	VAR_REAL(hexnix3D_3side, 0.667),
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{	
	
	/*  Any pre-calc operations
	    Set up two major angle systems
	*/
	
	VAR(rswtch) = trunc(random01()*3.0);  //  Chooses 6 or 3 nodes
	double hlift = sin(M_PI / 3.0);       // sin(60)
	VAR(fcycle) = 0;
	VAR(bcycle) = 0;
	VAR(seg60x)[0] =  1.0;   
	VAR(seg60x)[1] =  0.5;   
	VAR(seg60x)[2] =  -0.5;  
	VAR(seg60x)[3] =  -1.0;   
	VAR(seg60x)[4] =  -0.5;   
	VAR(seg60x)[5] =  0.5;    
	
	VAR(seg60y)[0] =  0.0;     
	VAR(seg60y)[1] =  -hlift;
	VAR(seg60y)[2] =  -hlift;
	VAR(seg60y)[3] =  0.0;
	VAR(seg60y)[4] =  hlift;
	VAR(seg60y)[5] =  hlift;
	
	VAR(seg120x)[0] = 0.0;                  // These settings cause the 3-node setting to 
	VAR(seg120x)[1] = cos(7.0*M_PI/6.0);    // rotate 30 degrees relative to the hex structure.
	VAR(seg120x)[2] = cos(11.0*M_PI/6.0);   // 
	
	VAR(seg120y)[0] = -1.0; 
    VAR(seg120y)[1] = 0.5;
    VAR(seg120y)[2] = 0.5;
		
  return TRUE; // Always return TRUE.    

}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    
	if(VAR(fcycle)>5)    // Resets the cyclic counting
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
	double smooth = 1.0;
	double smRotxFP = 0.0;
	double smRotyFP = 0.0;
	double smRotxFT = 0.0;
	double smRotyFT = 0.0;
	double gentleZ = 0.0;
	
	if(fabs(VVAR)<=0.5)
	{
	    smooth = VVAR*2.0;
	}
	else
	{
	    smooth = 1.0;
	}
	double boost = 0.0;  //  Boost is the separation distance between the two planes
	int posNeg = 1;
	int loc60;
	int loc120;
	double scale = VAR(hexnix3D_scale);   
	double scale3 = VAR(hexnix3D_3side);

	if (random01()< 0.5)
	{
	    posNeg = -1;
	}
	
	// Determine whether one or two major planes
	int majplane = 0;
	double abmajp = fabs(VAR(hexnix3D_majp));
	if (abmajp <= 1.0)
	{
	    majplane = 0; // 0= 1 plate active  1= transition to two plates active  2= defines two plates
		boost = 0.0;
	}
	else if(abmajp >1.0 && abmajp <2.0)
	    {
	        majplane = 1;
	    	boost = 0.0;
	    }
	    else
	    {
	        majplane = 2;
	        boost = (abmajp - 2.0) * 0.5; // distance above and below XY plane
	    }
		
	//  Creating Z factors relative to the planes	
	if(majplane == 0)
	{
	    FPz += smooth * FTz*scale*VAR(hexnix3D_zlift);   // single plate instructions
	}
	else if(majplane == 1 && VAR(hexnix3D_majp) < 0.0)   // Transition for reversing plates  because  majp is negative value
	    {
			if(VAR(hexnix3D_majp)<-1.0 && VAR(hexnix3D_majp)>= -2.0)
			{
				gentleZ = (abmajp-1.0);  //  Set transition smoothing values	0.00001 to 1.0		
			}
			else 
		    {
			   gentleZ = 1.0;   // full effect explicit default value
		    }
			          // Begin reverse transition - starts with FPz==FPz proceeds by gradual negative
			if(posNeg<0)
			{
			    FPz += -2.0*(FPz*gentleZ);  // gradually grows negative plate, in place, no boost,
			} 
		}
	if(majplane == 2 && VAR(hexnix3D_majp) < 0.0)     // Begin the splitting operation, animation transition is done
	{
	    if(posNeg>0)   //  The splitting operation positive side
		    {    
		        FPz +=(smooth*(FTz*scale*VAR(hexnix3D_zlift)+boost)); 
		    }
		    else   //  The splitting operation negative side
		    {     
		        FPz = (FPz-(2.0*smooth*FPz))+(smooth*posNeg*(FTz*scale*VAR(hexnix3D_zlift)+boost));
		    }
	}
	else    //  majp > 0.0       The splitting operation
	{	                    
	    FPz += smooth*(FTz*scale*VAR(hexnix3D_zlift)+(posNeg*boost));
	}
	
	
	if(VAR(rswtch) <= 1)         //  Occasion to build using 60 degree segments
	{
	    loc60 = trunc(random01()*6.0);  // random nodes selection
		//loc60 = VAR(fcycle);   // sequential nodes selection - seems to create artifacts that are progressively displaced
		smRotxFP = (smooth*scale*FPx*VAR(seg60x)[loc60])-(smooth*scale*FPy*VAR(seg60y)[loc60]);
		smRotyFP = (smooth*scale*FPy*VAR(seg60x)[loc60])+(smooth*scale*FPx*VAR(seg60y)[loc60]);
		smRotxFT = (FTx*smooth*scale*VAR(seg60x)[loc60])-(FTy*smooth*scale*VAR(seg60y)[loc60]);
		smRotyFT = (FTy*smooth*scale*VAR(seg60x)[loc60])+(FTx*smooth*scale*VAR(seg60y)[loc60]);
		
		FPx = FPx*(1.0-smooth) + smRotxFP + smRotxFT + smooth*lrmaj*VAR(seg60x)[loc60];
		FPy = FPy*(1.0-smooth) + smRotyFP + smRotyFT + smooth*lrmaj*VAR(seg60y)[loc60];
		
		VAR(fcycle) += 1;
	}
	
	else         // Occasion to build on 120 degree segments
	{
	    loc120 = trunc(random01()*3.0);  // random nodes selection
		//loc120 = VAR(bcycle);  // sequential nodes selection - seems to create artifacts that are progressively displaced
		smRotxFP = (smooth*scale*FPx*VAR(seg120x)[loc120])-(smooth*scale*FPy*VAR(seg120y)[loc120]);
		smRotyFP = (smooth*scale*FPy*VAR(seg120x)[loc120])+(smooth*scale*FPx*VAR(seg120y)[loc120]);
		smRotxFT = (FTx*smooth*scale*VAR(seg120x)[loc120])-(FTy*smooth*scale*VAR(seg120y)[loc120]);
		smRotyFT = (FTy*smooth*scale*VAR(seg120x)[loc120])+(FTx*smooth*scale*VAR(seg120y)[loc120]);
				
		FPx = FPx*(1.0-smooth) + smRotxFP + smRotxFT + smooth*lrmaj*scale3*VAR(seg120x)[loc120];		
		FPy = FPy*(1.0-smooth) + smRotyFP + smRotyFT + smooth*lrmaj*scale3*VAR(seg120y)[loc120];
		
		VAR(bcycle) += 1;
	}
	/*
	Rotations need to interchange smoothly between x and y values (pseudo code)
	new x = in_x*cos(r) - in_y*sin(r) + movedLoci_x;
	new y = in_y*cos(r) + in_x*sin(r) + movedLoci_y;
	*/
	
  return TRUE; // Always return TRUE.    

}



