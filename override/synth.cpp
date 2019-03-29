/*
    Apophysis Plugin - Synth v2

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
    The Thing That Should Not Be

    A much neater way of providing the kind of felixibility and control
    in Apophysis that I am aiming for with Synth would be to create
    a node-based system of connected functions that allowed advanced users
    to build their own routines for the Apophysis engine from simple
    components.

    Many other graphic and audio engines use this concept very successfully.

    Such a system could make FX, PX, xaos etc redundant too.

    I've made Synth, because I cannot forsee that kind of development happening
    with Apophysis. This is no sleight to the Apo developers - from Mark Townsend
    onwards the project has been an inspiration and joy to many people. It is
    more simply a recognition of how hard it would be to make such a change
    to Apophysis as it stands.
*/

// Must define this structure before we include apoplugin.h
typedef struct
{
    double synth_a;
	int synth_mode;
	double synth_power;
	double synth_mix;
	int synth_smooth;

    double synth_b;
    int synth_b_type;
    double synth_b_frq;
    double synth_b_skew;
    double synth_b_phs;
    int synth_b_layer;

    double synth_c;
    int synth_c_type;
    double synth_c_frq;
    double synth_c_skew;
    double synth_c_phs;
    int synth_c_layer;

    double synth_d;
    int synth_d_type;
    double synth_d_frq;
    double synth_d_skew;
    double synth_d_phs;
    int synth_d_layer;

    double synth_e;
    int synth_e_type;
    double synth_e_frq;
    double synth_e_skew;
    double synth_e_phs;
    int synth_e_layer;

    double synth_f;
    int synth_f_type;
    double synth_f_frq;
    double synth_f_skew;
    double synth_f_phs;
    int synth_f_layer;
} Variables;

#define _USE_MATH_DEFINES
#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("synth");

// Define the Variables
APO_VARIABLES(

    VAR_REAL(synth_a, 1.0),
    VAR_INTEGER(synth_mode, 3),
    VAR_REAL(synth_power, -2.0),
    VAR_REAL(synth_mix, 1.0),
    VAR_INTEGER(synth_smooth, 0),

    VAR_REAL(synth_b, 0.0),
    VAR_INTEGER(synth_b_type, 0),
    VAR_REAL(synth_b_skew, 0.0),
    VAR_REAL(synth_b_frq, 1.0),
    VAR_REAL(synth_b_phs, 0.0),
    VAR_INTEGER(synth_b_layer, 0),

    VAR_REAL(synth_c, 0.0),
    VAR_INTEGER(synth_c_type, 0),
    VAR_REAL(synth_c_skew, 0.0),
    VAR_REAL(synth_c_frq, 1.0),
    VAR_REAL(synth_c_phs, 0.0),
    VAR_INTEGER(synth_c_layer, 0),

    VAR_REAL(synth_d, 0.0),
    VAR_INTEGER(synth_d_type, 0),
    VAR_REAL(synth_d_skew, 0.0),
    VAR_REAL(synth_d_frq, 1.0),
    VAR_REAL(synth_d_phs, 0.0),
    VAR_INTEGER(synth_d_layer, 0),

    VAR_REAL(synth_e, 0.0),
    VAR_INTEGER(synth_e_type, 0),
    VAR_REAL(synth_e_skew, 0.0),
    VAR_REAL(synth_e_frq, 1.0),
    VAR_REAL(synth_e_phs, 0.0),
    VAR_INTEGER(synth_e_layer, 0),

	VAR_REAL(synth_f, 0.0),
	VAR_INTEGER(synth_f_type, 0),
	VAR_REAL(synth_f_skew, 0.0),
	VAR_REAL(synth_f_frq, 1.0),
	VAR_REAL(synth_f_phs, 0.0),
    VAR_INTEGER(synth_f_layer, 0)

);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    return TRUE; // Always return TRUE.
}

// -------------------------------------------------------------
// Modes
// "Lagacy" modes from v1
#define MODE_SPHERICAL 0
#define MODE_BUBBLE 1
#define MODE_BLUR_LEGACY 2
// New modes in v2
#define MODE_BLUR_NEW 3
#define MODE_BLUR_ZIGZAG 4
#define MODE_RAWCIRCLE 5
#define MODE_RAWX 6
#define MODE_RAWY 7
#define MODE_RAWXY 8
#define MODE_SHIFTX 9
#define MODE_SHIFTY 10
#define MODE_SHIFTXY 11
#define MODE_BLUR_RING 12
#define MODE_BLUR_RING2 13
#define MODE_SHIFTNSTRETCH 14
#define MODE_SHIFTTANGENT 15
#define MODE_SHIFTTHETA 16
#define MODE_XMIRROR 17
#define MODE_XYMIRROR 18
#define MODE_SPHERICAL2 19

// Ideas:
// Rectangle
// Grid
// Spiral grid
// Ortho?

