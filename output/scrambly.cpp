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
*/

#define MX_L  25 // set it lower on low memory machines
#define MX_L2 626 // set it lower on low memory machines
inline void mx_randflip(int idxmin, int idxmax, int seed, int* mxrdp);

// Must define this structure before we include apoplugin.h
typedef struct
{
	int scrambly_l;
	int scrambly_seed;
	int scrambly_byrows;
	double scrambly_cellsize;
	// *********** aux ***********
	int current_l;
	double cella;
	double cellainv;
	double mzcella;
	int mx_rd[MX_L2];
} Variables;

#include "apoplugin.h"
#include <stdlib.h> // for div and div_t

// Set the name of this plugin
APO_PLUGIN("scrambly");

// Define the Variables
APO_VARIABLES(
    VAR_INTEGER_RANGE(scrambly_l, 3, MX_L, 3),
    VAR_INTEGER(scrambly_seed, 51),
    VAR_INTEGER(scrambly_byrows, 0),
    VAR_REAL_CYCLE(scrambly_cellsize, 0.01, 1e20, 1.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    int curL=VAR(scrambly_l);
    int seed=VAR(scrambly_seed);
    int byrows=VAR(scrambly_byrows);
    int i,j;
    int LL, LL2;

    div_t divresult;
    // LL = curL*SGN(curL);

    LL = curL;

    if (LL < 3)          LL = 3; // min
    else if (LL > MX_L)  LL = MX_L; // max

    LL2 = LL*LL;
    VAR(current_l) = LL;

    if (seed >= 0 && seed <= 50) {
        for (j = 0; j < LL2; j++) {
            divresult = div(seed+j+1, LL2);
            VAR(mx_rd[j]) = divresult.rem; // shifts the matrix (interesting effect)
        }
    } else {
        for (j = 0; j < LL2; j++) {
            VAR(mx_rd[j]) = j;
        }

        if (byrows==0) {
           mx_randflip(0, LL2,seed,VAR(mx_rd)); // scrambles the whole matrix
        } else {
            for (j = 0; j < LL; j++) {
                mx_randflip(LL*j, LL*(1+j),seed+j,VAR(mx_rd)); // scrambles row by row
            }
        }
    }

    VAR(cella) = VAR(scrambly_cellsize) / VAR(current_l);
    VAR(mzcella) = 0.5*VAR(scrambly_cellsize);
    VAR(cellainv) = 1.0 / VAR(cella);
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double Vx = FTx;
    double Vy = FTy;
    int Ix;
    int Iy;
    int swp;
    div_t divresult;

    Vx += VAR(mzcella); Vy += VAR(mzcella);
    Vx *= VAR(cellainv); Vy *= VAR(cellainv);
	Ix = (int)floor( Vx );
	Iy = (int)floor( Vy );


	if (VAR(current_l) <= 0 || Ix<0 || Ix>=VAR(current_l) ||
       Iy<0 || Iy>=VAR(current_l)) {
    	FPx += VVAR * FTx;
    	FPy += VVAR * FTy;
    } else {
        Vx -= Ix; Vy -= Iy;
        // randomizing int parts:
        swp = Ix + VAR(current_l) * Iy;
        swp = (int)VAR(mx_rd[swp]);
        divresult = div(swp, VAR(current_l));
        Iy = divresult.quot; Ix = divresult.rem;

        // add int parts to fractional:
        Vx += Ix; Vy += Iy;
        Vx *= VAR(cella); Vy *= VAR(cella);
        Vx -= VAR(mzcella); Vy -= VAR(mzcella);
    	FPx += VVAR * Vx;
    	FPy += VVAR * Vy;
    }
	return TRUE;
}

inline void mx_randflip(int idxmin, int idxmax, int seed, int* mxrdp)
{
    div_t divresult;
    int i,j,prn,ridx;
    prn=1;

    for (j = idxmin; 1 ; j++) { // 1 means that I used a custom cycle break rule.
        prn = prn * 1103515245 + 12345;  // jwildfire source code :D
        prn = prn & 0xFFFF0000 |
            ((prn << 8) & 0xFF00 ) | ((prn >> 8) & 0x00FF ); // flippy bytes
        prn = (prn & 4)?prn-seed:prn^seed;
        prn = (prn <0)?-prn:prn; // neg are troubleful
        ridx = 1+j;
        if (idxmax > ridx) {
                   divresult = div(prn, idxmax-ridx);
                   ridx += divresult.rem;
        } else {
             //printf("STOP> %i %i %i\n",ridx, idxmin , idxmax);
             break;
        }
        //printf("!! %i ",ridx);
        i = mxrdp[ridx];
        mxrdp[ridx] = mxrdp[j];
        mxrdp[j] = i;
        //printf("-> %i\n",mx_rd[j]);
    }
    //printf("rflip end-> %i\n",mx_rd[j]);
}
