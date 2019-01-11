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

    double GlynnSim3_thickness,GlynnSim3_thickness2,GlynnSim3_pow;
    double GlynnSim3_radius,GlynnSim3_radius1,GlynnSim3_radius2;
    double GlynnSim3_contrast;
    double Gamma;

} Variables;

#include "apoplugin.h"


APO_PLUGIN("GlynnSim3");


APO_VARIABLES(

    VAR_REAL(GlynnSim3_radius,  1.0),
    VAR_REAL(GlynnSim3_thickness,  0.1),
    VAR_REAL(GlynnSim3_thickness2,  0.1),
    VAR_REAL_RANGE(GlynnSim3_contrast, 0.0, 1.0 , 0.5),
    VAR_REAL(GlynnSim3_pow,  1.5)

);


int PluginVarPrepare(Variation* vp)
{
    VAR(GlynnSim3_radius1)=VAR(GlynnSim3_radius)+VAR(GlynnSim3_thickness);
    VAR(GlynnSim3_radius2)=sqr(VAR(GlynnSim3_radius))/VAR(GlynnSim3_radius1);
    VAR(Gamma)=VAR(GlynnSim3_radius1)/(VAR(GlynnSim3_radius1)+VAR(GlynnSim3_radius2));

    return TRUE;
}

void Circle2(Variation* vp, double* X,double* Y)
{
   double sinPhi,cosPhi;
   double r=VAR(GlynnSim3_radius)+VAR(GlynnSim3_thickness)-VAR(Gamma)*random01();
   double Phi=2*M_PI*random01();
   fsincos(Phi,&sinPhi,&cosPhi);
   if (random01()<VAR(Gamma))
   {
      r=VAR(GlynnSim3_radius1);
   }
   else
   {
      r=VAR(GlynnSim3_radius2);
   }
   *X=r*cosPhi;
   *Y=r*sinPhi;
}

int PluginVarCalc(Variation* vp)
{

    double  r=sqrt(FTx*FTx+FTy*FTy);
    double X,Y,sinY,cosY,Alpha;
    Alpha = VAR(GlynnSim3_radius)/ r;


    if (r<VAR(GlynnSim3_radius1))
    {
       Circle2(vp, &X,&Y);
       FPx+=VVAR*X;
       FPy+=VVAR*Y;
    }
    else
    {
        if (random01()>VAR(GlynnSim3_contrast)*pow(Alpha,VAR(GlynnSim3_pow)))
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
