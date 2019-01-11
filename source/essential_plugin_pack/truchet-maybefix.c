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
        int Truchet_extended;
        double Truchet_exponent;
        double Truchet_arc_width;
        double Truchet_rotation;
        double Truchet_size;
        double Truchet_seed;
// ----------------------------
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
APO_PLUGIN("Truchet");

// Define the Variables
APO_VARIABLES(
VAR_INTEGER_RANGE(Truchet_extended, 0, 1, 0),
VAR_REAL_CYCLE(Truchet_exponent, 0.001, 2.0, 2.0),
VAR_REAL_CYCLE(Truchet_arc_width, 0.001, 1.0, 0.5),
VAR_REAL(Truchet_rotation,  0.0),
VAR_REAL_CYCLE(Truchet_size, 0.001, 10.0, 1.0),
//VAR_INTEGER_RANGE(Truchet_seed, 0, 99999,  12345)
VAR_REAL_RANGE(Truchet_seed, 0.0, DBL_MAX , 50.000) // REFUSE negative seeds

);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
    // be caref... no, VERY CAREFUL here
    VAR(scale) = (cos(-VAR(Truchet_rotation)) - sin(-VAR(Truchet_rotation))); // don't ask me why
    if (fabs(VVAR) > 0.001)
        VAR(scale) = VAR(scale) / VVAR; // avoid dividing by zero as soon as Apo fires up!
    VAR(exponent) = (VAR(Truchet_exponent) > 2.0 ? 2.0 : ( VAR(Truchet_exponent) < 0.001 ? 0.001 : VAR(Truchet_exponent)));
    VAR(onen) = 1.0 / VAR(exponent);
    VAR(width) = VAR(Truchet_arc_width) > 1.0 ? 1.0 : ( VAR(Truchet_arc_width) < 0.001 ? 0.001 : VAR(Truchet_arc_width));
    VAR(seed2) = 100.0;
    if (fabs(VAR(Truchet_seed)) > 0.001)
        VAR(seed2) =sqrt(fabs(VAR(Truchet_seed)) * 1.5+ EPS) / (fabs(VAR(Truchet_seed))+ EPS) * 0.5; // avoid dividing by zero as soon as Apo fires up!
    VAR(rmax) = 0.5 * ( saferpower(2.0, VAR(onen)) - 1.0) * VAR(width);

    return TRUE; // Always return TRUE.
}

// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
//VARIABLES
    double x, y;
    double r;
    double r0 = 0.0;
    double r1 = 0.0;

    int tiletype=0; // casted to int because double is useless :|
    double randint=0.0;
    double modbase=65535.0;
    double multiplier=32747.0;//1103515245;
    double offset=12345.0;
    double niter=0.0;

//INITIALISATION

    x = FTx*VAR(scale);
    y = FTy*VAR(scale);

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

//CALCULATE THE TILE TYPE
    /*
    if (seed == 0.0) tiletype == 0.0;
    else if (seed == 1.0) tiletype == 1.0;
    // o_O what does that mean? == for = ?
    */
    if ( (VAR(Truchet_seed) == 0.0) || (VAR(Truchet_seed) == 1.0) )
        tiletype = (int)(VAR(Truchet_seed));
    else {
         if (VAR(Truchet_extended) == 0) {
             double xrand = round(FTx);
             double yrand = round(FTy);
             xrand = xrand * VAR(seed2);
             yrand = yrand * VAR(seed2);
             niter = xrand + yrand + xrand*yrand;
             randint = (niter + VAR(Truchet_seed)) * VAR(seed2) * 0.5;
             randint = fmod((randint * multiplier + offset),modbase);
             tiletype = ((int)randint) % 2;
         }
         else {
             long int seed = (long int)(VAR(Truchet_seed));
             long int xrand = (long int)round(FTx);
             long int yrand = (long int)round(FTy);
             long int prn = xrand + yrand + xrand*yrand;
             prn = prn * 8291 + (long int)VAR(seed2);
             prn = (prn & 4)?prn-seed:prn^seed;
             prn = prn & 0xFFFF0000 |
                    ((prn << 8) & 0xFF00 ) | ((prn >> 8) & 0x00FF );
             prn = prn * multiplier;
             tiletype = prn % 2;

             /*
             // original scramble mode = DANGEROUS infinite cycles! don't!
             while (randiter < niter) {
                   randiter += 1;
                   randint = fmod((randint * multiplier+offset), modbase);
             }
             */
         }

    }

//DRAWING THE POINTS
    if (tiletype < 1) {  //Slow & fast drawmodes were identical: merged
       // I use saferpower to stay away from exceptions
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


    r = fabs(r0 - 0.5); // avoid an useless division!!!
       if (r < VAR(rmax)) {
            FPx += VAR(Truchet_size)*(x + floor(FTx));
            FPy += VAR(Truchet_size)*(y + floor(FTy));
       }

    r = fabs(r1 - 0.5);
       if (r < VAR(rmax)) {
            FPx += VAR(Truchet_size)*(x + floor(FTx));
            FPy += VAR(Truchet_size)*(y + floor(FTy));
       }

    return TRUE;
}
