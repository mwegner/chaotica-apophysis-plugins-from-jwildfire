#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: affine3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/Affine3DFunc.java

    Automatically converted by @mwegner

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

#include "datahelpers.h"

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
	double _sinX;
	double _cosX;
	double _sinY;
	double _cosY;
	double _sinZ;
	double _cosZ;
	bool _hasShear;

} Variables;

#define APO_VARIABLE_PREFIX "affine3D_"
#include "plugin.h"

APO_PLUGIN("affine3D");
APO_VARIABLES(
	VAR_REAL(translateX, 0),
	VAR_REAL(translateY, 0),
	VAR_REAL(translateZ, 0),
	VAR_REAL(scaleX, 1.0),
	VAR_REAL(scaleY, 1.0),
	VAR_REAL(scaleZ, 1.0),
	VAR_REAL(rotateX, 0),
	VAR_REAL(rotateY, 0),
	VAR_REAL(rotateZ, 0),
	VAR_REAL(shearXY, 0),
	VAR_REAL(shearXZ, 0),
	VAR_REAL(shearYX, 0),
	VAR_REAL(shearYZ, 0),
	VAR_REAL(shearZX, 0),
	VAR_REAL(shearZY, 0),

);


int PluginVarPrepare(Variation* vp)
{
    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    return TRUE;
}





