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
    
    I've used some ideas and routines from the beautiful introduction to Perlin noise by Hugo Elias
    http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
*/

// Must define this structure before we include apoplugin.h
typedef struct
{
    double circleRand_Sc,circleRand_Dens;
    double circleRand_X,circleRand_Y;
    int circleRand_Seed;
   
    

    
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("circleRand");

// Define the Variables
APO_VARIABLES(
    
    VAR_REAL(circleRand_Sc,1.0),
    VAR_REAL(circleRand_Dens,0.5),
    VAR_REAL(circleRand_X,10.0),
    VAR_REAL(circleRand_Y,10.0),
    VAR_INTEGER(circleRand_Seed,0)
    
  
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    

    // Always return TRUE.
    return TRUE;
}


double DiscretNoise2 (int X, int Y)
{
    int n = X + Y * 57;
    n = (n<<13) ^ n;
    return( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff)*AM;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{           
    double X, Y, Z, U, V;
    int M,N;
    
    do
    {
        
        X=VAR(circleRand_X)*(1-2*random01());
        Y=VAR(circleRand_Y)*(1-2*random01());
        M=floor(0.5*X/VAR(circleRand_Sc));
        N=floor(0.5*Y/VAR(circleRand_Sc));
        X=X-(M*2+1)*VAR(circleRand_Sc);
        Y=Y-(N*2+1)*VAR(circleRand_Sc);
        U=sqrt(X*X+Y*Y);
                        
    }
    while ((DiscretNoise2(M+VAR(circleRand_Seed),N)>VAR(circleRand_Dens))||(U>(0.3+0.7*DiscretNoise2(M+10,N+3))*VAR(circleRand_Sc)));
                         
    FPx+= VVAR*(X+(M*2+1)*VAR(circleRand_Sc));
    FPy+= VVAR*(Y+(N*2+1)*VAR(circleRand_Sc));
            

    return TRUE;
}

