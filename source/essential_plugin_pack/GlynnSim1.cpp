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


typedef struct
{
    double GlynnSim1_radius,GlynnSim1_radius1,GlynnSim1_Phi1;
    double GlynnSim1_thickness,GlynnSim1_contrast,GlynnSim1_pow;
    double GlynnSim1_X1,GlynnSim1_Y1;

} Variables;

#include "apoplugin.h"


APO_PLUGIN("GlynnSim1");


APO_VARIABLES(

    VAR_REAL(GlynnSim1_radius,  1.0),
    VAR_REAL(GlynnSim1_radius1,  0.1),
    VAR_REAL(GlynnSim1_Phi1,  0.0),
    VAR_REAL_RANGE(GlynnSim1_thickness, 0.0, 1.0 , 0.1),
    VAR_REAL(GlynnSim1_pow,  1.5),
    VAR_REAL_RANGE(GlynnSim1_contrast, 0.0, 1.0 , 0.5)

);


int PluginVarPrepare(Variation* vp)
{
    double sinPhi1,cosPhi1;
    fsincos(M_PI*VAR(GlynnSim1_Phi1)/180,&sinPhi1,&cosPhi1);
    VAR(GlynnSim1_X1)=VAR(GlynnSim1_radius)*cosPhi1;
    VAR(GlynnSim1_Y1)=VAR(GlynnSim1_radius)*sinPhi1;
    VAR(GlynnSim1_pow)=abs(VAR(GlynnSim1_pow));


    return TRUE;
}

void Circle(Variation* vp, double* X,double* Y)
{
   double sinPhi,cosPhi;
   double r=VAR(GlynnSim1_radius1)*(VAR(GlynnSim1_thickness)+(1-VAR(GlynnSim1_thickness))*random01());
   double Phi=2*M_PI*random01();
   fsincos(Phi,&sinPhi,&cosPhi);
   *X=r*cosPhi+VAR(GlynnSim1_X1);
   *Y=r*sinPhi+VAR(GlynnSim1_Y1);
}

int PluginVarCalc(Variation* vp)
{

    double  r=sqrt(FTx*FTx+FTy*FTy);
    double X,Y,Z,sinY,cosY,Alpha;
    Alpha = VAR(GlynnSim1_radius)/ r;



    if (r<VAR(GlynnSim1_radius))
    {  //object generation
       Circle(vp, &X,&Y);
       FPx+=VVAR*X;
       FPy+=VVAR*Y;
    }
    else
    {
        if (random01()>VAR(GlynnSim1_contrast)*pow(Alpha,VAR(GlynnSim1_pow)))
        {
            X=FTx;
            Y=FTy;
        }
        else
        {
            X=Alpha*Alpha*FTx;
            Y=Alpha*Alpha*FTy;
        }
        Z=sqr(X-VAR(GlynnSim1_X1))+sqr(Y-VAR(GlynnSim1_Y1));
        if (Z<VAR(GlynnSim1_radius1)*VAR(GlynnSim1_radius1))
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
