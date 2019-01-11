#pragma once

#include <stdlib.h>
#include <malloc.h>
#include <cmath>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <float.h>

#ifndef TRUE
	#define TRUE (1)
	#define FALSE (0)
#endif

#define _USE_MATH_DEFINES
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

#define EPSILON 0.0000000001

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define RANGE(a, b, c) (MAX(a, MIN(b, c)))

#define PLUGIN_ARCH_X86 0x00000020
#define PLUGIN_ARCH_X64 0x00000040

// this is here to more easily prefix variable names for i.e. jwildfire paste compatibility
#ifndef APO_VARIABLE_PREFIX
#define APO_VARIABLE_PREFIX
#endif

#ifdef X64
	#define CPU_BITS PLUGIN_ARCH_X64
#else
	#define CPU_BITS PLUGIN_ARCH_X86
#endif

enum VarType
{
    REAL,
    REAL_CYCLIC,
    REAL_NONZERO,
    INTEGER, // All real variable types must be before INTEGER.
    INTEGER_NONZERO
};

typedef struct
{
    const char* name;
    const VarType type;
    int offset;
    double min;
    double max;
    double def;
} VariableInfo;

extern VariableInfo VarInfo[];
double dummyFTz, dummyFPz, dummyColor;

typedef struct
{
	double vvar;
	double* pFTx;
    double* pFTy;
    double* pFTz;
	double* pFPx;
    double* pFPy;
    double* pFPz;
    double* pColor;
    double a, b, c, d, e, f;
	Variables var;
} Variation;

#define APO_EXPORT __declspec (dllexport)

#ifdef LIFETIME_EVENTS
	int    PluginVarInitialize(Variation* vp);
	int    PluginVarTerminate(Variation* vp);
#endif

APO_EXPORT int			PluginVarPrepare(Variation* vp);
APO_EXPORT int			PluginVarCalc(Variation* vp);
APO_EXPORT int			PluginVarResetVariable(void* VariationPtr, const char* name);
APO_EXPORT int			PluginVarGetNrVariables(void);
APO_EXPORT const char*	PluginVarGetName(void);
APO_EXPORT int			PluginVarGetArchitecture(void);

#ifdef X64
    #define OFFSET(name) ((long long) &(((Variables*) 0)->name))
    #define INT_LVALUE(varptr, info)    ( *((int*)    (((long long) &((varptr)->var)) + (info).offset)))
    #define DOUBLE_LVALUE(varptr, info) ( *((double*) (((long long) &((varptr)->var)) + (info).offset)))
#else
    #define OFFSET(name) ((int) &(((Variables*) 0)->name))
    #define INT_LVALUE(varptr, info)    ( *((int*)    (((int) &((varptr)->var)) + (info).offset)))
    #define DOUBLE_LVALUE(varptr, info) ( *((double*) (((int) &((varptr)->var)) + (info).offset)))	
#endif

#define VALUE(varptr, info) ( (info).type >= INTEGER ? INT_LVALUE(varptr, info) : DOUBLE_LVALUE(varptr, info) )

#define APO_PLUGIN(x) const char* PluginVarGetName(void) { return (x); }
#define APO_NUM_VARIABLES(x) int PluginVarGetNrVariables(void) { return (x); }

/*
NOTE:  This macro was causing issues with Visual Studio, since when it's used with no arguments, there's a zero-length array being initialized (other compilers are okay with this).
I went down an awful, awful rabbit hole of macro-based solutions, but in the end just padded the data with an extra first struct, and updated functions:

PluginVarGetVariableNameAt
- now accesses index+1

PluginVarResetVariable
PluginVarGetVariable
PluginVarSetVariable
- shifts loop to i = 1, i < NumVars + 1

This is sort of a gross solution, but it hides the complication from the plugin author, and allows more sources to be used verbatim
Tested in Chaotica and Apophysis 7X

Worst case, if a plugin host directly accesses VarInfo, you just get an "UNUSED" variable showing up
(I think...)

*/

#define APO_VARIABLES(...) VariableInfo VarInfo[] = { {"_UNUSED_", REAL, 0, 0, 0, 0 },  __VA_ARGS__ }; APO_NUM_VARIABLES((sizeof(VarInfo) / sizeof(VariableInfo) - 1))

