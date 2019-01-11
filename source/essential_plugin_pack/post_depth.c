typedef struct {
    double post_depth_power;
} Variables;

#include "apoplugin.h"

APO_PLUGIN("post_depth");
APO_VARIABLES(
        VAR_REAL(post_depth_power, 1.0)
        );

int PluginVarPrepare(Variation* vp) {
    return 1;
}

int PluginVarCalc(Variation* vp) {
    double coeff = fabs(FTz);
    if (coeff != 0.0 && VAR(post_depth_power) != 1.0)
        coeff = exp(log(coeff) * VAR(post_depth_power));

    FPx = VVAR * (FTx + FPx * coeff);
    FPy = VVAR * (FTy + FPy * coeff);
    FPz = VVAR * (FTz + FPz * coeff);
    return 1;
}