// Failed experiments (were 12-18)
#define MODE_SINUSOIDAL 1001
#define MODE_SWIRL 1002
#define MODE_HYPERBOLIC 1003
#define MODE_JULIA 1004
#define MODE_DISC 1005
#define MODE_RINGS 1006
#define MODE_CYLINDER 1007

// -------------------------------------------------------------
// Wave types
#define WAVE_SIN 0
#define WAVE_COS 1
#define WAVE_SQUARE 2
#define WAVE_SAW 3
#define WAVE_TRIANGLE 4
#define WAVE_CONCAVE 5
#define WAVE_CONVEX 6
#define WAVE_NGON 7
// New wave types in v2
#define WAVE_INGON 8

// -------------------------------------------------------------
// Layer types
#define LAYER_ADD 0
#define LAYER_MULT 1
#define LAYER_MAX 2
#define LAYER_MIN 3

// -------------------------------------------------------------
// Interpolation types
#define LERP_LINEAR 0
#define LERP_BEZIER 1

// -------------------------------------------------------------
// Sine/Cosine interpretation types
#define SINCOS_MULTIPLY 0
#define SINCOS_MIXIN 1

// -------------------------------------------------------------
// synth_value calculates the wave height y from theta, which is an abstract
// angle that could come from any other calculation - for circular modes
// it will be the angle between the positive y axis and the vector from
// the origin to the pont i.e. atan2(x,y)
// You must call the argument "vp".
inline double synth_value(Variation* vp, double theta)
{
    double theta_factor = VAR(synth_a);
    double x,y,z;

    if ( VAR(synth_b) != 0.0 ) {

		z = VAR(synth_b_phs) + theta * VAR(synth_b_frq);
		y = z / ( 2 * M_PI );
		y -= floor( y );

		// y is in range 0 - 1. Now skew according to synth_b_skew
		if (  VAR(synth_b_skew) != 0.0 ) {
			z = 0.5 + 0.5 * VAR(synth_b_skew);
			if ( y > z ) {
				// y is 0.5 if equals z, up to 1.0
				y = 0.5 + 0.5 * (y - z)/(1.0 - z + EPS);
			}
			else {
				// y is 0.5 if equals z, down to 0.0
				y = 0.5 - 0.5 * (z - y)/(z + EPS);
			}
		}

		switch ( VAR(synth_b_type) ) {
			case WAVE_SIN:
				x = sin( y * 2 * M_PI );
				break;
			case WAVE_COS:
				x = cos( y * 2 * M_PI );
				break;
			case WAVE_SQUARE:
				x = y > 0.5 ? 1.0 : -1.0;
				break;
			case WAVE_SAW:
				x = 1.0 - 2.0 * y;
				break;
			case WAVE_TRIANGLE:
				x = y > 0.5 ? 3.0 - 4.0 * y : 2.0 * y - 1.0;
				break;
			case WAVE_CONCAVE:
                x = 8.0 * ( y - 0.5 ) * ( y - 0.5 ) - 1.0;
				break;
			case WAVE_CONVEX:
                x = 2.0 * sqrt( y ) - 1.0;
				break;
			case WAVE_NGON:
                y -= 0.5;
                y *= (2.0 * M_PI / VAR(synth_b_frq) );
                x = ( 1.0 / ( cos(y) + EPS )  - 1.0);
				break;
			case WAVE_INGON:
                y -= 0.5;
                y *= (2.0 * M_PI / VAR(synth_b_frq) );
                z = cos(y);
                x = z / ( 1.0 + EPS - z );
				break;
		}

		switch ( VAR(synth_b_layer) ) {
			case LAYER_ADD:
				theta_factor += VAR(synth_b) * x;
				break;
		    case LAYER_MULT:
				theta_factor *= ( 1.0 + VAR(synth_b) * x );
				break;
			case LAYER_MAX:
			    z = VAR(synth_a) + VAR(synth_b) * x;
			    theta_factor = ( theta_factor > z ? theta_factor : z );
			    break;
			case LAYER_MIN:
			    z = VAR(synth_a) + VAR(synth_b) * x;
			    theta_factor = ( theta_factor < z ? theta_factor : z );
			    break;
		}
	}


    if ( VAR(synth_c) != 0.0 ) {

		z = VAR(synth_c_phs) + theta * VAR(synth_c_frq);
		y = z / ( 2 * M_PI );
		y -= floor( y );

		// y is in range 0 - 1. Now skew according to synth_c_skew
		if (  VAR(synth_c_skew) != 0.0 ) {
			z = 0.5 + 0.5 * VAR(synth_c_skew);
			if ( y > z ) {
				// y is 0.5 if equals z, up to 1.0
				y = 0.5 + 0.5 * (y - z)/(1.0 - z + EPS);
			}
			else {
				// y is 0.5 if equals z, down to 0.0
				y = 0.5 - 0.5 * (z - y)/(z + EPS);
			}
		}

		switch ( VAR(synth_c_type) ) {
			case WAVE_SIN:
				x = sin( y * 2 * M_PI );
				break;
			case WAVE_COS:
				x = cos( y * 2 * M_PI );
				break;
			case WAVE_SQUARE:
				x = y > 0.5 ? 1.0 : -1.0;
				break;
			case WAVE_SAW:
				x = 1.0 - 2.0 * y;
				break;
			case WAVE_TRIANGLE:
				x = y > 0.5 ? 3.0 - 4.0 * y : 2.0 * y - 1.0;
				break;
			case WAVE_CONCAVE:
                x = 8.0 * ( y - 0.5 ) * ( y - 0.5 ) - 1.0;
				break;
			case WAVE_CONVEX:
                x = 2.0 * sqrt( y ) - 1.0;
				break;
			case WAVE_NGON:
                y -= 0.5;
                y *= (2.0 * M_PI / VAR(synth_c_frq) );
                x = ( 1.0 / ( cos(y) + EPS )  - 1.0);
				break;
			case WAVE_INGON:
                y -= 0.5;
                y *= (2.0 * M_PI / VAR(synth_c_frq) );
                z = cos(y);
                x = z / ( 1.0 + EPS - z );
				break;
		}

		switch ( VAR(synth_c_layer) ) {
			case LAYER_ADD:
				theta_factor += VAR(synth_c) * x;
				break;
		    case LAYER_MULT:
				theta_factor *= ( 1.0 + VAR(synth_c) * x );
				break;
			case LAYER_MAX:
			    z = VAR(synth_a) + VAR(synth_c) * x;
			    theta_factor = ( theta_factor > z ? theta_factor : z );
			    break;
			case LAYER_MIN:
			    z = VAR(synth_a) + VAR(synth_c) * x;
			    theta_factor = ( theta_factor < z ? theta_factor : z );
			    break;
		}
	}


    if ( VAR(synth_d) != 0.0 ) {

		z = VAR(synth_d_phs) + theta * VAR(synth_d_frq);
		y = z / ( 2 * M_PI );
		y -= floor( y );

		// y is in range 0 - 1. Now skew according to synth_d_skew
		if (  VAR(synth_d_skew) != 0.0 ) {
			z = 0.5 + 0.5 * VAR(synth_d_skew);
			if ( y > z ) {
				// y is 0.5 if equals z, up to 1.0
				y = 0.5 + 0.5 * (y - z)/(1.0 - z + EPS);
			}
			else {
				// y is 0.5 if equals z, down to 0.0
				y = 0.5 - 0.5 * (z - y)/(z + EPS);
			}
		}

		switch ( VAR(synth_d_type) ) {
			case WAVE_SIN:
				x = sin( y * 2 * M_PI );
				break;
			case WAVE_COS:
				x = cos( y * 2 * M_PI );
				break;
			case WAVE_SQUARE:
				x = y > 0.5 ? 1.0 : -1.0;
				break;
			case WAVE_SAW:
				x = 1.0 - 2.0 * y;
				break;
			case WAVE_TRIANGLE:
				x = y > 0.5 ? 3.0 - 4.0 * y : 2.0 * y - 1.0;
				break;
			case WAVE_CONCAVE:
                x = 8.0 * ( y - 0.5 ) * ( y - 0.5 ) - 1.0;
				break;
			case WAVE_CONVEX:
                x = 2.0 * sqrt( y ) - 1.0;
				break;
			case WAVE_NGON:
                y -= 0.5;
                y *= (2.0 * M_PI / VAR(synth_d_frq) );
                x = ( 1.0 / ( cos(y) + EPS )  - 1.0);
				break;
			case WAVE_INGON:
                y -= 0.5;
                y *= (2.0 * M_PI / VAR(synth_d_frq) );
                z = cos(y);
                x = z / ( 1.0 + EPS - z );
				break;
		}

		switch ( VAR(synth_d_layer) ) {
			case LAYER_ADD:
				theta_factor += VAR(synth_d) * x;
				break;
		    case LAYER_MULT:
				theta_factor *= ( 1.0 + VAR(synth_d) * x );
				break;
			case LAYER_MAX:
			    z = VAR(synth_a) + VAR(synth_d) * x;
			    theta_factor = ( theta_factor > z ? theta_factor : z );
			    break;
			case LAYER_MIN:
			    z = VAR(synth_a) + VAR(synth_d) * x;
			    theta_factor = ( theta_factor < z ? theta_factor : z );
			    break;
		}
	}


    if ( VAR(synth_e) != 0.0 ) {

		z = VAR(synth_e_phs) + theta * VAR(synth_e_frq);
		y = z / ( 2 * M_PI );
		y -= floor( y );

		// y is in range 0 - 1. Now skew according to synth_e_skew
		if (  VAR(synth_e_skew) != 0.0 ) {
			z = 0.5 + 0.5 * VAR(synth_e_skew);
			if ( y > z ) {
				// y is 0.5 if equals z, up to 1.0
				y = 0.5 + 0.5 * (y - z)/(1.0 - z + EPS);
			}
			else {
				// y is 0.5 if equals z, down to 0.0
				y = 0.5 - 0.5 * (z - y)/(z + EPS);
			}
		}

		switch ( VAR(synth_e_type) ) {
			case WAVE_SIN:
				x = sin( y * 2 * M_PI );
				break;
			case WAVE_COS:
				x = cos( y * 2 * M_PI );
				break;
			case WAVE_SQUARE:
				x = y > 0.5 ? 1.0 : -1.0;
				break;
			case WAVE_SAW:
				x = 1.0 - 2.0 * y;
				break;
			case WAVE_TRIANGLE:
				x = y > 0.5 ? 3.0 - 4.0 * y : 2.0 * y - 1.0;
				break;
			case WAVE_CONCAVE:
                x = 8.0 * ( y - 0.5 ) * ( y - 0.5 ) - 1.0;
				break;
			case WAVE_CONVEX:
                x = 2.0 * sqrt( y ) - 1.0;
				break;
			case WAVE_NGON:
                y -= 0.5;
                y *= (2.0 * M_PI / VAR(synth_e_frq) );
                x = ( 1.0 / ( cos(y) + EPS )  - 1.0);
				break;
			case WAVE_INGON:
                y -= 0.5;
                y *= (2.0 * M_PI / VAR(synth_e_frq) );
                z = cos(y);
                x = z / ( 1.0 + EPS - z );
				break;

		}

		switch ( VAR(synth_e_layer) ) {
			case LAYER_ADD:
				theta_factor += VAR(synth_e) * x;
				break;
		    case LAYER_MULT:
				theta_factor *= ( 1.0 + VAR(synth_e) * x );
				break;
			case LAYER_MAX:
			    z = VAR(synth_a) + VAR(synth_e) * x;
			    theta_factor = ( theta_factor > z ? theta_factor : z );
			    break;
			case LAYER_MIN:
			    z = VAR(synth_a) + VAR(synth_e) * x;
			    theta_factor = ( theta_factor < z ? theta_factor : z );
			    break;
		}
	}


    if ( VAR(synth_f) != 0.0 ) {

		z = VAR(synth_f_phs) + theta * VAR(synth_f_frq);
		y = z / ( 2 * M_PI );
		y -= floor( y );

		// y is in range 0 - 1. Now skew according to synth_f_skew
		if (  VAR(synth_f_skew) != 0.0 ) {
			z = 0.5 + 0.5 * VAR(synth_f_skew);
			if ( y > z ) {
				// y is 0.5 if equals z, up to 1.0
				y = 0.5 + 0.5 * (y - z)/(1.0 - z + EPS);
			}
			else {
				// y is 0.5 if equals z, down to 0.0
				y = 0.5 - 0.5 * (z - y)/(z + EPS);
			}
		}

		switch ( VAR(synth_f_type) ) {
			case WAVE_SIN:
				x = sin( y * 2 * M_PI );
				break;
			case WAVE_COS:
				x = cos( y * 2 * M_PI );
				break;
			case WAVE_SQUARE:
				x = y > 0.5 ? 1.0 : -1.0;
				break;
			case WAVE_SAW:
				x = 1.0 - 2.0 * y;
				break;
			case WAVE_TRIANGLE:
				x = y > 0.5 ? 3.0 - 4.0 * y : 2.0 * y - 1.0;
				break;
			case WAVE_CONCAVE:
                x = 8.0 * ( y - 0.5 ) * ( y - 0.5 ) - 1.0;
				break;
			case WAVE_CONVEX:
                x = 2.0 * sqrt( y ) - 1.0;
				break;
			case WAVE_NGON:
                y -= 0.5;
                y *= (2.0 * M_PI / VAR(synth_f_frq) );
                x = ( 1.0 / ( cos(y) + EPS )  - 1.0);
				break;
			case WAVE_INGON:
                y -= 0.5;
                y *= (2.0 * M_PI / VAR(synth_f_frq) );
                z = cos(y);
                x = z / ( 1.0 + EPS - z );
				break;
		}

		switch ( VAR(synth_f_layer) ) {
			case LAYER_ADD:
				theta_factor += VAR(synth_f) * x;
				break;
		    case LAYER_MULT:
				theta_factor *= ( 1.0 + VAR(synth_f) * x );
				break;
			case LAYER_MAX:
			    z = VAR(synth_a) + VAR(synth_f) * x;
			    theta_factor = ( theta_factor > z ? theta_factor : z );
			    break;
			case LAYER_MIN:
			    z = VAR(synth_a) + VAR(synth_f) * x;
			    theta_factor = ( theta_factor < z ? theta_factor : z );
			    break;
		}
	}

    // Mix is applied here, assuming 1.0 to be the "flat" line for legacy support
    return theta_factor * VAR(synth_mix) + ( 1.0 - VAR(synth_mix) );
}

