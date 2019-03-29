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

// Must define this structure before we include apoplugin.h
typedef struct
{
	double checks_x;
	double checks_y;
	double checks_size;
	double checks_rnd;

	double cs, cx, cy, ncx, ncy;

} Variables;

#include "apoplugin.h"


// Set the name of this plugin
APO_PLUGIN("checks");

// Define the Variables
APO_VARIABLES(
	VAR_REAL(checks_x, 0.5),
	VAR_REAL(checks_y, 0.5),
	VAR_REAL(checks_size, 0.5),
	VAR_REAL(checks_rnd, 0.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    // Multiplication is faster than division, so divide in precalc, multiply in calc.
    VAR(cs) = 1.0 / (VAR(checks_size) + EPS);
    
    // -X- Copied the variables as we only need them for reading
    //     This is just for safety :-)
    VAR(cx) = VAR(checks_x); VAR(cy) = VAR(checks_y);
    // -X- Then precalculate -checkx_x, -checks_y
    VAR(ncx) = VAR(checks_x) * -1.0; VAR(ncy) = VAR(checks_y) * -1.0;
    
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double dx, dy;
    double x = FTx * VAR(cs);
    double y = FTy * VAR(cs);
    
    int isXY = lrint(FTx * VAR(cs)) + 
               lrint(FTy * VAR(cs));

    // -X- This is just for code readability,
    //     if there is any impact on performance, its minimal :-)
    double rnx = VAR(checks_rnd) * random01();
    double rny = VAR(checks_rnd) * random01();

    if (isXY % 2)
    {
        // -X- The -VAR(checks_#) stuff caused the error!
        dx = VAR(ncx) + rnx;
        dy = VAR(ncy);
    }
    else
    {
        dx = VAR(cx);
        dy = VAR(cy) + rny;
    }

	FPx += VVAR * (FTx + dx);
	FPy += VVAR * (FTy + dy);
	
	// -X- and as a little goodie, I pass through FTz so that
	//     neat lil variation does not kill 3Dness in hack & 7X
	FPz += VVAR * (FTz);

    return TRUE;
}
