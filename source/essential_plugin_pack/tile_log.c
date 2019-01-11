typedef struct {
    double tile_log_spread;
} Variables;

#include "apoplugin.h"

APO_PLUGIN("tile_log");

APO_VARIABLES(
        VAR_REAL(tile_log_spread, 1.0)
        );

int PluginVarPrepare(Variation* vp) {
    return TRUE;
}

int PluginVarCalc(Variation* vp) {

    FPx += VVAR * (FTx + round(log(random01()) * (rand() % 2 ? VAR(tile_log_spread) : -VAR(tile_log_spread))));
    FPy += VVAR * FTy;

    return TRUE;
}