// original java file embedded here:
//
// /*
//   JWildfire - an image and animation processor written in Java 
//   Copyright (C) 1995-2011 Andreas Maschke
// 
//   This is free software; you can redistribute it and/or modify it under the terms of the GNU Lesser 
//   General Public License as published by the Free Software Foundation; either version 2.1 of the 
//   License, or (at your option) any later version.
//  
//   This software is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without 
//   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
//   Lesser General Public License for more details.
// 
//   You should have received a copy of the GNU Lesser General Public License along with this software; 
//   if not, write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
//   02110-1301 USA, or see the FSF site: http://www.fsf.org.
// */
// package org.jwildfire.create.tina.variation;
// 
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// public class Affine3DFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_TRANSLATE_X = "translateX";
//   private static final String PARAM_TRANSLATE_Y = "translateY";
//   private static final String PARAM_TRANSLATE_Z = "translateZ";
//   private static final String PARAM_SCALE_X = "scaleX";
//   private static final String PARAM_SCALE_Y = "scaleY";
//   private static final String PARAM_SCALE_Z = "scaleZ";
//   private static final String PARAM_ROTATE_X = "rotateX";
//   private static final String PARAM_ROTATE_Y = "rotateY";
//   private static final String PARAM_ROTATE_Z = "rotateZ";
//   private static final String PARAM_SHEAR_XY = "shearXY";
//   private static final String PARAM_SHEAR_XZ = "shearXZ";
//   private static final String PARAM_SHEAR_YX = "shearYX";
//   private static final String PARAM_SHEAR_YZ = "shearYZ";
//   private static final String PARAM_SHEAR_ZX = "shearZX";
//   private static final String PARAM_SHEAR_ZY = "shearZY";
// 
// 
//   private static final String[] paramNames = {PARAM_TRANSLATE_X, PARAM_TRANSLATE_Y, PARAM_TRANSLATE_Z, PARAM_SCALE_X,
//           PARAM_SCALE_Y, PARAM_SCALE_Z, PARAM_ROTATE_X, PARAM_ROTATE_Y, PARAM_ROTATE_Z, PARAM_SHEAR_XY, PARAM_SHEAR_XZ,
//           PARAM_SHEAR_YX, PARAM_SHEAR_YZ, PARAM_SHEAR_ZX, PARAM_SHEAR_ZY};
// 
//   private double translateX;
//   private double translateY;
//   private double translateZ;
//   private double scaleX = 1.0;
//   private double scaleY = 1.0;
//   private double scaleZ = 1.0;
//   private double rotateX;
//   private double rotateY;
//   private double rotateZ;
//   private double shearXY;
//   private double shearXZ;
//   private double shearYX;
//   private double shearYZ;
//   private double shearZX;
//   private double shearZY;
// 
//   private double _sinX, _cosX, _sinY, _cosY, _sinZ, _cosZ;
//   private boolean _hasShear;
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // based on "affine3D" of Framelet
//     if (_hasShear) {
//       pVarTP.x += pAmount * (_cosZ * (_cosY * (shearXY * scaleY * pAffineTP.y + shearXZ * scaleZ * pAffineTP.z + scaleX * pAffineTP.x) + _sinY * (_sinX * (shearYX * scaleX * pAffineTP.x + shearYZ * scaleZ * pAffineTP.z + scaleY * pAffineTP.y) + _cosX * (shearZX * scaleX * pAffineTP.x + shearZY * scaleY * pAffineTP.y + scaleZ * pAffineTP.z))) - _sinZ * (_cosX * (shearYX * scaleX * pAffineTP.x + shearYZ * scaleZ * pAffineTP.z + scaleY * pAffineTP.y) - _sinX * (shearZX * scaleX * pAffineTP.x + shearZY * scaleY * pAffineTP.y + scaleZ * pAffineTP.z)) + translateX);
//       pVarTP.y += pAmount * (_sinZ * (_cosY * (shearXY * scaleY * pAffineTP.y + shearXZ * scaleZ * pAffineTP.z + scaleX * pAffineTP.x) + _sinY * (_sinX * (shearYX * scaleX * pAffineTP.x + shearYZ * scaleZ * pAffineTP.z + scaleY * pAffineTP.y) + _cosX * (shearZX * scaleX * pAffineTP.x + shearZY * scaleY * pAffineTP.y + scaleZ * pAffineTP.z))) + _cosZ * (_cosX * (shearYX * scaleX * pAffineTP.x + shearYZ * scaleZ * pAffineTP.z + scaleY * pAffineTP.y) - _sinX * (shearZX * scaleX * pAffineTP.x + shearZY * scaleY * pAffineTP.y + scaleZ * pAffineTP.z)) + translateY);
//       pVarTP.z += pAmount * (-_sinY * (shearXY * scaleY * pAffineTP.y + shearXZ * scaleZ * pAffineTP.z + scaleX * pAffineTP.x) + _cosY * (_sinX * (shearYX * scaleX * pAffineTP.x + shearYZ * scaleZ * pAffineTP.z + scaleY * pAffineTP.y) + _cosX * (shearZX * scaleX * pAffineTP.x + shearZY * scaleY * pAffineTP.y + scaleZ * pAffineTP.z)) + translateZ);
//     } else {
//       pVarTP.x += pAmount * (_cosZ * (_cosY * scaleX * pAffineTP.x + _sinY * (_cosX * scaleZ * pAffineTP.z + _sinX * scaleY * pAffineTP.y)) - _sinZ * (_cosX * scaleY * pAffineTP.y - _sinX * scaleZ * pAffineTP.z) + translateX);
//       pVarTP.y += pAmount * (_sinZ * (_cosY * scaleX * pAffineTP.x + _sinY * (_cosX * scaleZ * pAffineTP.z + _sinX * scaleY * pAffineTP.y)) + _cosZ * (_cosX * scaleY * pAffineTP.y - _sinX * scaleZ * pAffineTP.z) + translateY);
//       pVarTP.z += pAmount * (-_sinY * scaleX * pAffineTP.x + _cosY * (_cosX * scaleZ * pAffineTP.z + _sinX * scaleY * pAffineTP.y) + translateZ);
//     }
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{translateX, translateY, translateZ, scaleX, scaleY, scaleZ, rotateX, rotateY, rotateZ, shearXY,
//             shearXZ, shearYX, shearYZ, shearZX, shearZY};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_TRANSLATE_X.equalsIgnoreCase(pName))
//       translateX = pValue;
//     else if (PARAM_TRANSLATE_Y.equalsIgnoreCase(pName))
//       translateY = pValue;
//     else if (PARAM_TRANSLATE_Z.equalsIgnoreCase(pName))
//       translateZ = pValue;
//     else if (PARAM_SCALE_X.equalsIgnoreCase(pName))
//       scaleX = pValue;
//     else if (PARAM_SCALE_Y.equalsIgnoreCase(pName))
//       scaleY = pValue;
//     else if (PARAM_SCALE_Z.equalsIgnoreCase(pName))
//       scaleZ = pValue;
//     else if (PARAM_ROTATE_X.equalsIgnoreCase(pName))
//       rotateX = pValue;
//     else if (PARAM_ROTATE_Y.equalsIgnoreCase(pName))
//       rotateY = pValue;
//     else if (PARAM_ROTATE_Z.equalsIgnoreCase(pName))
//       rotateZ = pValue;
//     else if (PARAM_SHEAR_XY.equalsIgnoreCase(pName))
//       shearXY = pValue;
//     else if (PARAM_SHEAR_XZ.equalsIgnoreCase(pName))
//       shearXZ = pValue;
//     else if (PARAM_SHEAR_YX.equalsIgnoreCase(pName))
//       shearYX = pValue;
//     else if (PARAM_SHEAR_YZ.equalsIgnoreCase(pName))
//       shearYZ = pValue;
//     else if (PARAM_SHEAR_ZX.equalsIgnoreCase(pName))
//       shearZX = pValue;
//     else if (PARAM_SHEAR_ZY.equalsIgnoreCase(pName))
//       shearZY = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "affine3D";
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     super.init(pContext, pLayer, pXForm, pAmount);
//     double xa = rotateX * M_PI / 180.0;
//     _sinX = sin(xa);
//     _cosX = cos(xa);
//     double ya = rotateY * M_PI / 180.0;
//     _sinY = sin(ya);
//     _cosY = cos(ya);
//     double za = rotateZ * M_PI / 180.0;
//     _sinZ = sin(za);
//     _cosZ = cos(za);
//     _hasShear = fabs(shearXY) > EPSILON || fabs(shearXZ) > EPSILON || fabs(shearYX) > EPSILON ||
//             fabs(shearYZ) > EPSILON || fabs(shearZX) > EPSILON || fabs(shearZY) > EPSILON;
//   }
// }
// 
