/*
    Apophysis Plugin: glsl_

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/GLSLFunc.java

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
	int _resolutionX = 1000000;
	int _resolutionY = resolutionX;
	int _gradient;

    int ___warning;
} Variables;

#define APO_VARIABLE_PREFIX "glsl__"
#include "plugin.h"

APO_PLUGIN("glsl_");
APO_VARIABLES(

    { "WARNING_this_plugin_does_nothing", INTEGER, OFFSET(___warning), 0, 1, 0 },
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
// package org.jwildfire.create.tina.variation;
// 
// 
// import js.glsl.vec2;
// import js.glsl.vec3;
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// 
// 
// public class GLSLFunc extends VariationFunc {
// 
//   /*
//    * Variation : glslFunc Base class for GLSL variations
//    *
//    * Autor: Jesus Sosa
//    * Date: October 31, 2018
//    * Reference
//    */
// 
//   private static final String PARAM_RESOLUTIONX = "Density Pixels";
// 
//   private static final String PARAM_GRADIENT = "Gradient";
// 
//   private static final long serialVersionUID = 1L;
// 
//   private static final String[] paramNames = {PARAM_RESOLUTIONX, PARAM_GRADIENT};
// 
// 
//   int resolutionX = 1000000;
//   int resolutionY = resolutionX;
//   int gradient = 0;
// 
//   @Override
//   public void initOnce(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     super.initOnce(pContext, pLayer, pXForm, pAmount);
// 
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
// 
//   }
// 
//   public vec3 getRGBColor(int i, int j) {
//     double xt = (double) i + 0.5;
//     double yt = (double) j + 0.5;
// 
//     vec2 uv = new vec2(0.0, 0.0);
//     uv.x = xt / resolutionX;
//     uv.y = yt / resolutionY;
// 
//     return new vec3(uv, 0.0);
//   }
// 
//   public int[] dbl2int(vec3 theColor) {
//     int[] color = new int[3];
// 
//     color[0] = Math.max(0, Math.min(255, (int) Math.floor(theColor.x * 256.0D)));
//     color[1] = Math.max(0, Math.min(255, (int) Math.floor(theColor.y * 256.0D)));
//     color[2] = Math.max(0, Math.min(255, (int) Math.floor(theColor.z * 256.0D)));
//     return color;
//   }
//  	
//  
//  	
// /* 	public int[] dbl2int(vec3 theColor)
//   	{
//   		int[] color=new int[3];
// 
//   		int col = (int)(256D * theColor.x);
//   		if(col > 255)
//   			col = 255;
//   		color[0] = col;
//   		col = (int)(256D * theColor.y);
//   		if(col > 255)
//   			col = 255;
//   		color[1] = col;
//   		col = (int)(256D * theColor.z);
//   		if(col > 255)
//   			col = 255;
//   		color[2] = col;
//   		return color;
//   	}*/
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// 
//     int i = (int) (pContext.random() * resolutionX);
//     int j = (int) (pContext.random() * resolutionY);
// 
//     vec3 color = new vec3(0.0);
// 
//     color = getRGBColor(i, j);
// 
//     int[] tcolor = new int[3];
//     tcolor = dbl2int(color);
// 
//     pVarTP.rgbColor = true;
//     ;
//     pVarTP.redColor = tcolor[0];
//     pVarTP.greenColor = tcolor[1];
//     pVarTP.blueColor = tcolor[2];
// 
//     pVarTP.x += pAmount * ((double) (i) / resolutionX - 0.5);
//     pVarTP.y += pAmount * ((double) (j) / resolutionY - 0.5);
// 
//   }
// 
//   public String getName() {
//     return "glsl_";
//   }
// 
//   public String[] getParameterNames() {
//     return paramNames;
//   }
// 
// 
//   public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
//     return new Object[]{resolutionX, gradient};
//   }
// 
//   public void setParameter(String pName, double pValue) {
//     if (pName.equalsIgnoreCase(PARAM_RESOLUTIONX)) {
//       resolutionX = (int) Tools.limitValue(pValue, 100, 10000000);
//     } else if (pName.equalsIgnoreCase(PARAM_GRADIENT)) {
//       gradient = (int) Tools.limitValue(pValue, 0, 1);
//     } else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public boolean dynamicParameterExpansion() {
//     return true;
//   }
// 
//   @Override
//   public boolean dynamicParameterExpansion(String pName) {
//     // preset_id doesn't really expand parameters, but it changes them; this will make them refresh
//     return true;
//   }
// 
// }
// 
// 
// 
// 
