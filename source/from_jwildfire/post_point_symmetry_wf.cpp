/*
    Apophysis Plugin: post_point_symmetry

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
    double centre_x;
	double centre_y;
	int order;
	double colorshift;

	// not exposed
	double _sina[16];
	double _cosa[16];

} Variables;

#define APO_VARIABLE_PREFIX "post_point_symmetry_wf_"
#include "plugin.h"

APO_PLUGIN("post_point_symmetry_wf");
APO_VARIABLES(
	VAR_REAL(centre_x, 0.25),
	VAR_REAL(centre_y, 0.5),
	VAR_INTEGER(order, 3),
	VAR_REAL(colorshift, 0.0)
);

int PluginVarPrepare(Variation* vp)
{
	if (VAR(order) >= 16) {
		VAR(order) = 16;
	}

	double da = M_2PI / (double)VAR(order);
	double angle = 0.0;
	for (int i = 0; i < VAR(order); i++) {
		VAR(_sina)[i] = sin(angle);
		VAR(_cosa)[i] = cos(angle);
		angle += da;
	}

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
	double dx = (FPx - VAR(centre_x)) * VVAR;
	double dy = (FPy - VAR(centre_y)) * VVAR;
	int idx = rand() % VAR(order);

	FPx = VAR(centre_x) + dx * VAR(_cosa)[idx] + dy * VAR(_sina)[idx];
	FPy = VAR(centre_y) + dy * VAR(_cosa)[idx] - dx * VAR(_sina)[idx];
	TC = fmod(TC + idx * VAR(colorshift), 1.0);

    return TRUE;
}
