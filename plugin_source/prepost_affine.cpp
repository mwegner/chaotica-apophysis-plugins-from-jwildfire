/*
    Apophysis Plugin: prepost_affine

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/PrePostAffineFunc.java

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
	double scale_x;
	double scale_y;
	double scale_z;
	double yaw;
	double pitch;
	double roll;
	double move_x;
	double move_y;
	double move_z;
	double _coefxx;
	double _coefxy;
	double _coefxz;
	double _coefyx;
	double _coefyy;
	double _coefyz;
	double _coefzx;
	double _coefzy;
	double _coefzz;
	double _icoefxx;
	double _icoefxy;
	double _icoefxz;
	double _icoefyx;
	double _icoefyy;
	double _icoefyz;
	double _icoefzx;
	double _icoefzy;
	double _icoefzz;

GOODRAND_STRUCT;
} Variables;

#define APO_VARIABLE_PREFIX "prepost_affine_"
#include "plugin.h"

APO_PLUGIN("prepost_affine");
APO_VARIABLES(
	VAR_REAL(scale_x, 1),
	VAR_REAL(scale_y, 1),
	VAR_REAL(scale_z, 1),
	VAR_REAL(yaw, 0),
	VAR_REAL(pitch, 0),
	VAR_REAL(roll, 0),
	VAR_REAL(move_x, 0),
	VAR_REAL(move_y, 0),
	VAR_REAL(move_z, 0),

);


void invtransform (Variation* vp) {

    // pre affine, inverted, pAffineTP -> pAffineTP
    if (VVAR == 0) return;

    double x = FTx - VAR(move_x);
    double y = FTy - VAR(move_y);
    double z = FTz - VAR(move_z);

    FTx = (VAR(_icoefxx) * x + VAR(_icoefxy) * y + VAR(_icoefxz) * z) / (VVAR * VAR(scale_x));
    FTy = (VAR(_icoefyx) * x + VAR(_icoefyy) * y + VAR(_icoefyz) * z) / (VVAR * VAR(scale_y));
    FTz = (VAR(_icoefzx) * x + VAR(_icoefzy) * y + VAR(_icoefzz) * z) / (VVAR * VAR(scale_z));

}


int PluginVarPrepare(Variation* vp)
{
    GOODRAND_PREPARE();
    // pre-calculate coefficients for transform
    double d2r = M_PI / 180;
    double sinyaw = sin(VAR(yaw) * d2r), cosyaw = cos(VAR(yaw) * d2r);
    double sinpitch = sin(VAR(pitch) * d2r), cospitch = cos(VAR(pitch) * d2r);
    double sinroll = sin(VAR(roll) * d2r), cosroll = cos(VAR(roll) * d2r);

    VAR(_coefxx) = cosyaw * cosroll - sinyaw * sinpitch * sinroll;
    VAR(_coefxy) = -sinyaw * cosroll - cosyaw * sinpitch * sinroll;
    VAR(_coefxz) = -cospitch * sinroll;

    VAR(_coefyx) = sinyaw * cospitch;
    VAR(_coefyy) = cosyaw * cospitch;
    VAR(_coefyz) = -sinpitch;

    VAR(_coefzx) = cosyaw * sinroll + sinyaw * sinpitch * cosroll;
    VAR(_coefzy) = cosyaw * sinpitch * cosroll - sinyaw * sinroll;
    VAR(_coefzz) = cospitch * cosroll;

    VAR(_icoefxx) = cosyaw * cosroll - sinyaw * sinpitch * sinroll;
    VAR(_icoefxy) = sinyaw * cospitch;
    VAR(_icoefxz) = cosyaw * sinroll + sinyaw * sinpitch * cosroll;

    VAR(_icoefyx) = -sinyaw * cosroll - cosyaw * sinpitch * sinroll;
    VAR(_icoefyy) = cosyaw * cospitch;
    VAR(_icoefyz) = cosyaw * sinpitch * cosroll - sinyaw * sinroll;

    VAR(_icoefzx) = -cospitch * sinroll;
    VAR(_icoefzy) = -sinpitch;
    VAR(_icoefzz) = cospitch * cosroll;

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    // post affine, pVarTP -> pVarTP
    if (VVAR == 0) return TRUE;

    double x = VVAR * VAR(scale_x) * FPx;
    double y = VVAR * VAR(scale_y) * FPy;
    double z = VVAR * VAR(scale_z) * FPz;

    FPx = VAR(_coefxx) * x + VAR(_coefxy) * y + VAR(_coefxz) * z + VAR(move_x);
    FPy = VAR(_coefyx) * x + VAR(_coefyy) * y + VAR(_coefyz) * z + VAR(move_y);
    FPz = VAR(_coefzx) * x + VAR(_coefzy) * y + VAR(_coefzz) * z + VAR(move_z);



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
// public class PrePostAffineFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_SCALE_X = "scale_x";
//   private static final String PARAM_SCALE_Y = "scale_y";
//   private static final String PARAM_SCALE_Z = "scale_z";
//   private static final String PARAM_YAW = "yaw";
//   private static final String PARAM_PITCH = "pitch";
//   private static final String PARAM_ROLL = "roll";
//   private static final String PARAM_MOVE_X = "move_x";
//   private static final String PARAM_MOVE_Y = "move_y";
//   private static final String PARAM_MOVE_Z = "move_z";
// 
//   private static final String[] paramNames = {PARAM_SCALE_X, PARAM_SCALE_Y, PARAM_SCALE_Z, PARAM_YAW, PARAM_PITCH, PARAM_ROLL, PARAM_MOVE_X, PARAM_MOVE_Y, PARAM_MOVE_Z};
// 
//   private double scale_x = 1;
//   private double scale_y = 1;
//   private double scale_z = 1;
//   private double yaw = 0;
//   private double pitch = 0;
//   private double roll = 0;
//   private double move_x = 0;
//   private double move_y = 0;
//   private double move_z = 0;
// 
//   private double coefxx, coefxy, coefxz, coefyx, coefyy, coefyz, coefzx, coefzy, coefzz;
//   private double icoefxx, icoefxy, icoefxz, icoefyx, icoefyy, icoefyz, icoefzx, icoefzy, icoefzz;
// 
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     // pre-calculate coefficients for transform
//     double d2r = M_PI / 180;
//     double sinyaw = sin(yaw * d2r), cosyaw = cos(yaw * d2r);
//     double sinpitch = sin(pitch * d2r), cospitch = cos(pitch * d2r);
//     double sinroll = sin(roll * d2r), cosroll = cos(roll * d2r);
// 
//     coefxx = cosyaw * cosroll - sinyaw * sinpitch * sinroll;
//     coefxy = -sinyaw * cosroll - cosyaw * sinpitch * sinroll;
//     coefxz = -cospitch * sinroll;
// 
//     coefyx = sinyaw * cospitch;
//     coefyy = cosyaw * cospitch;
//     coefyz = -sinpitch;
// 
//     coefzx = cosyaw * sinroll + sinyaw * sinpitch * cosroll;
//     coefzy = cosyaw * sinpitch * cosroll - sinyaw * sinroll;
//     coefzz = cospitch * cosroll;
// 
//     icoefxx = cosyaw * cosroll - sinyaw * sinpitch * sinroll;
//     icoefxy = sinyaw * cospitch;
//     icoefxz = cosyaw * sinroll + sinyaw * sinpitch * cosroll;
// 
//     icoefyx = -sinyaw * cosroll - cosyaw * sinpitch * sinroll;
//     icoefyy = cosyaw * cospitch;
//     icoefyz = cosyaw * sinpitch * cosroll - sinyaw * sinroll;
// 
//     icoefzx = -cospitch * sinroll;
//     icoefzy = -sinpitch;
//     icoefzz = cospitch * cosroll;
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // post affine, pVarTP -> pVarTP
//     if (pAmount == 0) return;
// 
//     double x = pAmount * scale_x * pVarTP.x;
//     double y = pAmount * scale_y * pVarTP.y;
//     double z = pAmount * scale_z * pVarTP.z;
// 
//     pVarTP.x = coefxx * x + coefxy * y + coefxz * z + move_x;
//     pVarTP.y = coefyx * x + coefyy * y + coefyz * z + move_y;
//     pVarTP.z = coefzx * x + coefzy * y + coefzz * z + move_z;
// 
//   }
// 
//   @Override
//   public void invtransform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
//     // pre affine, inverted, pAffineTP -> pAffineTP
//     if (pAmount == 0) return;
// 
//     double x = pAffineTP.x - move_x;
//     double y = pAffineTP.y - move_y;
//     double z = pAffineTP.z - move_z;
// 
//     pAffineTP.x = (icoefxx * x + icoefxy * y + icoefxz * z) / (pAmount * scale_x);
//     pAffineTP.y = (icoefyx * x + icoefyy * y + icoefyz * z) / (pAmount * scale_y);
//     pAffineTP.z = (icoefzx * x + icoefzy * y + icoefzz * z) / (pAmount * scale_z);
// 
//   }
// 
//   @Override
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
//   @Override
//   public Object[] getParameterValues() {
//     return new Object[]{scale_x, scale_y, scale_z, yaw, pitch, roll, move_x, move_y, move_z};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_SCALE_X.equalsIgnoreCase(pName))
//       scale_x = (pValue == 0) ? EPSILON : pValue;
//     else if (PARAM_SCALE_Y.equalsIgnoreCase(pName))
//       scale_y = (pValue == 0) ? EPSILON : pValue;
//     else if (PARAM_SCALE_Z.equalsIgnoreCase(pName))
//       scale_z = (pValue == 0) ? EPSILON : pValue;
//     else if (PARAM_YAW.equalsIgnoreCase(pName))
//       yaw = pValue;
//     else if (PARAM_PITCH.equalsIgnoreCase(pName))
//       pitch = pValue;
//     else if (PARAM_ROLL.equalsIgnoreCase(pName))
//       roll = pValue;
//     else if (PARAM_MOVE_X.equalsIgnoreCase(pName))
//       move_x = pValue;
//     else if (PARAM_MOVE_Y.equalsIgnoreCase(pName))
//       move_y = pValue;
//     else if (PARAM_MOVE_Z.equalsIgnoreCase(pName))
//       move_z = pValue;
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "prepost_affine";
//   }
// 
//   @Override
//   public int getPriority() {
//     return 2;
//   }
// 
// }
// 
