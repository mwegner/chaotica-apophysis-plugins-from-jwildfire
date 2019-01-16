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
    double glynnSim1_radius,glynnSim1_radius1,glynnSim1_phi1;
    double glynnSim1_thickness,glynnSim1_contrast,glynnSim1_pow;
    double glynnSim1_x1,glynnSim1_y1;

GOODRAND_STRUCT;    
} Variables;

#include "apoplugin.h"


APO_PLUGIN("glynnSim1");


APO_VARIABLES(
    
    VAR_REAL(glynnSim1_radius,  1.0),
    VAR_REAL(glynnSim1_radius1,  0.1),
    VAR_REAL(glynnSim1_phi1,  0.0),
    VAR_REAL_RANGE(glynnSim1_thickness, 0.0, 1.0 , 0.1),
    VAR_REAL(glynnSim1_pow,  1.5),
    VAR_REAL_RANGE(glynnSim1_contrast, 0.0, 1.0 , 0.5)
    
);


int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();

    double sinPhi1,cosPhi1;
    fsincos(M_PI*VAR(glynnSim1_phi1)/180,&sinPhi1,&cosPhi1);
    VAR(glynnSim1_x1)=VAR(glynnSim1_radius)*cosPhi1;
    VAR(glynnSim1_y1)=VAR(glynnSim1_radius)*sinPhi1;
    VAR(glynnSim1_pow)=abs(VAR(glynnSim1_pow));

    
    return TRUE;
}

void Circle(Variation* vp, double* X,double* Y)
{
     double sinPhi,cosPhi;
     double r=VAR(glynnSim1_radius1)*(VAR(glynnSim1_thickness)+(1-VAR(glynnSim1_thickness))*GOODRAND_01());
     double Phi=2*M_PI*GOODRAND_01();
     fsincos(Phi,&sinPhi,&cosPhi);
     *X=r*cosPhi+VAR(glynnSim1_x1);
     *Y=r*sinPhi+VAR(glynnSim1_y1);
}


int PluginVarCalc(Variation* vp)
{
    double  r=sqrt(FTx*FTx+FTy*FTy);
    double X,Y,Z,sinY,cosY,Alpha;
    Alpha = VAR(glynnSim1_radius)/ r;
    
    if (r<VAR(glynnSim1_radius))
    {  //object generation
       Circle(vp, &X,&Y);
       FPx+=VVAR*X;
       FPy+=VVAR*Y;
    }
    else
    {
        if (GOODRAND_01()>VAR(glynnSim1_contrast)*pow(Alpha,VAR(glynnSim1_pow)))
        {                                
            X=FTx;
            Y=FTy;
        }
        else
        {
            X=Alpha*Alpha*FTx;
            Y=Alpha*Alpha*FTy;
        }
        Z=sqr(X-VAR(glynnSim1_x1))+sqr(Y-VAR(glynnSim1_y1));
        if (Z<VAR(glynnSim1_radius1)*VAR(glynnSim1_radius1))
        {  //object generation
           Circle(vp, &X,&Y);
           FPx+=VVAR*X;
           FPy+=VVAR*Y;
       }
       else
       {
           FPx+=VVAR*X;
           FPy+=VVAR*Y;
       }
    }
        

    return TRUE;
}