#define VAR_DEF(nm, min, max, def, type) { APO_VARIABLE_PREFIX#nm, type, OFFSET(nm), min, max, def }
#define VAR_REAL(nm, def) VAR_DEF(nm, -DBL_MAX, DBL_MAX, def, REAL)
#define VAR_INTEGER(nm, def) VAR_DEF(nm, INT_MIN, INT_MAX, def, INTEGER)
#define VAR_REAL_RANGE(nm, min, max, def)  VAR_DEF(nm, min, max, def, REAL)
#define VAR_INTEGER_RANGE(nm, min, max, def)  VAR_DEF(nm, min, max, def, INTEGER)
#define VAR_INTEGER_NONZERO(nm, def)  VAR_DEF(nm, INT_MIN, INT_MAX, def, INTEGER_NONZERO)
#define VAR_REAL_CYCLE(nm, min, max, def)  VAR_DEF(nm, min, max, def, REAL_CYCLIC)
#define VAR_REAL_NONZERO(nm, def)  VAR_DEF(nm, -DBL_MAX, DBL_MAX, def, REAL_NONZERO)

#define FTx (*(vp->pFTx))
#define FTy (*(vp->pFTy))
#define FTz (*(vp->pFTz))
#define FPx (*(vp->pFPx))
#define FPy (*(vp->pFPy))
#define FPz (*(vp->pFPz))
#define VAR(name) (vp->var.name)
#define VVAR (vp->vvar)

#define TC  (*(vp->pColor))
#define TM(name) (vp->name)

APO_EXPORT void* PluginVarCreate(void)
{
	Variation* vp = (Variation*) calloc(1, sizeof(Variation));
	int numVars = PluginVarGetNrVariables();

    for (int i = 0 ; i < numVars; i++)
    {
        PluginVarResetVariable(vp, VarInfo[i].name);
    }

	#ifdef LIFETIME_EVENTS
		PluginVarInitialize(vp);
	#endif

	return vp;
}
APO_EXPORT int PluginVarDestroy(void** vpp)
{
	int result = FALSE;

	#ifdef LIFETIME_EVENTS
		if (vpp) 
		{
			result = PluginVarTerminate((Variation*)(*vpp));
		}
	#endif

    if (vpp && *vpp)
    {
        free(*vpp);
        *vpp = NULL;
        return result;
    }

    return FALSE;
}

APO_EXPORT int PluginVarGetArchitecture(void)
{
	#ifdef X64
		return PLUGIN_ARCH_X64;
	#else
		return PLUGIN_ARCH_X86;
	#endif
}

APO_EXPORT int PluginVarInit(void* varptr, void* pFPx, void* pFPy, void* pFTx, void* pFTy, double vvar)
{
    Variation* vp = (Variation*) varptr;

    if (vp == NULL)
        return FALSE;
    vp->pFPx = (double*) pFPx;
    vp->pFPy = (double*) pFPy;
    vp->pFTx = (double*) pFTx;
    vp->pFTy = (double*) pFTy;
    vp->pFTz = &dummyFTz;
    vp->pFPz = &dummyFPz;
    vp->pColor = &dummyColor;

    dummyFTz = 0;
    dummyFPz = 0;
    dummyColor = 0;

    vp->a = vp->d = 1;
    vp->b = vp->c = vp->e = vp->f = 0;

    vp->vvar = vvar;

    return TRUE;
}
APO_EXPORT int PluginVarInit3D(void* varptr, void* pFPx, void* pFPy, void* pFPz, void* pFTx, void* pFTy, void* pFTz, double vvar) 
{
	int result = PluginVarInit(varptr, pFPx, pFPy, pFTx, pFTy, vvar);

	Variation* vp = (Variation*) varptr;
	vp->pFTz = (double*) pFTz;
	vp->pFPz = (double*) pFPz;

	return result;
}
APO_EXPORT int PluginVarInitDC(void* varptr, void* pFPx, void* pFPy, void* pFPz, void* pFTx, void* pFTy, void* pFTz, void* pColor, double vvar, double a, double b, double c, double d, double e, double f)
{
	int result = PluginVarInit3D(varptr, pFPx, pFPy, pFPz, pFTx, pFTy, pFTz, vvar);

	Variation* vp = (Variation*) varptr;
	vp->pColor = (double*) pColor;
    vp->a = a; vp->b = b; vp->c = c;
    vp->d = d; vp->e = e; vp->f = f;

	return result;
}

