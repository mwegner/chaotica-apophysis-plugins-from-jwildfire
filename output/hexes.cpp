#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
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

// This implements some basic 2D vector routines that assist with Voronoi
// cell calculations.

#define VORONOI_MAXPOINTS 25

// Cheap and cheerful vector definitions for 3D :-)
// They just make reading vector code based on arrays
// slightly nicer for me! E.g. use V[_x_] instead of V[0].

#define _x_ 0
#define _y_ 1
#define _z_ 2


// Distance between U and P compared to U and Q. If U is at P, then the value is 0, if it is
// equally far to Q and P then the value is 1.0
double vratio( double P[2], double Q[2], double U[2] ) {
	double PmQx, PmQy;

	PmQx = P[_x_] - Q[_x_];
	PmQy = P[_y_] - Q[_y_];

	if ( 0.0 == PmQx && 0.0 == PmQy ) {
		return 1.0;
	}

	return 2.0 * ( ( U[_x_] - Q[_x_] ) * PmQx + ( U[_y_] - Q[_y_] ) * PmQy ) / ( PmQx * PmQx + PmQy * PmQy );
}

// Closest point to U from array P.
//  P is an array of points
//  n is number of points to check
//  U is location to find closest
int closest( double P[VORONOI_MAXPOINTS][2], int n, double U[2] ) {
	double d2;
	double d2min = 1.0e100;
	int i, j;

	for( i = 0; i < n; i++ ) {
		d2 = (P[i][_x_] - U[_x_]) * (P[i][_x_] - U[_x_]) + (P[i][_y_] - U[_y_]) * (P[i][_y_] - U[_y_]);
		if ( d2 < d2min ) {
			d2min = d2;
			j = i;
		}
	}

	return j;
}

// Voronoi "value" is 0.0 (centre) to 1.0 (edge) if inside cell . . . higher values
// mean that point is not in the cell defined by chosen centre.
//  P is an array of points defining cell centres
//  n is number of points in array
//  q is chosen centre to measure distance from
//  U is point to test
double voronoi( double P[VORONOI_MAXPOINTS][2], int n, int q, double U[2] ) {
	double ratio;
	double ratiomax = -1.0e100;
	int i;

	for( i = 0; i < n; i++ ) {
		if ( i != q ) {
			ratio = vratio( P[i], P[q], U );
			if ( ratio > ratiomax ) {
				ratiomax = ratio;
			}
		}
	}

	return ratiomax;
}

// Following are pre-calculated fixed multipliers for converting
// between "Hex" co-ordinates and "Original" co-ordinates.

// This is, in fact, an affine transform. So we'll use same notation
// as for Apophysis transforms:
// x_hex = a_hex * x_cartesian + b_hex * y_cartesian
// y_hex = c_hex * x_cartesian + d_hex * y_cartesian
//  . . . and the reverse:
// x_cartesian =  a_cart * x_hex + b_cart * y_hex
// y_cartesian =  c_cart * x_hex + d_cart * y_hex
// Values for e and f are 0.0 in both cases, so not required.

// Xh = (Xo + sqrt(3) * Yo) / (3 * l)
static const double a_hex = 1.0/3.0;
static const double b_hex = 1.7320508075688772935/3.0;
// Now:  Xh = ( a_hex * Xo + b_hex * Yo ) / l;

// Yh = (-Xo + sqrt(3) * Yo) / (3 * l)
static const double c_hex = -1.0/3.0;
static const double d_hex = 1.7320508075688772935/3.0;
// Now:  Yh = ( c_hex * Xo + d_hex * Yo ) / l;

// Xo = 3/2 * l * (Xh - Yh)
static const double a_cart = 1.5;
static const double b_cart = -1.5;
// Now:  Xo = ( a_cart * Xh + b_cart * Yh ) * l;

// Yo = sqrt(3)/2 * l * (Xh + Yh)
static const double c_cart = 1.7320508075688772935/2.0;
static const double d_cart = 1.7320508075688772935/2.0;
// Now:  Yo = ( c_cart * Xh + d_cart * Yh ) * l;

static int cell_choice[9][2] = { { -1, -1}, { -1, 0}, { -1, 1}, { 0, -1}, { 0, 0}, { 0, 1}, { 1, -1}, { 1, 0}, { 1, 1} };

// centre gives centre co-ordinates either from cache,
// or calculated from scratch if needed
void cell_centre( int x, int y, double s, double V[2] ) {
	V[_x_] = (a_cart * x + b_cart * y ) * s;
	V[_y_] = (c_cart * x + d_cart * y ) * s;
}

