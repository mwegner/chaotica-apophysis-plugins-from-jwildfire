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
    
    I've used some ideas and routines from the beautiful introduction to Perlin noise by Hugo Elias
    http://freespace.virgin.net/hugo.elias/models/m_perlin.htm
*/

// Must define this structure before we include apoplugin.h
typedef struct
{
    double circleLinear_Sc, circleLinear_K,circleLinear_Reverse,circleLinear_Dens1,circleLinear_Dens2;
    double circleLinear_X,circleLinear_Y;
    int circleLinear_Seed;
    
    

    
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("circleLinear");

// Define the Variables
APO_VARIABLES(
    
    VAR_REAL(circleLinear_Sc,1.0),
    VAR_REAL(circleLinear_K,0.5),
    VAR_REAL(circleLinear_Dens1,0.5),
    VAR_REAL(circleLinear_Dens2,0.5),
    VAR_REAL(circleLinear_Reverse,1.0),
    VAR_REAL(circleLinear_X,10.0),
    VAR_REAL(circleLinear_Y,10.0),
    VAR_INTEGER(circleLinear_Seed,0)
    
  
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
    double X, Y, Z,Z1, U, V;
    int M,N;
    
        M=floor(0.5*FTx/VAR(circleLinear_Sc));
        N=floor(0.5*FTy/VAR(circleLinear_Sc));
        X=FTx-(M*2+1)*VAR(circleLinear_Sc);
        Y=FTy-(N*2+1)*VAR(circleLinear_Sc);
        U=sqrt(X*X+Y*Y);
        V=(0.3+0.7*DiscretNoise2(M+10,N+3))*VAR(circleLinear_Sc);                
        Z1=DiscretNoise2(M+VAR(circleLinear_Seed),N);
    if ((Z1<VAR(circleLinear_Dens1))&&(U<V))
    {
        if (VAR(circleLinear_Reverse)>0)
        {
           if (Z1<VAR(circleLinear_Dens1)*VAR(circleLinear_Dens2))
           {
              X=VAR(circleLinear_K)*X;
              Y=VAR(circleLinear_K)*Y;
           }
           else
           {
              Z=V/U*(1-VAR(circleLinear_K))+VAR(circleLinear_K);
              X=Z*X;
              Y=Z*Y;
           }
        }
        else
        {
           if (Z1>VAR(circleLinear_Dens1)*VAR(circleLinear_Dens2))
           {
              X=VAR(circleLinear_K)*X;
              Y=VAR(circleLinear_K)*Y;
           }
           else
           {
              Z=V/U*(1-VAR(circleLinear_K))+VAR(circleLinear_K);
              X=Z*X;
              Y=Z*Y;
           }
        }
    }
    
                         
    FPx+= VVAR*(X+(M*2+1)*VAR(circleLinear_Sc));
    FPy+= VVAR*(Y+(N*2+1)*VAR(circleLinear_Sc));
            

    return TRUE;
}

