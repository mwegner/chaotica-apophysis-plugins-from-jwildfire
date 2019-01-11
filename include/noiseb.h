/*
    Apophysis Plugin (Supporting Library)

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

double simplexNoise3D( double V[3] );
double simplexDNoise3D( double V[3], double R[3] );
double perlinNoise3D( double V[3], double aScale, double fScale, int octaves );
double perlinDNoise3D( double V[3], double R[3], double aScale, double fScale, int octaves );

// Cheap and cheerful vector definitions for 3D :-)
// They just make reading vector code based on arrays
// slightly nicer for me! E.g. use V[_x_] instead of V[0].

#define _x_ 0
#define _y_ 1
#define _z_ 2