// Must define this structure before we include apoplugin.h
typedef struct
{
	double hexes_cellsize;
	double hexes_power;
	double hexes_rotate;
	double hexes_scale;

	// P is a working list of points
	double P[VORONOI_MAXPOINTS][2];
	double rotSin;
	double rotCos;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("hexes");

// Define the Variables
APO_VARIABLES(
		VAR_REAL(hexes_cellsize, 1.0),
		VAR_REAL(hexes_power, 1.0),
		VAR_REAL(hexes_rotate, 0.166),
		VAR_REAL(hexes_scale, 1.0),
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
	// Pre-calculate rotation matrix, to save time later . . .
	VAR(rotSin) = sin( VAR(hexes_rotate) * 2 * M_PI );
	VAR(rotCos) = cos( VAR(hexes_rotate) * 2 * M_PI );
	return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
	double XCh, YCh, XCo, YCo, DXo, DYo, L, L1, L2, R, R1, R2, s, trgL, Vx, Vy;
	double U[2];
	int Hx, Hy;

	// For speed/convenience
	s = VAR(hexes_cellsize);

	// Infinite number of small cells? No effect . . .
	if ( 0.0 == s ) { return TRUE; }

	// Get cartesian co-ordinates, and convert to hex co-ordinates
	U[_x_] = FTx;
	U[_y_] = FTy;

	Hx = (int) floor( ( a_hex * U[_x_] + b_hex * U[_y_] ) / s );
	Hy = (int) floor( ( c_hex * U[_x_] + d_hex * U[_y_] ) / s );

	// Get a set of 9 hex centre points, based around the one above
	int i = 0;
	int di, dj;
	for (di = -1; di < 2; di++) {
		for (dj = -1; dj < 2; dj++) {
			cell_centre( Hx + di, Hy + dj, s, VAR(P)[i] );
			i++;
		}
	}

	int q = closest( VAR(P), 9, U );

	// Remake list starting from chosen hex, ensure it is completely surrounded (total 7 points)

	// First adjust centres according to which one was found to be closest
	Hx += cell_choice[q][_x_];
	Hy += cell_choice[q][_y_];

	// First point is central/closest
	cell_centre( Hx, Hy, VAR(hexes_cellsize), VAR(P)[0] );

	XCo = VAR(P)[0][_x_];
	YCo = VAR(P)[0][_y_];

	// Next six points are based on hex graph (6 hexes around centre). As long as
	// centre points are not too distorted from simple hex, this defines all possible edges

	// In hex co-ords, offsets are: (0,1) (1,1) (1,0) (0,-1) (-1,-1) (-1, 0)
	cell_centre( Hx    , Hy + 1, s, VAR(P)[1] );
	cell_centre( Hx + 1, Hy + 1, s, VAR(P)[2] );
	cell_centre( Hx + 1, Hy    , s, VAR(P)[3] );
	cell_centre( Hx    , Hy - 1, s, VAR(P)[4] );
	cell_centre( Hx - 1, Hy - 1, s, VAR(P)[5] );
	cell_centre( Hx - 1, Hy    , s, VAR(P)[6] );

	L1 = voronoi( VAR(P), 7, 0, U );

	// Delta vector from centre of hex
	DXo = U[_x_] - VAR(P)[0][_x_];
	DYo = U[_y_] - VAR(P)[0][_y_];

	/////////////////////////////////////////////////////////////////
	// Apply "interesting bit" to cell's DXo and DYo co-ordinates

	// trgL is the defined value of l, independent of any rotation
	trgL = pow( L1 + 1e-100, VAR(hexes_power) ) * VAR(hexes_scale);

	// Rotate
	Vx = DXo * VAR(rotCos) + DYo * VAR(rotSin);
	Vy = -DXo * VAR(rotSin) + DYo * VAR(rotCos);

	//////////////////////////////////////////////////////////////////
	// Measure voronoi distance again

	U[_x_] = Vx + VAR(P)[0][_x_];
	U[_y_] = Vy + VAR(P)[0][_y_];
	L2 = voronoi( VAR(P), 7, 0, U );

	//////////////////////////////////////////////////////////////////
	// Scale to meet target size . . . adjust according to how close
	// we are to the edge

	// Code here attempts to remove the "rosette" effect caused by
	// scaling difference between corners and closer edges

	// L is maximum of L1 or L2 . . .
	// When L = 0.8 or higher . . . match trgL/L2 exactly
	// When L = 0.5 or less . . . match trgL/L1 exactly

	R1 = trgL / ( L1 + 1e-100 );
	R2 = trgL / ( L2 + 1e-100 );

	L = ( L1 > L2 ) ? L1 : L2;

	if ( L < 0.5 ) {
		R = trgL / L1;
	} else {
		if ( L > 0.8 ) {
			R = trgL / L2;
		} else {
			R = ( ( trgL / L1 ) * ( 0.8 - L )  + ( trgL / L2 ) * ( L - 0.5 ) ) / 0.3;
		}
	}

	Vx *= R;
	Vy *= R;

	// Add cell centre co-ordinates back in
	Vx += VAR(P)[0][_x_];
	Vy += VAR(P)[0][_y_];

	// Finally add values in
	FPx += VVAR * Vx;
	FPy += VVAR * Vy;

	return TRUE;
}