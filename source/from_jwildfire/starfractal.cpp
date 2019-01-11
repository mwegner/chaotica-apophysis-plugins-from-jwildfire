/*
    Apophysis Plugin: starfractal

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/StarFractalFunc.java

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
    int m;

	// not exposed
	double a[25];
	double b[25];
	double x, y, x1, y1;

} Variables;

#include "plugin.h"

APO_PLUGIN("starfractal");
APO_VARIABLES(
	VAR_INTEGER_RANGE(m, 3, 10, 3),
);

int PluginVarPrepare(Variation* vp)
{
	VAR(x) = 1.0;
	VAR(y) = 1.0;

	if (VAR(m) >= 10) {
		VAR(m) = 10;
	}

	for (int i = 0; i < VAR(m); i++) {
		VAR(a)[2 * i] = cos(2 * M_PI * (i + 1) / (double) VAR(m));
		VAR(b)[2 * i] = sin(2 * M_PI * (i + 1) / (double) VAR(m));
    }

    for (int i = 0; i < VAR(m); i++) {
		VAR(a)[2 * i + 1] = 0.5 * (cos(2 * M_PI * (i + 1) / (double) VAR(m)) + cos(2 * M_PI * i / (double) VAR(m)));
		VAR(b)[2 * i + 1] = 0.5 * (sin(2 * M_PI * (i + 1) / (double) VAR(m)) + sin(2 * M_PI * i / (double) VAR(m)));
    }

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
	int c = (int) (rand() % (VAR(m) * 2));

	VAR(x1) = (  VAR(x) / ( VAR(x) * VAR(x) + VAR(y) * VAR(y) ) ) / 3 + VAR(a)[c];
    VAR(y1) = ( -VAR(y) / ( VAR(x) * VAR(x) + VAR(y) * VAR(y) ) ) / 3 + VAR(b)[c];
    VAR(x) = VAR(x1) / ( VAR(x1) * VAR(x1) + VAR(y1) * VAR(y1) );
    VAR(y) = VAR(y1) / ( VAR(x1) * VAR(x1) + VAR(y1) * VAR(y1) );

    FPx = VAR(x) * VVAR;
    FPy = VAR(y) * VVAR;

    return TRUE;
}
