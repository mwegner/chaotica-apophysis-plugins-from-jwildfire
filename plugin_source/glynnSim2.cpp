/*
    Apophysis Plugin
    
    The structure of file and "apoplugin.h" are written by Joel Faber
    
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

#include "datahelpers.h"

typedef struct
{
    
    double glynnSim2_radius,glynnSim2_thickness;
    double glynnSim2_Phi1,glynnSim2_phi2,glynnSim2_phi10,glynnSim2_phi20;
    double glynnSim2_contrast,glynnSim2_pow;
    double gamma,delta;

GOODRAND_STRUCT;    
} Variables;

#include "apoplugin.h"


APO_PLUGIN("glynnSim2");


APO_VARIABLES(
    
    VAR_REAL(glynnSim2_radius,  1.0),
    VAR_REAL_RANGE(glynnSim2_thickness, 0.0, 1.0 , 0.1),
    VAR_REAL_RANGE(glynnSim2_contrast, 0.0, 1.0 , 0.5),
    VAR_REAL(glynnSim2_pow,  1.5),
    VAR_REAL(glynnSim2_Phi1,  0.0),
    VAR_REAL(glynnSim2_phi2,  360.0)
);


int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    VAR(glynnSim2_phi10)=M_PI*VAR(glynnSim2_Phi1)/180.0;
    VAR(glynnSim2_phi20)=M_PI*VAR(glynnSim2_phi2)/180.0;
    VAR(gamma)=VAR(glynnSim2_thickness)*(2*VAR(glynnSim2_radius)+VAR(glynnSim2_thickness))/(VAR(glynnSim2_radius)+VAR(glynnSim2_thickness));
    VAR(delta)=VAR(glynnSim2_phi20)-VAR(glynnSim2_phi10);
    VAR(glynnSim2_pow)=fabs(VAR(glynnSim2_pow));
    return TRUE;
}

void Circle(Variation* vp, double* X,double* Y)
{
   double sinPhi,cosPhi;
   double r=VAR(glynnSim2_radius)+VAR(glynnSim2_thickness)-VAR(gamma)*GOODRAND_01();
   double Phi=VAR(glynnSim2_phi10)+VAR(delta)*GOODRAND_01();
   fsincos(Phi,&sinPhi,&cosPhi);
   *X=r*cosPhi;
   *Y=r*sinPhi;
}

int PluginVarCalc(Variation* vp)
{
    
    double  r=sqrt(FTx*FTx+FTy*FTy);
    double X,Y,sinY,cosY,Alpha;
    Alpha = VAR(glynnSim2_radius)/ r;
    
    if (r<VAR(glynnSim2_radius))
    {
       Circle(vp, &X,&Y);
       FPx+=VVAR*X;
       FPy+=VVAR*Y;
       
    }
    else
    {
        if (GOODRAND_01()>VAR(glynnSim2_contrast)*pow(Alpha,VAR(glynnSim2_pow)))
        {
                                            
            FPx+=VVAR*FTx;
            FPy+=VVAR*FTy;
        }
        else
        {
            FPx+=VVAR*Alpha*Alpha*FTx;
            FPy+=VVAR*Alpha*Alpha*FTy;
        }
    }
        

    return TRUE;
}

