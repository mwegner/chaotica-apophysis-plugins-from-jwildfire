/*
    Apophysis Plugin: affine3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Affine3DFunc.java

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

typedef struct
{
    double translateX;
    double translateY;
    double translateZ;

    double scaleX;
    double scaleY;
    double scaleZ;

    double rotateX;
    double rotateY;
    double rotateZ;
    
    double shearXY;
    double shearXZ;
    double shearYX;
    double shearYZ;
    double shearZX;
    double shearZY;
    
	// not exposed
	double _sinX, _cosX, _sinY, _cosY, _sinZ, _cosZ;
    bool _hasShear;

} Variables;

#define APO_VARIABLE_PREFIX "affine3D_"
#include "plugin.h"

APO_PLUGIN("affine3D");
APO_VARIABLES(
	VAR_REAL(translateX, 0.0),
    VAR_REAL(translateY, 0.0),
    VAR_REAL(translateZ, 0.0),
    VAR_REAL(scaleX, 1.0),
    VAR_REAL(scaleY, 1.0),
    VAR_REAL(scaleZ, 1.0),
    VAR_REAL(rotateX, 0.0),
    VAR_REAL(rotateY, 0.0), 
    VAR_REAL(rotateZ, 0.0),
    VAR_REAL(shearXY, 0.0),
    VAR_REAL(shearZY, 0.0),
    VAR_REAL(shearYX, 0.0),
    VAR_REAL(shearYZ, 0.0),
    VAR_REAL(shearZX, 0.0),
    VAR_REAL(shearZY, 0.0),
);

int PluginVarPrepare(Variation* vp)
{
    double sina, cosa;

	double xa = VAR(rotateX) * M_PI / 180.0;
    fsincos(xa, &sina, &cosa);
    VAR(_sinX) = sina;
    VAR(_cosX) = cosa;

    double ya = VAR(rotateY) * M_PI / 180.0;
    fsincos(ya, &sina, &cosa);
    VAR(_sinY) = sina;
    VAR(_cosY) = cosa;

    double za = VAR(rotateZ) * M_PI / 180.0;
    fsincos(za, &sina, &cosa);
    VAR(_sinZ) = sina;
    VAR(_cosZ) = cosa;

    VAR(_hasShear) = fabs(VAR(shearXY)) > EPSILON || fabs(VAR(shearXZ)) > EPSILON || fabs(VAR(shearYX)) > EPSILON ||
            fabs(VAR(shearYZ)) > EPSILON || fabs(VAR(shearZX)) > EPSILON || fabs(VAR(shearZY)) > EPSILON;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
	// based on "affine3D" of Framelet
    if (VAR(_hasShear)) {
      FPx += VVAR * (VAR(_cosZ) * (VAR(_cosY) * (VAR(shearXY) * VAR(scaleY) * FTy + VAR(shearXZ) * VAR(scaleZ) * FTz + VAR(scaleX) * FTx) + VAR(_sinY) * (VAR(_sinX) * (VAR(shearYX) * VAR(scaleX) * FTx + VAR(shearYZ) * VAR(scaleZ) * FTz + VAR(scaleY) * FTy) + VAR(_cosX) * (VAR(shearZX) * VAR(scaleX) * FTx + VAR(shearZY) * VAR(scaleY) * FTy + VAR(scaleZ) * FTz))) - VAR(_sinZ) * (VAR(_cosX) * (VAR(shearYX) * VAR(scaleX) * FTx + VAR(shearYZ) * VAR(scaleZ) * FTz + VAR(scaleY) * FTy) - VAR(_sinX) * (VAR(shearZX) * VAR(scaleX) * FTx + VAR(shearZY) * VAR(scaleY) * FTy + VAR(scaleZ) * FTz)) + VAR(translateX));
      FPy += VVAR * (VAR(_sinZ) * (VAR(_cosY) * (VAR(shearXY) * VAR(scaleY) * FTy + VAR(shearXZ) * VAR(scaleZ) * FTz + VAR(scaleX) * FTx) + VAR(_sinY) * (VAR(_sinX) * (VAR(shearYX) * VAR(scaleX) * FTx + VAR(shearYZ) * VAR(scaleZ) * FTz + VAR(scaleY) * FTy) + VAR(_cosX) * (VAR(shearZX) * VAR(scaleX) * FTx + VAR(shearZY) * VAR(scaleY) * FTy + VAR(scaleZ) * FTz))) + VAR(_cosZ) * (VAR(_cosX) * (VAR(shearYX) * VAR(scaleX) * FTx + VAR(shearYZ) * VAR(scaleZ) * FTz + VAR(scaleY) * FTy) - VAR(_sinX) * (VAR(shearZX) * VAR(scaleX) * FTx + VAR(shearZY) * VAR(scaleY) * FTy + VAR(scaleZ) * FTz)) + VAR(translateY));
      FPz += VVAR * (-VAR(_sinY) * (VAR(shearXY) * VAR(scaleY) * FTy + VAR(shearXZ) * VAR(scaleZ) * FTz + VAR(scaleX) * FTx) + VAR(_cosY) * (VAR(_sinX) * (VAR(shearYX) * VAR(scaleX) * FTx + VAR(shearYZ) * VAR(scaleZ) * FTz + VAR(scaleY) * FTy) + VAR(_cosX) * (VAR(shearZX) * VAR(scaleX) * FTx + VAR(shearZY) * VAR(scaleY) * FTy + VAR(scaleZ) * FTz)) + VAR(translateZ));
    } else {
      FPx += VVAR * (VAR(_cosZ) * (VAR(_cosY) * VAR(scaleX) * FTx + VAR(_sinY) * (VAR(_cosX) * VAR(scaleZ) * FTz + VAR(_sinX) * VAR(scaleY) * FTy)) - VAR(_sinZ) * (VAR(_cosX) * VAR(scaleY) * FTy - VAR(_sinX) * VAR(scaleZ) * FTz) + VAR(translateX));
      FPy += VVAR * (VAR(_sinZ) * (VAR(_cosY) * VAR(scaleX) * FTx + VAR(_sinY) * (VAR(_cosX) * VAR(scaleZ) * FTz + VAR(_sinX) * VAR(scaleY) * FTy)) + VAR(_cosZ) * (VAR(_cosX) * VAR(scaleY) * FTy - VAR(_sinX) * VAR(scaleZ) * FTz) + VAR(translateY));
      FPz += VVAR * (-VAR(_sinY) * VAR(scaleX) * FTx + VAR(_cosY) * (VAR(_cosX) * VAR(scaleZ) * FTz + VAR(_sinX) * VAR(scaleY) * FTy) + VAR(translateZ));
    }

    return TRUE;
}
