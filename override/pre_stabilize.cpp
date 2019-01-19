/*
    Apophysis Plugin: pre_stabilize

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PreStabilizeFunc.java

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

#include "datahelpers.h"

typedef struct
{
	int n;
	int seed;
	double p;
	int dc;
	double x[64];
	double y[64];
	double c[64];
	bool start = true;
	double nextColor;
	double colorDelta;
} Variables;

#define APO_VARIABLE_PREFIX "pre_stabilize_"
#include "plugin.h"

APO_PLUGIN("pre_stabilize");
APO_VARIABLES(
	VAR_INTEGER(n, 4),
	VAR_INTEGER(seed, (int) (random01() * 100000)),
	VAR_REAL(p, 0.1),
	VAR_INTEGER(dc, 0),

);



int PluginVarPrepare(Variation* vp)
{
    if (VAR(n) < 1)
      VAR(n) = 1;

    if (VAR(n) > 64)
        VAR(n) = 64;
    
    srand(VAR(seed));
    VAR(nextColor) = 0.5;
    VAR(colorDelta) = 1.0;

    for (int i = 0; i < VAR(n); i++) {
      VAR(x)[i] = GOODRAND_01() * 2 - 1;
      VAR(y)[i] = GOODRAND_01() * 2 - 1;
      VAR(c)[i] = VAR(nextColor);
      VAR(nextColor) += VAR(colorDelta);
      if (VAR(nextColor) >= 1) {
        VAR(colorDelta) /= 2;
        VAR(nextColor) = VAR(colorDelta) / 2;
      }
    }

    VAR(start) = true;



    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // pre_stabilize by Rick Sidwell, works as glitch repellent

    if (VAR(start) || rand() < VAR(p) / 1000) {
      VAR(start) = false;
      int i = GOODRAND_0X(VAR(n));
      FTx = VAR(x)[i];
      FTy = VAR(y)[i];
      FTz = 0;
      if (VAR(dc) != 0) TC = VAR(c)[i];
    }


    return TRUE;
}


