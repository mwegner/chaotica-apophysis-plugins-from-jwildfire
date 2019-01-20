#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: %name%

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/%java%

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

%headers%

#include "datahelpers.h"

%consts%

typedef struct
{
%struct%
    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "%name%_"
#include "plugin.h"

APO_PLUGIN("%name%");
APO_VARIABLES(
%variables%
);

%functions%

int PluginVarPrepare(Variation* vp)
{
%prepare%
    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
%calc%

    return TRUE;
}


