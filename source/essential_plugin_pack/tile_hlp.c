typedef struct {
    double tile_hlp_width, tile_hlp_edge;
    double tile_hlp_pi_width, tile_hlp_v_width;
} Variables;

#include "apoplugin.h"

APO_PLUGIN("tile_hlp");

APO_VARIABLES(
        VAR_REAL_NONZERO(tile_hlp_width, 1.0),
        VAR_REAL(tile_hlp_edge, 1.0)
        );

int PluginVarPrepare(Variation* vp) {
    VAR(tile_hlp_v_width) = VAR(tile_hlp_width) * VVAR;
    return TRUE;
}

int PluginVarCalc(Variation* vp) {
    double x = FTx / VAR(tile_hlp_width);
    int pos = x > 0;
    if (cos((pos ? x - (int) x : x + (int) x) * M_PI) < rand() * 2.0 / RAND_MAX - 1.0)
        FPx = pos ? -VAR(tile_hlp_v_width) : VAR(tile_hlp_v_width);
    FPx += VVAR * FTx;
    FPy += VVAR * FTy;
    return TRUE;
}