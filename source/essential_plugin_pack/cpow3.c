typedef struct {
    double cpow3_r, cpow3_d, cpow3_spread;
    int cpow3_divisor;

    double cpow3_a;
    double c, half_c;
    double d, half_d;
    double ang, cpow3_coeff;
} Variables;

#include "apoplugin.h"

APO_PLUGIN("cpow3");

APO_VARIABLES(
        VAR_REAL(cpow3_r, 1.0),
        VAR_REAL_NONZERO(cpow3_d, 1.0),
        VAR_INTEGER_NONZERO(cpow3_divisor, 1),
        VAR_REAL(cpow3_spread, 1.0)
        );

int PluginVarPrepare(Variation* vp) {
    VAR(ang) = M_2PI / ((double) VAR(cpow3_divisor));
    VAR(cpow3_a) = atan2((VAR(cpow3_d) < 0 ? -log(-VAR(cpow3_d)) : log(VAR(cpow3_d))) * VAR(cpow3_r), M_2PI);
    VAR(c) = cos(VAR(cpow3_a)) * VAR(cpow3_r) * cos(VAR(cpow3_a)) / ((double) VAR(cpow3_divisor));
    VAR(d) = cos(VAR(cpow3_a)) * VAR(cpow3_r) * sin(VAR(cpow3_a)) / ((double) VAR(cpow3_divisor));
    VAR(half_c) = VAR(c) / 2;
    VAR(half_d) = VAR(d) / 2;
    VAR(cpow3_coeff) = VAR(d) == 0 ? 0 : -0.095 * VAR(cpow3_spread) / VAR(d);
    return TRUE;
}

int PluginVarCalc(Variation* vp) {
    double s, c;
    double a = atan2(FTy, FTx);

    if (a < 0) a += M_2PI;
    if (cos(a / 2) < rand() * 2.0 / RAND_MAX - 1.0)
        a -= M_2PI;
    a += (rand() % 2 ? M_2PI : -M_2PI) * round(log(random01()) * VAR(cpow3_coeff));

    double lnr2 = log(FTx * FTx + FTy * FTy);

    double r = VVAR * exp(VAR(half_c) * lnr2 - VAR(d) * a);

    fsincos(VAR(c) * a + VAR(half_d) * lnr2 + VAR(ang) * rand(), &s, &c);

    FPx += r * c;
    FPy += r * s;

    return TRUE;
}
