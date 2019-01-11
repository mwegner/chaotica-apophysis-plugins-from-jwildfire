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
	double edisc_vvar;
} Variables;

#include "apoplugin.h"

// Set the name of this plugin
APO_PLUGIN("edisc");

// Define the Variables
APO_VARIABLES(
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
	VAR(edisc_vvar) = VVAR / 11.57034632;
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
	double tmp = FTy * FTy + FTx * FTx + 1.0;
	double tmp2 = 2.0 * FTx;
	double r1 = sqrt(tmp + tmp2);
	double r2 = sqrt(tmp - tmp2);
	double xmax = (r1 + r2) * 0.5;
	double snv, csv, snhu, cshu;
	double expu, expuinv;

    fsincos(log(xmax + sqrt(xmax - 0.99999999999)), &snv, &csv); // leaves an epsilon to prevent bugs
    sinhcosh(-acos(FTx / xmax), &snhu, &cshu);

    if (FTy > 0.0)
        snv = -snv;

    FPx += VAR(edisc_vvar) * cshu * csv;
    FPy += VAR(edisc_vvar) * snhu * snv;

    return TRUE;
}
