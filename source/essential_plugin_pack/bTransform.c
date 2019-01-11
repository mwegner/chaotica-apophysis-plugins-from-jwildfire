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
*/

typedef struct
{
    double bTransform_rotate;
    int bTransform_power;
    int bT_pow;
    double bTransform_move;
    double bTransform_split;
} Variables;

#include "apoplugin.h"

/* Place plugin name here */
APO_PLUGIN("bTransform");

APO_VARIABLES(
    VAR_REAL(bTransform_rotate, 0.0),
    VAR_INTEGER_RANGE(bTransform_power, 1, INT_MAX,1),
    VAR_REAL(bTransform_move, 0.0),
    VAR_REAL(bTransform_split, 0.0)
);

/* This function is called once before the calculation starts.
   Prepare everything you need to do only once here.
   You must call the argument "vp"
*/
int PluginVarPrepare(Variation* vp)
{
    // must return true
    return TRUE; 
}

/* This function is called during calculation.
   You must call the argument "vp"
*/
int PluginVarCalc(Variation* vp)
{
    double tau, sigma;
    double temp;
    double cosht,sinht;
    double sins, coss;
    
    tau = 0.5 * ( log( sqr(FTx + 1.0) + sqr(FTy) ) - log( sqr(FTx - 1.0) + sqr(FTy)) ) / VAR(bTransform_power) + VAR(bTransform_move);	
	sigma = M_PI - atan2(FTy, FTx + 1.0) - atan2(FTy, 1.0 - FTx) + VAR(bTransform_rotate);
    sigma = sigma / VAR(bTransform_power) + M_2PI / VAR(bTransform_power) * floor(random01() * VAR(bTransform_power));

    if( FTx >= 0.0)
    	tau += VAR(bTransform_split);
    else
    	tau -= VAR(bTransform_split);
    
    sinhcosh(tau, &sinht, &cosht);
	fsincos(sigma, &sins, &coss);
    temp = cosht - coss;
    FPx += VVAR * sinht / temp;
    FPy += VVAR * sins / temp;
    
    // must return true
    return TRUE;
}
