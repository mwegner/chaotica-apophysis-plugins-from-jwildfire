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

    FIXED BY DARKBEAM :D
*/

// Must define this structure before we include apoplugin.h
typedef struct
{
        double tf_exponent;
        double tf_arc_width;
        double tf_seed;
        // ---------------------------------
        double exponent, onen, width, seed, seed2;
        double rmax, scale;
} Variables;

double saferpower(double b, double e);

#include "apoplugin.h"
//#include "apotest.h"

double saferpower(double b, double e) {
    // return pow(fabs(b) + EPS, e);
    double fbs = fabs(b);
    if (fbs < 1E-10)
        return fbs;
    return exp(e*log(fbs + 1E-10));
}

// Set the name of this plugin
APO_PLUGIN("Truchet_fill");

// Define the Variables
APO_VARIABLES(
    VAR_REAL_CYCLE(tf_exponent, 0.001, 2.0, 2.0),
    VAR_REAL_CYCLE(tf_arc_width, 0.001, 1.0, 0.5),
    VAR_REAL(tf_seed, 0)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    // be caref... no, VERY CAREFUL here
    VAR(exponent) = (VAR(tf_exponent) > 2.0 ? 2.0 : ( VAR(tf_exponent) < 0.001 ? 0.001 : VAR(tf_exponent)));
    VAR(onen) = 1.0 / VAR(exponent);
    VAR(width) = VAR(tf_arc_width) > 1.0 ? 1.0 : ( VAR(tf_arc_width) < 0.001 ? 0.001 : VAR(tf_arc_width));
    VAR(seed2) = 100.0;
    if ((VAR(tf_seed)) > 0.001)
        VAR(seed2) = sqrt(VAR(tf_seed) * 1.5) / (VAR(tf_seed) * 0.5) * 0.25; // avoid dividing by zero as soon as Apo fires up!
    VAR(rmax) = 0.5 * ( saferpower(2.0, VAR(onen)) - 1.0) * VAR(width);
    VAR(scale) = 1.0;
    if (fabs(VVAR) > 0.001)
        VAR(scale) = 1.0 / VVAR; // avoid dividing by zero as soon as Apo fires up!
    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
    double x = FTx*VAR(scale);
    double y = FTy*VAR(scale);
    double tiletype = 0.0;
    double r, r0, r1, r00, r11;
    double x1 = 0.0, y1 = 0.0;

    r = x - round(x);
      if (r < 0.0)
         x = 1.0+r;
      else
         x = r;

    r = y - round(y);
      if (r < 0.0)
         y = 1.0+r;
      else
         y = r;

    if (VAR(tf_seed) != 0.0)
    {
        if (VAR(tf_seed) == 1.0)
            {
                tiletype = 1.0;
            }
        else {
            double xrand = round(fabs(FTx)) * VAR(seed2);
            double yrand = round(fabs(FTy)) * VAR(seed2);
            double niter = xrand + yrand + xrand*yrand;
            double randint = (VAR(tf_seed) + niter) * VAR(seed2) * 0.5;
            tiletype = fmod(randint * 32747.0 + 12345.0, 2.0);
        }
    }

        if (tiletype < 1.0) {  //Slow drawmode
           r0 = saferpower((saferpower(x, VAR(exponent))
                            + saferpower(y, VAR(exponent))), VAR(onen));
           r1 = saferpower((saferpower(x-1.0, VAR(exponent))
                            + saferpower(y-1.0, VAR(exponent))), VAR(onen));
        }
        else {
           r0 = saferpower((saferpower(x-1.0, VAR(exponent))
                            + saferpower(y, VAR(exponent))), VAR(onen));
           r1 = saferpower((saferpower(x, VAR(exponent))
                            + saferpower(y-1.0, VAR(exponent))), VAR(onen));
        }

    r00 = fabs(r0 - 0.5);
       if (r00 < VAR(rmax)) {
            x1 = 2.0 * ( x + floor(FTx) );
            y1 = 2.0 * ( y + floor(FTy) );
       }

    r11 = fabs(r1 - 0.5);
       if (r11 < VAR(rmax)) {
            FPx += x1 + 2.0 * ( x + floor(FTx) ) - FTx;
            FPy += y1 + 2.0 * ( y + floor(FTy) ) - FTy;
       }
       else
       {
           FPx += x1 - FTx;
           FPy += y1 - FTy;
       }

    return TRUE;
}
