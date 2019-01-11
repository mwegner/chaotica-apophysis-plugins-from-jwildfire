typedef struct {
    int starblur_power;
    double starblur_range;
    double starblur_length, starblur_alpha;
} Variables;

#include "apoplugin.h"

APO_PLUGIN("starblur");
APO_VARIABLES(
        VAR_INTEGER_NONZERO(starblur_power, 5),
        VAR_REAL(starblur_range, 0.40162283177245455973959534526548)
        );

int PluginVarPrepare(Variation* vp) {
    VAR(starblur_alpha) = M_PI / VAR(starblur_power);
    VAR(starblur_length) = sqrt(1 + sqr(VAR(starblur_range)) - 2 * VAR(starblur_range) * cos(VAR(starblur_alpha)));
    VAR(starblur_alpha) = asin(sin(VAR(starblur_alpha)) * VAR(starblur_range) / VAR(starblur_length));
    return 1;
}

int PluginVarCalc(Variation* vp) {
    double f = random01() * VAR(starblur_power) * 2;
    double angle = trunc(f);
    f = f - angle;
    double x = f * VAR(starblur_length);
    double z = sqrt(1 + sqr(x) - 2 * x * cos(VAR(starblur_alpha)));
    if (((int) angle) % 2)
        angle = M_2PI / VAR(starblur_power) * (((int) angle) / 2) + asin(sin(VAR(starblur_alpha)) * x / z);
    else
        angle = M_2PI / VAR(starblur_power) * (((int) angle) / 2) - asin(sin(VAR(starblur_alpha)) * x / z);
    z = z * sqrt(random01());

    double s, c;
    fsincos(angle - M_PI_2, &s, &c);

    FPx += VVAR * z * c;
    FPy += VVAR * z * s;
    return 1;
}
