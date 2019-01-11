typedef struct {
    double sineblur_power;
} Variables;

#include "apoplugin.h"

APO_PLUGIN("sineblur");
APO_VARIABLES(
        VAR_REAL(sineblur_power, 1.0)
        );

int PluginVarPrepare(Variation* vp) {
    if (VAR(sineblur_power) < 0) VAR(sineblur_power) = 0.0;

    return TRUE;
}

int PluginVarCalc(Variation* vp) {
    double ang = random01() * M_2PI, r = VVAR * (VAR(sineblur_power) == 1.0 ? acos(random01() * 2 - 1) / M_PI : acos(exp(log(random01()) * VAR(sineblur_power)) * 2 - 1) / M_PI);
    double s, c;
    fsincos(ang, &s, &c);
    FPx += r * c;
    FPy += r * s;
    return TRUE;
}