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

/*
    09-10-04    - Optimized by Xyrus02
*/

typedef struct
{
	//double v;
	double spr;
	double flux_spread;

} Variables;

#include "apoplugin.h"

APO_PLUGIN("flux");

APO_VARIABLES(
    VAR_REAL(flux_spread, 0.0),
);

int PluginVarPrepare(Variation* vp)
{
    // Why is this calculated? It isn't used...
	//VAR(v) = 0.5 * VVAR / M_PI;
	
	// But we only use 2 + VAR(flux_spread) so we can precalculate that :-)
	VAR(spr) = 2 + VAR(flux_spread);
	
	// We succeeded :-)
    return TRUE; 
}

int PluginVarCalc(Variation* vp)
{
	double avgr, avga;
	double s, c;
	
	// Avoid reduant calculations by precalculating everything what is used at least twice
	double x = FTx, 
           y = FTy;
	double xpv = FTx + VVAR, 
           xmv = FTx - VVAR;
	double y2 = sqr(y);
	
	// We have a division by zero problem in the original flux
	// (What if y + (x-vvar) == 0 ????)
	double frac = sqrt(y2 + sqr(xmv));
	if (frac == 0) frac = 1.0;
	
	// This is a huge shitload of calculations :O
	avgr = VVAR * (VAR(spr) * sqrt(sqrt(y2 + sqr(xpv) ) / frac));
	avga = (atan2(y , xmv) - atan2(y , xpv)) / 2.0;
	fsincos(avga, &s, &c);

	FPx += avgr * c;
	FPy += avgr * s;
	
	// Add 3D compatibility
	FPz += FTz;

    // Report success!
    return TRUE;
}