// -------------------------------------------------------------
// Mapping function y = fn(x) based on quadratic Bezier curves for smooth type 1
// Returns close to y = x for high/low values of x, y = m when x = 1.0, and
// something in-between y = m*x and y = x lines when x is close-ish to 1.0
// Function always has slope of 0.0 or greater, so no x' values "overlap"
inline double bezier_quad_map( double x, double m )
{
	double a = 1.0; // a is used to control sign of result
	double t = 0.0; // t is the Bezier curve parameter

	// Simply reflect in the y axis for negative values
	if ( m < 0.0 ) { m = -m; a = -1.0; }
	if ( x < 0.0 ) { x = -x; a = -a; }

	// iM is "inverse m" used in a few places below
	double iM = 1e10;
	if ( m > 1.0e-10 )
	{
       iM = 1.0 / m;
    }

    // L is the upper bound on our curves, where we have rejoined the y = x line
    double L = iM < m * 2.0 ? m * 2.0 : iM;

	// "Non Curved"
	// Covers x >= L, or always true if m == 1.0
	// y = x  i.e. not distorted
	if ( ( x > L ) || ( m == 1.0 ) )
	{
		return a * x;
	}

	if ( ( m < 1.0 ) && ( x <= 1.0 ) )
	{
		// Bezier Curve #1
		// Covers 0 <= $m <= 1.0, 0 <= $x <= 1.0
		// Control points are (0,0), (m,m) and (1,m)

		t = x; // Special case when m == 0.5
		if ( abs(m-0.5) > 1e-10 )
		{
			t = ( -1.0 * m + sqrt(  m * m + ( 1.0 - 2.0 * m) * x ) ) / ( 1.0 - 2.0 * m );
		}
		return a * ( x + ( m - 1.0 ) * t * t );
	}

	if  ( ( 1.0 < m ) && ( x <= 1.0 ) )
	{
		// Bezier Curve #2
		// Covers m >= 1.0, 0 <= x <= 1.0
		// Control points are (0,0), (iM,iM) and (1,m)

		t = x; // Special case when m == 2
		if ( abs(m-2.0) > 1e-10 )
		{
			t = ( -1.0 * iM + sqrt( iM * iM + ( 1.0 - 2.0 * iM ) * x ) ) / ( 1 - 2 * iM );
		}
		return a * ( x + ( m - 1.0 ) * t * t );
	}

	if ( m < 1.0 )
	{
		// Bezier Curve #3
		// Covers 0 <= m <= 1.0, 1 <= x <= L
		// Control points are (1,m), (1,1) and (L,L)
		// (L is x value (>1) where we re-join y = x line, and is maximum( iM, 2 * m )

		t =	sqrt( ( x - 1.0 ) / ( L - 1.0 ) );
		return a * ( x  +  ( m - 1.0 ) * t * t  +  2 * ( 1.0 - m ) * t  + ( m - 1.0 ) );
	}

	// Curve #4
	// Covers 1.0 <= m, 1 <= x <= L
	// Control points are (1,m), (m,m) and (L,L)
	// (L is x value (>1) where we re-join y = x line, and is maximum( iM, 2 *  m )

	t =	( 1.0 - m ) + sqrt( ( m - 1.0 ) * ( m - 1.0 ) + ( x - 1.0 ) );
	return a * ( x + ( m - 1.0 ) * t * t - 2.0 * ( m - 1.0 ) *  t + (  m - 1.0 ) );
}


