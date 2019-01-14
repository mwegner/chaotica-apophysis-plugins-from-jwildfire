// a quick-and-dirty as-needed port of https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/base/mathlib/Complex.java
// supports a couple of the variations, but nowhere near fully featured or even structured

#include <complex>

using namespace std;
typedef complex<double> Complex;
#include "c8lib.hpp"

inline Complex complexScale(Complex z, double mul)
{
    Complex result (z.real() * mul, z.imag() * mul);
    return result;
}

inline Complex complexLog(Complex z)
{
    Complex result (0.5 * log(z.real() * z.real() + z.imag() * z.imag() + 1e-20), atan2(z.imag(), z.real()));
    return result;
}

inline Complex complexFlip(Complex z)
{
    Complex result (z.imag(), z.real());
    return result;
}

inline Complex complexSqrt(Complex z)
{
    // uses the exact formula and the expansion...
    // sqrt(a+i b) = sqrt(Radius + re) + i * sqrt(Radius - re)
    double Rad = hypot(z.real(), z.imag());
    double sb = (z.imag() < 0) ? -1 : 1;
    double im = sb * sqrt(0.5 * (Rad - z.real()));
    double re = sqrt(0.5 * (Rad + z.real()));

    Complex result(re, im);
    return result;
}

inline Complex complexSqr(Complex z)
{
    double r2 = z.real() * z.real() - z.imag() * z.imag();
    double i2 = 2 * z.real() * z.imag();
    Complex result(r2, i2);
    return result;
}


inline Complex complexToP(Complex z)
{
    Complex result (hypot(z.real(), z.imag()), atan2(z.real(), z.imag()));
    return result;
}

inline double complexMag2(Complex z)
{
    return z.real() * z.real() + z.imag() * z.imag();
}

inline double complexMagInv(Complex z)
{
    double M2 = complexMag2(z);
    return (M2 < 1e-100 ? 1.0 : 1.0 / M2);
}

inline Complex complexRecip(Complex z)
{
    double mi = complexMagInv(z);

    Complex result(z.real() * mi, -z.imag() * mi);

    return result;
}


inline Complex complexPow(Complex z, double exp)
{
    // some obvious cases come at first
    // instant evaluation for (-2, -1, -0.5, 0, 0.5, 1, 2)
    if (exp == 0.0) {
        Complex result(1.0, 0.0);
        return result;
    }
    double ex = fabs(exp);
    if (exp < 0) {
        return complexRecip(z);
    }
    if (ex == 0.5) {
        return complexSqrt(z);
    }
    if (ex == 1.0) {
        return z;
    }
    if (ex == 2.0) {
        return complexSqr(z);
    }
    // In general we need sin, cos etc
    Complex PF = complexToP(z);
    double re = pow(PF.real(), ex);
    double im = PF.imag() * ex;

    Complex result (re * cos(im), re * sin(im));
    return result;
}

inline Complex complexDec(Complex z)
{
    Complex result (z.real() - 1.0, z.imag());
    return result;
}

inline Complex complexInc(Complex z)
{
    Complex result (z.real() + 1.0, z.imag());
    return result;
}

inline Complex complexNeg(Complex z)
{
    Complex result (z.real() * -1.0, z.imag() * -1.0);
    return result;
}

inline Complex complexAdd(Complex z1, Complex z2)
{
    Complex result(z1.real() + z2.real(), z1.imag() + z2.imag());
    return result;
}

inline Complex complexDiv(Complex z1, Complex z2)
{
    // divides by zz
    // except if zz is 0
    double r2 = z1.imag() * z2.imag() + z1.real() * z2.real();
    double i2 = z1.imag() * z2.real() - z1.real() * z2.imag();
    double M2 = complexMagInv(z2);

    Complex result(r2 * M2, i2 * M2);
    return result;
}

inline Complex complexAcosH(Complex z)
{
    Complex D(z.real(), z.imag());

    D = complexSqr(D);
    D = complexDec(D);
    D = complexPow(D, 0.5);

    D = complexAdd(z, D);

    return complexLog(D);
}

inline Complex complexAcosecH(Complex z)
{
    z = complexRecip(z);

    Complex result;

    result = c8_acosh(z);

    return result;
}

inline Complex complexAtanH(Complex z)
{
    Complex D(z.real(), z.imag());
    D = complexDec(D);
    D = complexNeg(D);
    D = complexInc(D);
    D = complexDiv(z, D);
    D = complexLog(D);
    D = complexScale(D, 0.5);

    return D;
}

inline Complex complexAcotH(Complex z)
{
    Complex D(z.real(), z.imag());
    D = complexRecip(D);
    D = c8_atanh(D);

    return D;
}

inline Complex complexAsinH(Complex z)
{
    Complex D(z.real(), z.imag());
    D = c8_asinh(D);

    return D;
}