typedef struct {
    double post_scrop_radius, post_scrop_scatter, post_scrop_power, post_scrop_offset, post_scrop_edge, post_scrop_distortion, post_scrop_rotation, post_scrop_roundstr, post_scrop_roundwidth;
    double post_scrop_workpower, post_scrop_workradius, post_scrop_alpha, post_scrop_roundcoeff, post_scrop_workrotation;
    double post_scrop_x, post_scrop_y, post_scrop_z, post_scrop_c;
    double *xi, *yi, *zi;
    int post_scrop_mode, post_scrop_cropmode, post_scrop_static;
    int post_scrop_radial;
} Variables;

#include "apoplugin.h"

APO_PLUGIN("post_smartcrop");
APO_VARIABLES(
        VAR_REAL(post_scrop_power, 4.0),
        VAR_REAL(post_scrop_radius, 1.0),
        VAR_REAL(post_scrop_roundstr, 0.0),
        VAR_REAL(post_scrop_roundwidth, 1.0),
        VAR_REAL(post_scrop_distortion, 1.0),
        VAR_REAL(post_scrop_edge, 0.0),
        VAR_REAL(post_scrop_scatter, 0.0),
        VAR_REAL(post_scrop_offset, 0.0),
        VAR_REAL(post_scrop_rotation, 0.0),
        VAR_INTEGER_RANGE(post_scrop_cropmode, -1, 2, 1),
        VAR_INTEGER_RANGE(post_scrop_static, -1, 3, 1)
        );

int PluginVarPrepare(Variation* vp) {
    VAR(post_scrop_mode) = (VAR(post_scrop_power) > 0) == (VAR(post_scrop_radius) > 0);
    VAR(post_scrop_workradius) = fabs(VAR(post_scrop_radius));
    VAR(post_scrop_workpower) = fabs(VAR(post_scrop_power));
    if (VAR(post_scrop_workpower) < 2) {
        VAR(post_scrop_workpower) = VAR(post_scrop_workpower) * M_PI;
        VAR(post_scrop_radial) = 1;
    } else {
        VAR(post_scrop_radial) = 0;
        VAR(post_scrop_alpha) = M_2PI / VAR(post_scrop_workpower);
        VAR(post_scrop_roundcoeff) = VAR(post_scrop_roundstr) / sin(VAR(post_scrop_alpha) / 2) / VAR(post_scrop_workpower) * 2;
        VAR(post_scrop_workrotation) = VAR(post_scrop_rotation) * VAR(post_scrop_alpha);
    }
    VAR(post_scrop_x) = VAR(post_scrop_y) = VAR(post_scrop_z) = VAR(post_scrop_c) = 0;
    if (VAR(post_scrop_static) > 1) {
        VAR(xi) = vp->pFPx;
        VAR(yi) = vp->pFPy;
        VAR(zi) = vp->pFPz;
    } else {
        VAR(xi) = vp->pFTx;
        VAR(yi) = vp->pFTy;
        VAR(zi) = vp->pFTz;
    }
    return TRUE;
}