// Handle potentially many types of interpolation routine in future  . . .
inline double interpolate( double x, double m, int lerp_type )
{
    switch ( lerp_type )
    {
           case LERP_LINEAR:
                return x * m;
           case LERP_BEZIER:
                return bezier_quad_map( x, m );
    }
    return x * m;
}

inline void synthsincos( Variation* vp, double theta, double* s, double* c, int sine_type )
{
    fsincos( theta, s, c );
    switch ( sine_type )
    {
           case SINCOS_MULTIPLY:
                *s = (*s) * synth_value( vp, theta );
                *c = (*c) * synth_value( vp, theta + M_PI/2.0 );
                break;
           case SINCOS_MIXIN:
                *s = ( 1.0 - VAR(synth_mix) ) * (*s) + ( synth_value( vp, theta ) - 1.0 );
                *c = ( 1.0 - VAR(synth_mix) ) * (*c) + ( synth_value( vp, theta + M_PI/2.0 ) - 1.0 );
                break;
    }
    return;
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double Vx, Vy, radius, theta; // Position vector in cartesian and polar co-ords
    double theta_factor;          // Evaluation of synth() function for current point
    double s, c, mu;              // Handy temp variables, s & c => sine & cosine, mu = generic temp param

    switch( VAR(synth_mode) ) {

		case MODE_RAWCIRCLE:  // Power NO, Smooth YES
		    // Get current radius and angle
			Vx = FTx;
			Vy = FTy;
			radius = sqrt(Vx * Vx + Vy * Vy);
            theta = atan2(Vx, Vy);

            // Calculate new radius
            theta_factor = synth_value( vp, theta );
            radius = interpolate( radius, theta_factor, VAR(synth_smooth) );
            fsincos(theta, &s, &c);

            // Write to running totals for transform
            FPx += VVAR * radius * s;
            FPy += VVAR * radius * c;
			break;


		case MODE_RAWY:  // Power NO, Smooth YES
		    // Use x and y values directly
			Vx = FTx;
			Vy = FTy;

            // y value will be mapped according to synth(x) value
            theta_factor = synth_value( vp, Vx );

            // Write to running totals for transform
            FPx += VVAR * Vx;
            FPy += VVAR * interpolate( Vy, theta_factor, VAR(synth_smooth) );;
			break;


		case MODE_RAWX:  // Power NO, Smooth YES
		    // Use x and y values directly
			Vx = FTx;
			Vy = FTy;

            // x value will be mapped according to synth(y) value
            theta_factor = synth_value( vp, Vy );

            // Write to running totals for transform
            FPx += VVAR * interpolate( Vx, theta_factor, VAR(synth_smooth) );
            FPy += VVAR * Vy;
			break;


		case MODE_RAWXY:  // Power NO, Smooth YES
		    // Use x and y values directly
			Vx = FTx;
			Vy = FTy;

            // x value will be mapped according to synth(y) value
            theta_factor = synth_value( vp, Vy );
            FPx += VVAR * interpolate( Vx, theta_factor, VAR(synth_smooth) );

            // y value will be mapped according to synth(x) value
            theta_factor = synth_value( vp, Vx );
            FPy += VVAR * interpolate( Vy, theta_factor, VAR(synth_smooth) );
			break;


		case MODE_SPHERICAL:  // Power YES, Smooth YES
		    // Re-write of spherical with synth tweak
			Vx = FTx;
			Vy = FTy;
			radius = pow(Vx * Vx + Vy * Vy + EPS, ( VAR(synth_power) + 1.0 )/2.0);

            // Get angle and angular factor
            theta = atan2(Vx, Vy);
            theta_factor = synth_value( vp, theta );
            radius = interpolate( radius, theta_factor, VAR(synth_smooth) );
            fsincos(theta, &s, &c);

            // Write to running totals for transform
            FPx += VVAR * radius * s;
            FPy += VVAR * radius * c;
			break;


	    case MODE_BUBBLE:  // Power NO, Smooth YES
		    // Re-write of bubble with synth tweak
			Vx = FTx;
			Vy = FTy;
	        radius = sqrt(Vx * Vx + Vy * Vy) / ( (Vx * Vx + Vy * Vy)/4 + 1);

            // Get angle and angular factor
            theta = atan2(Vx, Vy);
            theta_factor = synth_value( vp, theta );
            radius = interpolate( radius, theta_factor, VAR(synth_smooth) );
            fsincos(theta, &s, &c);

            // Write to running totals for transform
            FPx += VVAR * radius * s;
            FPy += VVAR * radius * c;
			break;


	    case MODE_BLUR_LEGACY:  // Power YES, Smooth YES
	        // "old" blur style, has some problems with moire-style artefacts
			radius = ( random01() + random01() + 0.002 * random01() ) / 2.002;
			theta = 2.0 * M_PI * random01() - M_PI;
		    Vx = radius * sin(theta);
		    Vy = radius * cos(theta);
		    radius = pow( radius * radius + EPS, VAR(synth_power)/2.0);

            // Get angle and angular factor
            theta_factor = synth_value( vp, theta );
            radius = VVAR * interpolate( radius, theta_factor, VAR(synth_smooth) );

            // Write back to running totals for new vector
            FPx += Vx * radius;
            FPy += Vy * radius;
            break;


	    case MODE_BLUR_NEW:  // Power YES, Smooth YES
	        // Blur style, with normal smoothing function

            // Choose radius randomly, then adjust distribution using pow
            radius = 0.5 * ( random01() + random01() );
			theta = 2 * M_PI * random01() - M_PI;
		    radius = pow( radius * radius + EPS, - VAR(synth_power)/2.0 );

            // Get angular factor defining the shape
            theta_factor = synth_value( vp, theta );

            // Get final radius after synth applied
            radius = interpolate( radius, theta_factor, VAR(synth_smooth) );
            fsincos(theta, &s, &c);

            // Write to running totals for transform
            FPx += VVAR * radius * s;
            FPy += VVAR * radius * c;
            break;


	    case MODE_BLUR_RING:  // Power YES, Smooth YES
	        // Blur style, with normal smoothing function

            radius = 1.0 + 0.1 * ( random01() + random01() - 1.0 ) * VAR(synth_power);
			theta = 2 * M_PI * random01() - M_PI;

            // Get angular factor defining the shape
            theta_factor = synth_value( vp, theta );

            // Get final radius after synth applied
            radius = interpolate( radius, theta_factor, VAR(synth_smooth) );
            fsincos(theta, &s, &c);

            // Write to running totals for transform
            FPx += VVAR * radius * s;
            FPy += VVAR * radius * c;
            break;


	    case MODE_BLUR_RING2:  // Power YES, Smooth NO
	        // Simple, same-thickness ring

            // Choose radius randomly, then adjust distribution using pow
			theta = 2 * M_PI * random01() - M_PI;

            radius = pow( random01() + EPS, VAR(synth_power) );

            // Get final radius after synth applied
            radius = synth_value( vp, theta ) + 0.1 * radius;
            fsincos(theta, &s, &c);

            // Write to running totals for transform
            FPx += VVAR * radius * s;
            FPy += VVAR * radius * c;
            break;

        case MODE_SHIFTNSTRETCH: // Power YES, Smooth NO
            // Use (adjusted) radius to move point around circle
            Vx = FTx;
            Vy = FTy;

            radius = pow(Vx * Vx + Vy * Vy + EPS, VAR(synth_power) / 2.0);

            theta = atan2(Vx, Vy) - 1.0 + synth_value(vp, radius);

            fsincos(theta, &s, &c);

            // Write to running totals for transform
            FPx += VVAR * radius * s;
            FPy += VVAR * radius * c;
            break;

        case MODE_SHIFTTANGENT: // Power YES, Smooth NO
            // Use (adjusted) radius to move point tangentially to circle
            Vx = FTx;
            Vy = FTy;

            radius = pow(Vx * Vx + Vy * Vy + EPS, VAR(synth_power) / 2.0);

            theta = atan2(Vx, Vy) - 1.0 + synth_value(vp, radius);

            // Adjust  Vx and Vy directly
            mu = synth_value(vp, radius) - 1.0;
            Vx += mu * c;
            Vy -= mu * s;

            // Write to running totals for transform
            FPx += VVAR * Vx;
            FPy += VVAR * Vy;
            break;

	    case MODE_SHIFTTHETA:  // Power YES, Smooth NO
            // Use (adjusted) radius to move point around circle
            Vx = FTx;
            Vy = FTy;

            radius = pow(Vx * Vx + Vy * Vy + EPS, VAR(synth_power)/2.0 );

            theta  = atan2( Vx, Vy ) - 1.0 + synth_value( vp, radius );

            fsincos(theta, &s, &c);

            // Write to running totals for transform
            FPx += VVAR * radius * s;
            FPy += VVAR * radius * c;
            break;


    	case MODE_BLUR_ZIGZAG:  // Power YES, Smooth YES
		    // Blur effect based on line segment
            // theta is used as x value
            // Vy is y value
            Vy    = 1.0 + 0.1 * ( random01() + random01() - 1.0 ) * VAR(synth_power);
			theta = 2.0 * asin( (random01()- 0.5) * 2.0 );

            // Get angular factor defining the shape
            theta_factor = synth_value( vp, theta );

            // Get new location
            Vy = interpolate( Vy, theta_factor, VAR(synth_smooth) );

            // Write to running totals for transform
            FPx += VVAR * ( theta / M_PI );
            FPy += VVAR * ( Vy - 1.0 );
            break;


        case MODE_SHIFTX:  // Power NO, Smooth YES
		    // Use x and y values directly
			Vx = FTx;
			Vy = FTy;

            // Write to running totals for transform
            FPx += VVAR * ( Vx + synth_value( vp, Vy ) - 1.0);
            FPy += VVAR * Vy;
			break;


        case MODE_SHIFTY:  // Power NO, Smooth NO
		    // Use x and y values directly
			Vx = FTx;
			Vy = FTy;

            // Write to running totals for transform
            FPx += VVAR * Vx;
            FPy += VVAR * ( Vy + synth_value( vp, Vx ) - 1.0);

            break;


        case MODE_SHIFTXY:  // Power NO, Smooth NO
		    // Use x and y values directly
			Vx = FTx;
			Vy = FTy;

            // Write to running totals for transform
            FPx += VVAR * ( Vx + synth_value( vp, Vy ) - 1.0);
            FPy += VVAR * ( Vy + synth_value( vp, Vx ) - 1.0);

            break;


        case MODE_SINUSOIDAL:  // Power NO, Smooth NO
             Vx = FTx;
             Vy = FTy;

             // The default mix=0 is same as normal sin
             FPx +=  VVAR * ( synth_value( vp, Vx ) - 1.0 + (1.0-VAR(synth_mix)) * sin (Vx) );
             FPy +=  VVAR * ( synth_value( vp, Vy ) - 1.0 + (1.0-VAR(synth_mix)) * sin (Vy) );

             break;


        case MODE_SWIRL:  // Power YES, Smooth WAVE
             Vx = FTx;
             Vy = FTy;

             radius = pow( Vx * Vx + Vy * Vy + EPS, VAR(synth_power)/2.0 );

             // Synth-modified sine & cosine
             synthsincos( vp, radius, &s, &c, VAR(synth_smooth) );

             FPx +=  VVAR * (s * Vx - c * Vy);
	         FPy +=  VVAR * (c * Vx + s * Vy);

             break;


        case MODE_HYPERBOLIC:  // Power YES, Smooth WAVE
             Vx = FTx;
             Vy = FTy;

             radius = pow(Vx * Vx + Vy * Vy + EPS, VAR(synth_power)/2.0 );

             theta  = atan2( Vx, Vy );

             // Synth-modified sine & cosine
             synthsincos( vp, theta, &s, &c, VAR(synth_smooth) );

             FPx += VVAR * s / radius;
             FPy += VVAR * c * radius;

             break;


        case MODE_JULIA: // Power YES, Smooth WAVE
            Vx = FTx;
            Vy = FTy;

            radius = pow(Vx * Vx + Vy * Vy + EPS, VAR(synth_power)/4.0 );

            theta  = atan2( Vx, Vy )/2.0;

            if ( random01() < 0.5 ) theta += M_PI;

            // Synth-modified sine & cosine
            synthsincos( vp, theta, &s, &c, VAR(synth_smooth) );

            FPx += VVAR * radius * c;
            FPy += VVAR * radius * s;

            break;


        case MODE_DISC: // Power YES, Smooth WAVE
            Vx = FTx;
            Vy = FTy;

            theta = atan2( Vx, Vy ) / M_PI;

            radius  = M_PI * pow(Vx * Vx + Vy * Vy + EPS, VAR(synth_power)/2.0 );

            // Synth-modified sine & cosine
            synthsincos( vp, radius, &s, &c, VAR(synth_smooth) );

            FPx = VVAR * s * theta;
            FPy = VVAR * c * theta;

            break;


        case MODE_RINGS: // Power PARAM, Smooth WAVE

            Vx = FTx;
            Vy = FTy;
            radius = sqrt( Vx * Vx + Vy * Vy );
            theta = atan2( Vx, Vy );

            mu = VAR(synth_power) * VAR(synth_power) + EPS;

            radius += -2.0 * mu * (int)((radius + mu)/( 2.0 * mu )) + radius * ( 1.0 - mu );

            synthsincos( vp, radius, &s, &c, VAR(synth_smooth) );

            FPx += VVAR * s * radius;
            FPy += VVAR * c * radius;

            break;


        case MODE_CYLINDER: // Power YES, Smooth WAVE
            Vx = FTx;
            Vy = FTy;
            radius = pow(Vx * Vx + Vy * Vy + EPS, VAR(synth_power)/2.0 );

            // Modified sine only used here
            synthsincos( vp, Vx, &s, &c, VAR(synth_smooth) );

            FPx += VVAR * radius * s;
            FPy += VVAR * radius * Vy;

            break;

        case MODE_XMIRROR: // Power NO, Smooth NO
            Vx = FTx;
            Vy = FTy;

            // Modified sine only used here
            mu = synth_value(vp, Vx) - 1.0;
            Vy = 2.0 * mu - Vy;

            FPx += VVAR * Vx;
            FPy += VVAR * Vy;

            break;

        case MODE_XYMIRROR: // Power NO, Smooth NO
            Vx = FTx;
            Vy = FTy;

            // radius sneakily being used to represent something completely different, sorry!
            mu = synth_value(vp, Vx) - 1.0;
            radius = synth_value(vp, Vy) - 1.0;
            Vy = 2.0 * mu - Vy;
            Vx = 2.0 * radius - Vx;

            FPx += VVAR * Vx;
            FPy += VVAR * Vy;

            break;

        case MODE_SPHERICAL2: // Power YES, Smooth YES
            Vx = FTx;
            Vy = FTy;
            radius = sqrt(Vx * Vx + Vy * Vy);

            // Get angle and angular factor
            theta = atan2(Vx, Vy);
            theta_factor = synth_value(vp, theta);
            radius = interpolate(radius, theta_factor, VAR(synth_smooth));
            radius = pow(radius, VAR(synth_power));
            fsincos(theta, &s, &c);

            // Write to running totals for transform
            FPx += VVAR * radius * s;
            FPy += VVAR * radius * c;
            break;
	}

    return TRUE;
}
