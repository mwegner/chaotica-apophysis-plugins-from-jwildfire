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
    int lazyjess_n;
	double lazyjess_spin;
    double lazyjess_space;
	int lazyjess_corner;
	double vertex;
	double sin_vertex;
	double pie_slice;
	double half_slice;
	double corner_rotation;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("lazyjess");

// Define the Variables
APO_VARIABLES(
	VAR_INTEGER_NONZERO (lazyjess_n, 4),
    VAR_REAL_CYCLE(lazyjess_spin, 0.0, M_2PI, M_PI),
    VAR_REAL(lazyjess_space, 0.0),
	VAR_INTEGER_NONZERO (lazyjess_corner, 1)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
	// there's no way to have an apo variable that has to be an integer greater than 1
	if(VAR(lazyjess_n) < 2)
	{
		VAR(lazyjess_n) = 2;
	}
	
	VAR(vertex) = M_PI * (VAR(lazyjess_n) - 2) / (2 * VAR(lazyjess_n));
	VAR(sin_vertex) = sin(VAR(vertex));
	VAR(pie_slice) = M_2PI / VAR(lazyjess_n);
	VAR(half_slice) = VAR(pie_slice) / 2;
	VAR(corner_rotation) = (VAR(lazyjess_corner) - 1) * VAR(pie_slice);
    
	// Always return TRUE.
	return TRUE;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double theta, sina, cosa;
	double x = FTx;
	double y = FTy;
	double modulus = sqrt(x*x + y*y);
	
	// n==2 requires a special case
	if (VAR(lazyjess_n) == 2)
	{
		if (abs(x) < VVAR) // If the input point falls inside the designated area...
		{
			// ...then rotate it.
			theta = atan2(y, x) + VAR(lazyjess_spin);
			fsincos(theta, &sina, &cosa);
			x = VVAR * modulus * cosa;
			y = VVAR * modulus * sina;
			
			if (abs(x) < VVAR)
			{
				FPx += x;
				FPy += y;
			}
			else // If it is now part of a corner that falls outside the designated area...
			{
				// ...then flip and rotate into place.
				theta = atan2(y, x) - VAR(lazyjess_spin) + VAR(corner_rotation);
				fsincos(theta, &sina, &cosa);
				FPx += VVAR * modulus * cosa;
				FPy -= VVAR * modulus * sina;
			}
		}
		else
		{
			modulus = 1.0 + VAR(lazyjess_space) / modulus;
			FPx += VVAR * modulus * x;
			FPy += VVAR * modulus * y;
		}
	}
	else
	{
		// Calculate the distance r from origin to the edge of the polygon at the angle of the input point.
		theta = atan2(y, x) + M_2PI;
		double theta_diff = fmod(theta + VAR(half_slice), VAR(pie_slice));
		double r = VVAR * M_SQRT2 * VAR(sin_vertex) / sin(M_PI - theta_diff - VAR(vertex));

		if (modulus < r)
		{
			// Again, rotating points within designated area.
			theta = atan2(y, x) + VAR(lazyjess_spin) + M_2PI;
			fsincos(theta, &sina, &cosa);
			x = VVAR * modulus * cosa;
			y = VVAR * modulus * sina;

			// Calculating r and modulus for our rotated point.
			theta_diff = fmod(theta + VAR(half_slice), VAR(pie_slice));
			r = VVAR * M_SQRT2 * VAR(sin_vertex) / sin(M_PI - theta_diff - VAR(vertex));
			modulus = sqrt(x*x + y*y);
			 
			if (modulus < r)
			{
				FPx += x;
				FPy += y;
			}
			else
			{
				// Again, flipping and rotating corners that fall outside the designated area.
				theta = atan2(y, x) - VAR(lazyjess_spin) + VAR(corner_rotation) + M_2PI;
				fsincos(theta, &sina, &cosa);
				FPx += VVAR * modulus * cosa;
				FPy -= VVAR * modulus * sina;
			}
		}
		else
		{
			modulus = 1.0 + VAR(lazyjess_space) / modulus;
			FPx += VVAR * modulus * x;
			FPy += VVAR * modulus * y;
		}
	}

    return TRUE;
}
