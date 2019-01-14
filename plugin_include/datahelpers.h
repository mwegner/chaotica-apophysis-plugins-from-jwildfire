// separated from apoplugin.h so it can be included first
// just a couple of math constants and a wrapper for better randomization

#include "sfmt.cpp"

typedef struct
{
    double x;
    double y;
    double z;
} Point;

#define POINT(x,y,z) { (x), (y), (z) }
#define POINT_ADD(a, b) { (a).x + (b).x, (a).y + (b).y, (a).z + (b).z }
#define POINT_SQTR(a) (sqrt((a).x * (a).x + (a).y * (a).y) + SMALL_EPSILON)

#define EPS			1.0e-20
#define M_PI		3.14159265358979323846
#define M_2PI       6.283185307179586476925286766559
#define M_3PI_4     2.3561944901923449288469825374596
#define M_SQRT3     1.7320508075688772935274463415059
#define M_SQRT3_2   0.86602540378443864676372317075249
#define M_SQRT5     2.2360679774997896964091736687313
#define M_PHI       1.61803398874989484820458683436563
#define M_1_2PI     0.15915494309189533576888376337251

#define M_E        2.71828182845904523536
#define M_LOG2E    1.44269504088896340736
#define M_LOG10E   0.434294481903251827651
#define M_LN2      0.693147180559945309417
#define M_LN10     2.30258509299404568402
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616
#define M_1_PI     0.318309886183790671538
#define M_2_PI     0.636619772367581343076
#define M_2_SQRTPI 1.12837916709551257390
#define M_SQRT2    1.41421356237309504880
#define M_SQRT1_2  0.707106781186547524401

#define GOODRAND_0X(x) VAR(goodRandom).IRandom(0, x)
#define GOODRAND_01() VAR(goodRandom).Random()
#define GOODRAND_SEED(x) vp->var.goodRandom.RandomInit(x)
#define GOODRAND_INT() vp->var.goodRandom.IRandom(0, 4294967296)
#define GOODRAND_PREPARE() VAR(goodRandom) = CRandomSFMT(rand(), true)
#define GOODRAND_STRUCT CRandomSFMT goodRandom
#define GOODRAND_PI() GOODRAND_01() * M_PI_2