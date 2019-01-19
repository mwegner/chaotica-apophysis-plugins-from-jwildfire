/*
    Apophysis Plugin

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    fixed up for 64-bit/etc by mwegner
*/

#include "datahelpers.h"

typedef struct
{
    
    int nblur_numEdges, nblur_numStripes;
    double nblur_ratioStripes, nblur_ratioComplement;
    int nblur_equalBlur;
    double nblur_ratioHole;
    int nblur_exactCalc;
    int nblur_adjustToLinear;
    int nblur_circumCircle;
    double nblur_highlightEdges;    
    double midAngle, angStripes, angStart;
    double tan90_m_2, sina, cosa;
    int hasStripes, negStripes;
    //**********Variables for speed up***********
    double speedCalc1, speedCalc2;
    double maxStripes;
    double arc_tan1, arc_tan2;    
        
} Variables;

#include "apoplugin.h"


APO_PLUGIN("nBlur");

APO_VARIABLES(
    
    VAR_INTEGER(nblur_numEdges, 3),
    VAR_INTEGER(nblur_numStripes, 0),
    VAR_REAL_RANGE(nblur_ratioStripes, 0.0, 2.0, 1.0),
    VAR_REAL_RANGE(nblur_ratioHole, 0.0, 1.0, 0.0),
    VAR_INTEGER_RANGE(nblur_circumCircle, FALSE, TRUE, FALSE),
    VAR_INTEGER_RANGE(nblur_adjustToLinear, FALSE, TRUE, TRUE),
    VAR_INTEGER_RANGE(nblur_equalBlur, FALSE, TRUE, TRUE),
    VAR_INTEGER_RANGE(nblur_exactCalc, FALSE, TRUE, FALSE),
    VAR_REAL(nblur_highlightEdges, 1.0)
    
        
);


int PluginVarPrepare(Variation* vp)
{
    //**********Prepare edge related stuff***********
    if(VAR(nblur_numEdges)<3) VAR(nblur_numEdges) = 3;
    
    //*********Prepare stripes related stuff*********
    if(VAR(nblur_numStripes)!=0)
    {
        VAR(hasStripes) = TRUE;
        if(VAR(nblur_numStripes)<0)
        {
            VAR(negStripes) = TRUE;
            VAR(nblur_numStripes) *= -1;
        }
        else
        {
            VAR(negStripes) = FALSE;
        }
    }
    else
    {
        VAR(hasStripes) = FALSE;
        VAR(negStripes) = FALSE;
    }

    //**********Prepare angle related stuff**********
    VAR(midAngle)   = M_2PI / (double)VAR(nblur_numEdges);
    if(VAR(hasStripes)==TRUE)
    {
        VAR(angStripes)      = VAR(midAngle)/(double)(2*VAR(nblur_numStripes));
        VAR(angStart)        = VAR(angStripes)/2.0;
        VAR(nblur_ratioComplement) = 2.0 - VAR(nblur_ratioStripes);
    }
    
    //**********Prepare hole related stuff***********
    if((VAR(nblur_ratioHole)>0.95)&&(VAR(nblur_exactCalc)==TRUE)&&(VAR(nblur_circumCircle)==FALSE)) VAR(nblur_ratioHole) = 0.95;
    
    //*********Prepare edge calculation related stuff*********
    VAR(tan90_m_2)  = tan(M_PI_2 + VAR(midAngle) / 2.0);
    fsincos((VAR(midAngle)/2.0), &VAR(sina), &VAR(cosa));
    
    //*********Prepare factor of adjustment of interpolated calculation*********
    if(VAR(nblur_highlightEdges)<=0.1) VAR(nblur_highlightEdges) = 0.1;
    
    //*********Adjustment of width of shape*********
    if(VAR(nblur_adjustToLinear)==TRUE)
    {
        if((VAR(nblur_numEdges)%4)==0)
        {
            VVAR /= sqrt(2.0 - 2.0 * cos(VAR(midAngle)*((double)VAR(nblur_numEdges)/2.0-1.0)))/2.0;
        }
        else
        {
            VVAR /= sqrt(2.0 - 2.0 * cos(VAR(midAngle)*floor(((double)VAR(nblur_numEdges)/2.0))))/2.0;
        }
    }
    
    //*********Prepare circumCircle-calculation*********
    if(VAR(nblur_circumCircle)==TRUE)
    {
        VAR(nblur_exactCalc)==FALSE;
        VAR(nblur_highlightEdges) = 0.1;
    }
    
    //*********Prepare speed up related stuff*********
    VAR(speedCalc1) = VAR(nblur_ratioComplement)*VAR(angStart);
    VAR(speedCalc2) = VAR(nblur_ratioStripes)*VAR(angStart);
    VAR(maxStripes) = 2*VAR(nblur_numStripes);
    if(VAR(negStripes)==FALSE)
    {
        VAR(arc_tan1) = (13.0/pow(VAR(nblur_numEdges),1.3))*VAR(nblur_highlightEdges);
        VAR(arc_tan2) = (2.0*atan(VAR(arc_tan1)/(-2.0)));
    }
    else
    {
        VAR(arc_tan1) = (7.5/pow(VAR(nblur_numEdges),1.3))*VAR(nblur_highlightEdges);
        VAR(arc_tan2) = (2.0*atan(VAR(arc_tan1)/(-2.0)));
    }
    
    return TRUE; 
}

