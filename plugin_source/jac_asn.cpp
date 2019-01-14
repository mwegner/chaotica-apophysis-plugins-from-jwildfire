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

// Apo Plugin by Dark-Beam: jac_asn
// Must define this structure before we include apoplugin.h
typedef struct
{
	double jac_asn_kr, jac_asn_ki;
	int jac_asn_type;
} Variables;

#include "plugin.h"

#include <complex>

typedef std::complex<double> cp_t;

// Set the name of this plugin
APO_PLUGIN("jac_asn");


// Define the Variables
APO_VARIABLES(
	VAR_REAL(jac_asn_kr, 0.5),
	VAR_REAL(jac_asn_ki, 0.0),
	VAR_INTEGER_RANGE(jac_asn_type,0,7,1)
);

// You must call the argument "vp".
int PluginVarPrepare(Variation* vp)
{
	// Always return TRUE.
	return TRUE;
}


// You must call the argument "vp".
int PluginVarCalc(Variation* vp)
{
	// plugin inverse jacobi_sn by DarkBeam, using Jacobi's incomplete ell.int. 1st kind
	cp_t geo1;
	using namespace std::complex_literals;

	double epsi = 1e-8;

	cp_t phi(FTx, FTy);
	cp_t modul(VAR(jac_asn_kr), VAR(jac_asn_ki));

	switch (VAR(jac_asn_type)) { // 1st iteration; apply transform to phi.
	case 0:
	case 4:
		phi = 0.5 * (phi + asin(modul*sin(phi))); // nothing; just EllipticF = invdn
		break;
	case 1:
	case 5:
	default:
		phi = 0.5 * (asin(phi) + asin(modul*phi)); // inverse of jacobi sn needs an arcsin of argument.
		// BUT sin(arcsin(x)) = x
		break;
	case 2:
	case 6:
		phi = 0.5 * (acos(phi) + asin(modul*sqrt(1. - phi * phi))); // inverse of jacobi cn needs an arccos of argument.
		// BUT sin(arccos(x)) = sqrt(1-x*x)
		break;
	case 3:
	case 7:
		phi = 1i * asinh(phi);
		phi = 0.5 * (phi + asin(modul*sin(phi))); // inverse of jacobi sc needs an i*arcsinh of argument.
		break;
	}

	if (VAR(jac_asn_type) > 3) { // SWAP modul & phi
		geo1 = phi;
		phi = modul;
		modul = geo1;
	}

	cp_t geo(VVAR); // should be 1. But we care for VVAR instead of multiplying after.

					// Method from Norbert Rosch, described in the paper:
					// The derivation of algorithms to compute
					// elliptic integrals of the first and second kind
					// by Landen transformation. (2011)
	for (int j = 0; j<10; j++) {

		if (norm(1. - modul) < epsi) {
			break; // enough iters.
		}
		if (j > 0)
			phi = 0.5 * (phi + asin(modul*sin(phi)));

		geo1 = 2. / (1. + modul);
		geo *= geo1;
		modul = geo1 * sqrt(modul);
	}
	phi = geo * log(tan(0.5 * phi + M_PI_4));

	FPx += phi.real();
	FPy += phi.imag();
	// Add 3D compatibility
	FPz += FTz;

	return TRUE;
}
