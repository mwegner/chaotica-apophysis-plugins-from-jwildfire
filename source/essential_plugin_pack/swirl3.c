typedef struct {
    double swirl3_shift;
} Variables;

#include "apoplugin.h"

APO_PLUGIN("swirl3");
APO_VARIABLES(
        VAR_REAL(swirl3_shift, 0.5)
        );

int PluginVarPrepare(Variation* vp) {
    return TRUE;
}

int PluginVarCalc(Variation* vp) {
    double rad = sqrt(FTx * FTx + FTy * FTy);
    double ang = atan2(FTy, FTx) + log(rad) * VAR(swirl3_shift);
    double s, c;
    fsincos(ang, &s, &c);
    FPx += VVAR * rad * c;
    FPy += VVAR * rad * s;
    return 1;
}