void randXY(Variation* vp, double &x, double &y, double &xTmp, double &yTmp, double &lenOuterEdges, double &lenInnerEdges, double &angXY, double &lenXY, double &ranTmp, double &angTmp, double &angMem, double &rotTmp, double &ratioTmp, double &ratioTmpNum, double &ratioTmpDen, double &step, double &speedCalcTmp, int &count)
{
    if(VAR(nblur_exactCalc)==TRUE)
    {
        angXY = GOODRAND_01() * M_2PI;
    }
    else
    {
        angXY = (atan(VAR(arc_tan1)*(GOODRAND_01()-0.5))/VAR(arc_tan2)+0.5 + (double)(GOODRAND_0X(VAR(nblur_numEdges)))) * VAR(midAngle) ;
    }
    fsincos(angXY, &x, &y);
    angMem = angXY;

    while(angXY>VAR(midAngle))
    {
        angXY -= VAR(midAngle);
    }

    //********Begin of xy-calculation of radial stripes********
    if(VAR(hasStripes)==TRUE)
    {
        angTmp = VAR(angStart);
        count = 0;

        while(angXY>angTmp)
        {
            angTmp += VAR(angStripes);
            if(angTmp>VAR(midAngle)) angTmp = VAR(midAngle);
            count++;
        }

        if(angTmp!=VAR(midAngle)) angTmp -= VAR(angStart);

        if(VAR(negStripes)==FALSE)
        {
            if((count%2)==1)
            {
                if(angXY>angTmp)
                {
                    angXY =  angXY + VAR(angStart);
                    angMem = angMem + VAR(angStart);
                    fsincos(angMem, &x, &y);
                    angTmp += VAR(angStripes);
                    count++;
                }
                else
                {
                    angXY  = angXY - VAR(angStart);
                    angMem = angMem - VAR(angStart);
                    fsincos(angMem, &x, &y);
                    angTmp -= VAR(angStripes);
                    count--;
                }
            }
            if(((count%2)==0)&&(VAR(nblur_ratioStripes)>1.0))
            {
                if((angXY>angTmp)&&(count!=VAR(maxStripes)))
                {
                    angMem = angMem - angXY + angTmp + (angXY-angTmp)/VAR(angStart) * VAR(nblur_ratioStripes) * VAR(angStart);
                    angXY  = angTmp + (angXY-angTmp)/VAR(angStart) * VAR(nblur_ratioStripes) * VAR(angStart);
                    fsincos(angMem, &x, &y);
                }
                else
                {
                    angMem = angMem - angXY + angTmp - (angTmp-angXY)/VAR(angStart) * VAR(nblur_ratioStripes) * VAR(angStart);
                    angXY  = angTmp + (angXY-angTmp)/VAR(angStart) * VAR(nblur_ratioStripes) * VAR(angStart);
                    fsincos(angMem, &x, &y);
                }
            }
            if(((count%2)==0)&&(VAR(nblur_ratioStripes)<1.0))
            {
                if((fabs(angXY-angTmp)>VAR(speedCalc2))&&(count!=(VAR(maxStripes))))
                {
                    if((angXY-angTmp)>VAR(speedCalc2))
                    {
                        ratioTmpNum = (angXY-(angTmp+VAR(speedCalc2)))*VAR(speedCalc2);
                        ratioTmpDen = VAR(angStart)-VAR(speedCalc2);
                        ratioTmp    = ratioTmpNum/ratioTmpDen;
                        fsincos((angMem-angXY+angTmp+ratioTmp), &x, &y);
                        angXY = angTmp + ratioTmp;
                    }
                    if((angTmp-angXY)>VAR(speedCalc2))
                    {
                        ratioTmpNum = ((angTmp-VAR(speedCalc2)-angXY))*VAR(speedCalc2);
                        ratioTmpDen = VAR(angStart)-VAR(speedCalc2);
                        ratioTmp    = ratioTmpNum/ratioTmpDen;
                        fsincos((angMem-angXY+angTmp-ratioTmp), &x, &y);
                        angXY = angTmp - ratioTmp;
                    }
                }
                if(count==VAR(maxStripes))
                {
                    if((angTmp-angXY)>VAR(speedCalc2))
                    {
                        ratioTmpNum = ((angTmp-VAR(speedCalc2)-angXY))*VAR(speedCalc2);
                        ratioTmpDen = VAR(angStart)-VAR(speedCalc2);
                        ratioTmp    = ratioTmpNum/ratioTmpDen;
                        fsincos((angMem-angXY+angTmp-ratioTmp), &x, &y);
                        angXY = angTmp - ratioTmp;
                    }
                }
            }
        }
        else
        {
            //********Change ratio and ratioComplement********
            ratioTmp = VAR(nblur_ratioStripes);
            VAR(nblur_ratioStripes) = VAR(nblur_ratioComplement);
            VAR(nblur_ratioComplement) = ratioTmp;
            speedCalcTmp = VAR(speedCalc1);
            VAR(speedCalc1) = VAR(speedCalc2);
            VAR(speedCalc2) = speedCalcTmp;
            //************************************************
            if((count%2)==0)
            {
                if((angXY>angTmp)&&(count!=VAR(maxStripes)))
                {
                    angXY =  angXY + VAR(angStart);
                    angMem = angMem + VAR(angStart);
                    fsincos(angMem, &x, &y);
                    angTmp += VAR(angStripes);
                    count++;
                }
                else
                {
                    angXY  = angXY - VAR(angStart);
                    angMem = angMem - VAR(angStart);
                    fsincos(angMem, &x, &y);
                    angTmp -= VAR(angStripes);
                    count--;
                }
            }
            if(((count%2)==1)&&(VAR(nblur_ratioStripes)>1.0))
            {
                if((angXY>angTmp)&&(count!=VAR(maxStripes)))
                {
                    angMem = angMem - angXY + angTmp + (angXY-angTmp)/VAR(angStart) * VAR(nblur_ratioStripes) * VAR(angStart);
                    angXY  = angTmp + (angXY-angTmp)/VAR(angStart) * VAR(nblur_ratioStripes) * VAR(angStart);
                    fsincos(angMem, &x, &y);
                }
                else
                {
                    angMem = angMem - angXY + angTmp - (angTmp-angXY)/VAR(angStart) * VAR(nblur_ratioStripes) * VAR(angStart);
                    angXY  = angTmp + (angXY-angTmp)/VAR(angStart) * VAR(nblur_ratioStripes) * VAR(angStart);
                    fsincos(angMem, &x, &y);
                }
            }
            if(((count%2)==1)&&(VAR(nblur_ratioStripes)<1.0))
            {
                if((fabs(angXY-angTmp)>VAR(speedCalc2))&&(count!=VAR(maxStripes)))
                {
                    if((angXY-angTmp)>VAR(speedCalc2))
                    {
                        ratioTmpNum = (angXY-(angTmp+VAR(speedCalc2)))*VAR(speedCalc2);
                        ratioTmpDen = VAR(angStart)-VAR(speedCalc2);
                        ratioTmp    = ratioTmpNum/ratioTmpDen;
                        fsincos((angMem-angXY+angTmp+ratioTmp), &x, &y);
                        angXY = angTmp + ratioTmp;
                    }
                    if((angTmp-angXY)>VAR(speedCalc2))
                    {
                        ratioTmpNum = ((angTmp-VAR(speedCalc2)-angXY))*VAR(speedCalc2);
                        ratioTmpDen = VAR(angStart)-VAR(speedCalc2);
                        ratioTmp    = ratioTmpNum/ratioTmpDen;
                        fsincos((angMem-angXY+angTmp-ratioTmp), &x, &y);
                        angXY = angTmp - ratioTmp;
                    }
                }
                if(count==VAR(maxStripes))
                {
                    angTmp = VAR(midAngle);
                    if((angTmp-angXY)>VAR(speedCalc2))
                    {
                        ratioTmpNum = ((angTmp-VAR(speedCalc2)-angXY))*VAR(speedCalc2);
                        ratioTmpDen = VAR(angStart)-VAR(speedCalc2);
                        ratioTmp    = ratioTmpNum/ratioTmpDen;
                        fsincos((angMem-angXY+angTmp-ratioTmp), &x, &y);
                        angXY = angTmp - ratioTmp;
                    }
                }
            }
            //********Restore ratio and ratioComplement*******
            ratioTmp = VAR(nblur_ratioStripes);
            VAR(nblur_ratioStripes) = VAR(nblur_ratioComplement);
            VAR(nblur_ratioComplement) = ratioTmp;
            speedCalcTmp = VAR(speedCalc1);
            VAR(speedCalc1) = VAR(speedCalc2);
            VAR(speedCalc2) = speedCalcTmp;
            //************************************************
        }
    }
    //********End of xy-calculation of radial stripes********

    //********Begin of calculation of edge limits********
    xTmp = VAR(tan90_m_2) / (VAR(tan90_m_2) - tan(angXY));
    yTmp = xTmp * tan(angXY);
    lenOuterEdges = sqrt(xTmp*xTmp+yTmp*yTmp);
    //*********End of calculation of edge limits********

    //********Begin of radius-calculation (optionally hole)********
    if(VAR(nblur_exactCalc)==TRUE)
    {
        if(VAR(nblur_equalBlur)==TRUE) ranTmp = sqrt(GOODRAND_01());
        else                        ranTmp = GOODRAND_01();
    }
    else
    {
        if(VAR(nblur_circumCircle)==TRUE)
        {
            if(VAR(nblur_equalBlur)==TRUE) ranTmp = sqrt(GOODRAND_01());
            else                        ranTmp = GOODRAND_01();
        }
        else
        {
            if(VAR(nblur_equalBlur)==TRUE) ranTmp = sqrt(GOODRAND_01()) * lenOuterEdges;
            else                        ranTmp = GOODRAND_01() * lenOuterEdges;
        }
    }
    lenInnerEdges = VAR(nblur_ratioHole)*lenOuterEdges;

    if(VAR(nblur_exactCalc)==FALSE)
    {
        if(ranTmp<lenInnerEdges)
        {
            if(VAR(nblur_circumCircle)==TRUE)
            {
                if(VAR(nblur_equalBlur==TRUE)) ranTmp = lenInnerEdges + sqrt(GOODRAND_01()) * (1.0 - lenInnerEdges + EPS);
                else                        ranTmp = lenInnerEdges + GOODRAND_01() * (1.0 - lenInnerEdges + EPS);
            }
            else
            {
                if(VAR(nblur_equalBlur==TRUE)) ranTmp = lenInnerEdges + sqrt(GOODRAND_01()) * (lenOuterEdges - lenInnerEdges);
                else                        ranTmp = lenInnerEdges + GOODRAND_01()       * (lenOuterEdges - lenInnerEdges);
            }
        }
    }

    //if(VAR(hasStripes)==TRUE) ranTmp = pow(ranTmp,0.75);
    x *= ranTmp;
    y *= ranTmp;
    lenXY = sqrt(x*x+y*y);
    //*********End of radius-calculation (optionally hole)*********
}