int PluginVarCalc(Variation* vp) {
    double ang, rad;
    const double *xi = VAR(xi), *yi = VAR(yi), *zi = VAR(zi);

    ang = atan2(*yi, *xi);
    rad = sqrt(*xi * *xi + *yi * *yi);

    if (VAR(post_scrop_radial))
	{
        double edge = VAR(post_scrop_edge) * (random01() - 0.5);
        double xang = ang / M_2PI + 1 + edge;
        xang = (xang - (int) xang) * M_2PI;

		if ((xang > VAR(post_scrop_workpower)) == VAR(post_scrop_mode))
		{
            if (VAR(post_scrop_cropmode) == 2)
			{
                if ((VAR(post_scrop_static) > 1) || (VAR(post_scrop_static) == -1))
				{
                    FPx = VAR(post_scrop_x);
                    FPy = VAR(post_scrop_y);
                    FPz = VAR(post_scrop_z);
                    TC = VAR(post_scrop_c);
                    return 1;
                }
				else
				{
					FPx += VAR(post_scrop_x);
					FPy += VAR(post_scrop_y);
					FPz += VAR(post_scrop_z);
					TC = VAR(post_scrop_c);
					return 1;
				}
            }
			else
			{
				double s, c;
				fsincos(((int) (random01() * 2)) ? VAR(post_scrop_workpower) + (random01() * VAR(post_scrop_scatter) + VAR(post_scrop_offset) + edge) * M_PI : -(random01() * VAR(post_scrop_scatter) + VAR(post_scrop_offset) + edge) * M_PI, &s, &c);

				if ((VAR(post_scrop_static) > 1) || (VAR(post_scrop_static) == -1))
				{
					FPx = VVAR * rad * c;
					FPy = VVAR * rad * s;
					FPz = VVAR * *zi;
					return 1;
				}
				else
				{
					FPx += VVAR * rad * c;
					FPy += VVAR * rad * s;
					FPz += VVAR * *zi;
					return 1;
				}
			}
        }
    }
	else
	{
		double coeff;

		if (VAR(post_scrop_distortion) == 0.0)
		{
            coeff = 1;
		}
        else
		{
            double xang = (ang + M_PI) / VAR(post_scrop_alpha);
            xang = xang - (int) xang;
            xang = (xang < 0.5) ? xang : 1 - xang;
            coeff = 1 / cos(xang * VAR(post_scrop_alpha));

			if (VAR(post_scrop_roundstr) != 0.0)
			{
                const double wwidth = ((VAR(post_scrop_roundwidth) != 1.0) ? exp(log(xang * 2) * VAR(post_scrop_roundwidth)) : (xang * 2)) * VAR(post_scrop_roundcoeff);
                coeff = fabs((1 - wwidth) * coeff + wwidth);
            }

            if (VAR(post_scrop_distortion) != 1.0)
			{
                coeff = exp(log(coeff) * VAR(post_scrop_distortion));
			}
        }

		const double xr = coeff * ((VAR(post_scrop_edge) != 0.0) ? VAR(post_scrop_workradius) + VAR(post_scrop_edge) * (random01() - 0.5) : VAR(post_scrop_workradius));

        if ((rad > xr) == VAR(post_scrop_mode))
		{
            if (VAR(post_scrop_cropmode))
			{
                if (VAR(post_scrop_cropmode) == 2)
				{
                    if ((VAR(post_scrop_static) > 1) || (VAR(post_scrop_static) == -1))
					{
                        FPx = VAR(post_scrop_x);
                        FPy = VAR(post_scrop_y);
                        FPz = VAR(post_scrop_z);
                        TC = VAR(post_scrop_c);
                        return 1;
                    }
					else
					{
						FPx += VAR(post_scrop_x);
						FPy += VAR(post_scrop_y);
						FPz += VAR(post_scrop_z);
						TC = VAR(post_scrop_c);
						return 1;
					}
                }

				double rdc = (VAR(post_scrop_cropmode) == -1) ? rad : xr + coeff * (random01() * VAR(post_scrop_scatter) + VAR(post_scrop_offset));
                double s, c;
                fsincos(ang + VAR(post_scrop_workrotation), &s, &c);

				if ((VAR(post_scrop_static) > 1) || (VAR(post_scrop_static) == -1))
				{
                    FPx = VVAR * rdc * c;
                    FPy = VVAR * rdc * s;
                    FPz = VVAR * *zi;
                    return 1;
                }
				else
				{
					FPx += VVAR * rdc * c;
					FPy += VVAR * rdc * s;
					FPz += VVAR * *zi;
		            return 1;
				}
            }
			else
			{
                if ((VAR(post_scrop_static) > 1) || (VAR(post_scrop_static) == -1))
				{
                    FPx = 0;
                    FPy = 0; // This is extremely problematic and won't work i think?
                    FPz = 0;

					return 1;
                }
            }
            return 1;
        }
    }

    if (VAR(post_scrop_static) == 3) {
        VAR(post_scrop_x) = VVAR * FTx;
        VAR(post_scrop_y) = VVAR * FTy;
        VAR(post_scrop_z) = VVAR * FTz;
    } else {
        VAR(post_scrop_x) = VVAR * *xi;
        VAR(post_scrop_y) = VVAR * *yi;
        VAR(post_scrop_z) = VVAR * *zi;
    }
    if (VAR(post_scrop_cropmode) == 2)
        VAR(post_scrop_c) = TC;

    if (VAR(post_scrop_static) > 0) {
        FPx = VAR(post_scrop_x);
        FPy = VAR(post_scrop_y);
        FPz = VAR(post_scrop_z);
        return 1;
    }

    FPx += VAR(post_scrop_x);
    FPy += VAR(post_scrop_y);
    FPz += VAR(post_scrop_z);
    return 1;
}