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
*/

// Must define this structure before we include apoplugin.h
typedef struct
{
	double jac_sn_k;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("jac_sn");

// Define the Variables
APO_VARIABLES(
    VAR_REAL_RANGE(jac_sn_k, -1.0, 1.0, 0.5)
);

void Jacobi_elliptic(double uu,double emmc,double *sn,double *cn,double *dn)
 {
    // Code is taken from IROIRO++ library,
    // released under CC share-alike license.
    
    // less accurate for faster rendering (still very precise)
    double const CA = 0.0003; // (The accuracy is the square of CA.)
    
    double a,b,c,d,em[13],en[13];
    int bo;
    int l;
    int ii;
    int i;
    // LOGICAL bo
    
    // main
    double emc = emmc;
    double u = uu;
    
    if(emc != 0.0) {
        bo = 0;
        if(emc < 0.0) bo = 1;
        
        if(bo != 0) {
            d = 1.0 - emc;
            emc = - emc/d;
            d = sqrt(d);
            u = d*u;
        }
        a = 1.0;
        *dn = 1.0;
        
        // for(i=0; i<13; i++){ original
        for(i=0; i<8; i++){
            l = i;
            em[i] = a;
            emc = sqrt(emc);
            en[i] = emc;
            c = 0.5*(a + emc);
            if(fabs(a-emc) <= CA*a) goto continued;
            emc = a * emc;
            a = c;
        }
        
        continued:
        u = c*u;
        *sn = sin(u);
        *cn = cos(u);
        
        if(*sn == 0.0) goto continued2;
        
        a = *cn/ *sn;
        c = a * c;
        for(ii=l; ii >= 0; --ii){
            b = em[ii];
            a = c * a;
            c = *dn * c;
            *dn = (en[ii] + a)/(b + a);
            a = c/b;
        }
        
        a = 1.0/sqrt(c*c + 1.0);
        if (*sn < 0.0) (*sn) = -a;
        else *sn = a;
        *cn = c * (*sn);
        
        continued2:
        if(bo != 0) {
            a = *dn;
            *dn = *cn;
            *cn = a;
            *sn = (*sn)/d;
        }
    } else {
        *cn = 1.0/cosh(u);
        *dn = *cn;
        (*sn) = tanh(u);
    }
}

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    // Always return TRUE.
    return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double snx,cnx,dnx;
    double sny,cny,dny;
    double NumX,NumY,Denom;
       
    Jacobi_elliptic(FTx,   VAR(jac_sn_k)   ,&snx,&cnx,&dnx);
    Jacobi_elliptic(FTy, 1.0-VAR(jac_sn_k) ,&sny,&cny,&dny);
    
    NumX = snx*dny;
    NumY = cnx*dnx*cny*sny;
    Denom = sqr(snx)*sqr(sny)*VAR(jac_sn_k) + sqr(cny);
    Denom = VVAR / (EPS + Denom);
	FPx += Denom * NumX;
	FPy += Denom * NumY;

    return TRUE;
}