int PluginVarCalc(Variation* vp)
{
    double x, y;
    double xTmp, yTmp, lenOuterEdges, lenInnerEdges;
    double angXY, lenXY;
    double ranTmp, angTmp, angMem, rotTmp;
    double ratioTmp, ratioTmpNum, ratioTmpDen, step;
    double speedCalcTmp;
    int    count;

    randXY(vp, x, y, xTmp, yTmp, lenOuterEdges, lenInnerEdges, angXY, lenXY, ranTmp, angTmp, angMem, rotTmp,
            ratioTmp, ratioTmpNum, ratioTmpDen, step, speedCalcTmp, count);

    //********Exact calculation slower - interpolated calculation faster********
    if((VAR(nblur_exactCalc)==TRUE)&&(VAR(nblur_circumCircle)==FALSE))
    {
        while((lenXY<lenInnerEdges)||(lenXY>lenOuterEdges))         randXY(vp, x, y, xTmp, yTmp, lenOuterEdges, lenInnerEdges, angXY, lenXY, ranTmp, angTmp, angMem, rotTmp,
                                                                           ratioTmp, ratioTmpNum, ratioTmpDen, step, speedCalcTmp, count);
    }
    if((VAR(nblur_exactCalc)==TRUE)&&(VAR(nblur_circumCircle)==TRUE))
    {
        while(lenXY<lenInnerEdges)        randXY(vp, x, y, xTmp, yTmp, lenOuterEdges, lenInnerEdges, angXY, lenXY, ranTmp, angTmp, angMem, rotTmp,
                                                 ratioTmp, ratioTmpNum, ratioTmpDen, step, speedCalcTmp, count);
    }
    xTmp = x;
    yTmp = y;
    
    //**************************************************************************
    
    //********Begin of horizontal adjustment (rotation)********
    x = VAR(cosa)*xTmp - VAR(sina)*yTmp;
    y = VAR(sina)*xTmp + VAR(cosa)*yTmp;
    //*********End of horizontal adjustment (rotation)*********
    
    FPx += VVAR * x;
    FPy += VVAR * y;

    return TRUE;
}
