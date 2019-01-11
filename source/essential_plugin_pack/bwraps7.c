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

// bwraps7 - Bubble Wraps beta version

// Must define this structure before we include apoplugin.h
typedef struct
{
	double bwraps7_cellsize;
	double bwraps7_space;
	double bwraps7_gain;
	double bwraps7_inner_twist;
	double bwraps7_outer_twist;
    double g2;
	double r2;
	double rfactor;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("bwraps7");

// Define the Variables
APO_VARIABLES(
    VAR_REAL(bwraps7_cellsize, 1.0),
    VAR_REAL(bwraps7_space, 0.0),
    VAR_REAL(bwraps7_gain, 2.0),
    VAR_REAL(bwraps7_inner_twist, 0.0),
    VAR_REAL(bwraps7_outer_twist, 0.0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
	double radius = 0.5 * ( VAR(bwraps7_cellsize) / ( 1.0 + VAR(bwraps7_space) * VAR(bwraps7_space) ) );
	
	// g2 is multiplier for radius
	VAR(g2) = VAR(bwraps7_gain) * VAR(bwraps7_gain) + 1.0e-6;
	
	// Start max_bubble as maximum x or y value before applying bubble
	double max_bubble = VAR(g2) * radius;
	
    if ( max_bubble > 2.0 )
    {
   	     // Values greater than 2.0 "recurve" round the back of the bubble
         max_bubble = 1.0;
    }
    else
    {
        // Expand smaller bubble to fill the space
	    max_bubble *= 1.0 / ( (max_bubble * max_bubble)/4.0 + 1.0);
    }

	VAR(r2) = radius * radius;
	VAR(rfactor) =  radius / max_bubble;

    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double Vx, Vy; // V is "global" vector,
	double Cx, Cy; // C is "cell centre" vector
	double Lx, Ly; // L is "local" bubble vector
	double r, theta, s, c;

    Vx = FTx;
    Vy = FTy;

	if ( VAR(bwraps7_cellsize) == 0.0 )
	{
		// Linear if cells are too small
		FPx += VVAR * Vx;
		FPy += VVAR * Vy;
		return TRUE;
	}

	Cx = ( floor( Vx / VAR(bwraps7_cellsize) ) + 0.5 ) * VAR(bwraps7_cellsize);
	Cy = ( floor( Vy / VAR(bwraps7_cellsize) ) + 0.5 ) * VAR(bwraps7_cellsize);

	Lx = Vx - Cx;
	Ly = Vy - Cy;

	if ( ( Lx * Lx + Ly * Ly ) > VAR(r2) )
	{
		// Linear if outside the bubble
		FPx += VVAR * Vx;
		FPy += VVAR * Vy;
		return TRUE;
	}

	// We're in the bubble!
	
	// Bubble distortion on local co-ordinates:
	Lx *= VAR(g2);
	Ly *= VAR(g2);
	r = VAR(rfactor) / ( (Lx * Lx + Ly * Ly)/4.0 + 1.0);
	Lx *= r;
	Ly *= r;
 
 	// Spin around the centre:
    r = (Lx * Lx + Ly * Ly) / VAR(r2);  // r should be 0.0 - 1.0
    theta = VAR(bwraps7_inner_twist) * ( 1.0 - r ) + VAR(bwraps7_outer_twist) * r;
    fsincos( theta, &s, &c );
    
    // Add rotated local vectors direct to centre (avoids use of temp storage)
    Vx = Cx    + c * Lx + s * Ly;
    Vy = Cy    - s * Lx + c * Ly;
   	
	// Finally add values in
	FPx += VVAR * Vx;
	FPy += VVAR * Vy;

	return TRUE;
}
