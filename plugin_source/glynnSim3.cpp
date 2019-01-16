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
    
    double glynnSim3_thickness,glynnSim3_thickness2,glynnSim3_pow;
    double glynnSim3_radius,glynnSim3_radius1,glynnSim3_radius2;
    double glynnSim3_contrast;
    double gamma;

GOODRAND_STRUCT;    
} Variables;

#include "apoplugin.h"


APO_PLUGIN("glynnSim3");


APO_VARIABLES(
    
    VAR_REAL(glynnSim3_radius,  1.0),
    VAR_REAL(glynnSim3_thickness,  0.1),
    VAR_REAL(glynnSim3_thickness2,  0.1),
    VAR_REAL_RANGE(glynnSim3_contrast, 0.0, 1.0 , 0.5),
    VAR_REAL(glynnSim3_pow,  1.5)
    
);

void Circle2(Variation* vp, double* X,double* Y)
{
   double sinPhi,cosPhi;
   double r=VAR(glynnSim3_radius)+VAR(glynnSim3_thickness)-VAR(gamma)*GOODRAND_01();
   double Phi=2*M_PI*GOODRAND_01();
   fsincos(Phi,&sinPhi,&cosPhi);
   if (GOODRAND_01()<VAR(gamma))
   {
      r=VAR(glynnSim3_radius1);
   }
   else
   {
      r=VAR(glynnSim3_radius2);
   }
   *X=r*cosPhi;
   *Y=r*sinPhi;
}

int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    VAR(glynnSim3_radius1)=VAR(glynnSim3_radius)+VAR(glynnSim3_thickness);
    VAR(glynnSim3_radius2)=sqr(VAR(glynnSim3_radius))/VAR(glynnSim3_radius1);
    VAR(gamma)=VAR(glynnSim3_radius1)/(VAR(glynnSim3_radius1)+VAR(glynnSim3_radius2));

    return TRUE;
}


int PluginVarCalc(Variation* vp)
{
    double  r=sqrt(FTx*FTx+FTy*FTy);
    double X,Y,sinY,cosY,Alpha;
    Alpha = VAR(glynnSim3_radius)/ r;
    
    
    if (r<VAR(glynnSim3_radius1))
    {     
       Circle2(vp, &X,&Y);
       FPx+=VVAR*X;
       FPy+=VVAR*Y; 
    }
    else
    {
        if (GOODRAND_01()>VAR(glynnSim3_contrast)*pow(Alpha,VAR(glynnSim3_pow)))
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