APO_EXPORT const char* PluginVarGetVariableNameAt(int index)
{
	int numVars = PluginVarGetNrVariables();

    if (index >= 0 && index < numVars)
        return VarInfo[index+1].name;

    return "";
}
APO_EXPORT int PluginVarResetVariable(void* VariationPtr, const char* name)
{
    Variation* var;
	int numVars = PluginVarGetNrVariables();

    if ((var = (Variation*) VariationPtr) == 0)
        return FALSE;

    for (int i = 1 ; i < numVars + 1; i++)
    {
        if (strcmp(VarInfo[i].name, name) == 0)
        {
            switch (VarInfo[i].type)
            {
            case REAL :
            case REAL_CYCLIC :
                DOUBLE_LVALUE(var, VarInfo[i]) = VarInfo[i].def;
                break;
            case INTEGER :
            case INTEGER_NONZERO :
                INT_LVALUE(var, VarInfo[i]) = (int)(VarInfo[i].def);
                break;
            }

            return TRUE;
        }
    }

    return FALSE;
}
APO_EXPORT int PluginVarGetVariable(void* VariationPtr, const char* name, double* value)
{
    Variation* var;
	int numVars = PluginVarGetNrVariables();

    if ((var = (Variation*) VariationPtr) == 0)
        return FALSE;

    for (int i = 1 ; i < numVars + 1; i++)
    {
        if (strcmp(VarInfo[i].name, name) == 0)
        {
            *value = (double) VALUE(var, VarInfo[i]);
            return TRUE;
        }
    }

    return FALSE;
}
APO_EXPORT int PluginVarSetVariable(void* VariationPtr, const char* name, double* value)
{
    Variation* var;
	int numVars = PluginVarGetNrVariables();

    if ((var = (Variation*) VariationPtr) == 0)
        return FALSE;

    for (int i = 1 ; i < numVars + 1; i++)
    {
        if (strcmp(VarInfo[i].name, name) == 0)
        {
            int v = 0;

            switch (VarInfo[i].type)
            {
            case REAL :
                DOUBLE_LVALUE(var, VarInfo[i]) = RANGE(VarInfo[i].min, *value, VarInfo[i].max);
                break;
            case REAL_CYCLIC :
                if (*value > VarInfo[i].max)
                    DOUBLE_LVALUE(var, VarInfo[i]) = VarInfo[i].min + fmod(*value - VarInfo[i].min, VarInfo[i].max - VarInfo[i].min);
                else if (*value < VarInfo[i].min)
                    DOUBLE_LVALUE(var, VarInfo[i]) = VarInfo[i].max - fmod(VarInfo[i].max - *value, VarInfo[i].max - VarInfo[i].min);
                else
                    DOUBLE_LVALUE(var, VarInfo[i]) = *value;
                break;
            case INTEGER :
                INT_LVALUE(var, VarInfo[i]) = (int) RANGE(VarInfo[i].min, floor(*value + 0.5), VarInfo[i].max);
                break;
            case INTEGER_NONZERO :
                v = (int) RANGE(VarInfo[i].min, floor(*value + 0.5), VarInfo[i].max);
                if (v == 0)
                    v = 1;
                INT_LVALUE(var, VarInfo[i]) = v;
                break;
            }

            return TRUE;
        }
    }

    return FALSE;
}

inline void fsincos(double theta, double* s, double* c)
{
	#if !defined(NO_ASM) && defined(__GNUC__)
	  __asm__ (
		"fsincos\n\t"
		: "=t" (*c), "=u" (*s)
		: "0" (theta)
	  );
	#elif !defined(NO_ASM) && defined(_MSC_VER)
	  __asm {
		fld QWORD PTR theta
		fsincos
		mov ebx,[c]
		fstp QWORD PTR [ebx]
		mov ebx,[s]
		fstp QWORD PTR [ebx]
	  }
	#else
	  *s = sin(theta);
	  *c = cos(theta);
	#endif
}
inline void sinhcosh(double theta, double* sh, double* ch)
{
    double expt = exp(theta);
    double exptinv = 1.0 / expt;
    *sh = (expt - exptinv) * 0.5;
    *ch = (expt + exptinv) * 0.5;
}
inline double random01()
{
    return ((rand() ^ (rand()<<15)) & 0xfffffff) / (double) 0xfffffff;
}
inline double sqr(double x)
{
    return x*x;
}
