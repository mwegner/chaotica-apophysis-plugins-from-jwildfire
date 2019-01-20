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
    double CircleTrans1_Sc,CircleTrans1_Dens;
    double CircleTrans1_X,CircleTrans1_Y;
    int CircleTrans1_Seed;
    
    

    
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("CircleTrans1");

// Define the Variables
APO_VARIABLES(
    VAR_REAL(CircleTrans1_Sc,1.0),
    VAR_REAL(CircleTrans1_Dens,0.5),
    VAR_REAL(CircleTrans1_X,10.0),
    VAR_REAL(CircleTrans1_Y,10.0),
    VAR_INTEGER(CircleTrans1_Seed,0)
    
  
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

void CircleR(Variation* vp, double*Ux, double*Vy)
{
    double X, Y, s,c,alpha, U;
    int M,N;

    do
    {
        
        X=fabs(VAR(CircleTrans1_X))*(1-2*random01());
        Y=fabs(VAR(CircleTrans1_Y))*(1-2*random01());
        M=floor(0.5*X/VAR(CircleTrans1_Sc));
        N=floor(0.5*Y/VAR(CircleTrans1_Sc));
        alpha=2*M_PI*random01();
        fsincos(alpha,&s,&c);
        U=0.3+0.7*DiscretNoise2(M+10,N+3);
        X=U*c;
        Y=U*s;
                        
    }
    while (DiscretNoise2(M+VAR(CircleTrans1_Seed),N)>VAR(CircleTrans1_Dens));
                         
        *Ux=X+(M*2+1)*VAR(CircleTrans1_Sc);
        *Vy=Y+(N*2+1)*VAR(CircleTrans1_Sc);
}

void Trans( double A, double B, double X, double Y, double* X1, double* Y1)
{
  *X1= (X-A)*0.5+A;
  *Y1= (Y-B)*0.5+B;

}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double Ux,Uy,U,X,Y,Z;
    int M,N;
    
    Trans(VAR(CircleTrans1_X),VAR(CircleTrans1_Y),FTx, FTy, &Ux, &Uy);
    
    
    M=floor(0.5*Ux/VAR(CircleTrans1_Sc));
    N=floor(0.5*Uy/VAR(CircleTrans1_Sc));
    X=Ux-(M*2+1)*VAR(CircleTrans1_Sc);
    Y=Uy-(N*2+1)*VAR(CircleTrans1_Sc);
    U=sqrt(X*X+Y*Y);
    
    if ((DiscretNoise2(M+VAR(CircleTrans1_Seed),N)>VAR(CircleTrans1_Dens))||(U>(0.3+0.7*DiscretNoise2(M+10,N+3))*VAR(CircleTrans1_Sc)))
                                  
    {
         Ux=Ux;
         Uy=Uy;
    }
    else
    {
        CircleR(vp, &Ux,&Uy);
    }
    FPx +=VVAR*Ux;
    FPy +=VVAR*Uy;
    return TRUE;
}

