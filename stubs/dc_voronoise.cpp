#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: dc_voronoise

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/DC_VoronoiseFunc.java

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

} Variables;

#define APO_VARIABLE_PREFIX "dc_voronoise_"
#include "plugin.h"

APO_PLUGIN("dc_voronoise");
APO_VARIABLES(


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
// import java.util.Random;
// 
// import org.jwildfire.base.Tools;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// import org.jwildfire.create.tina.palette.RGBColor;
// import org.jwildfire.create.tina.palette.RGBPalette;
// 
// import js.glsl.G;
// import js.glsl.mat3;
// import js.glsl.vec2;
// import js.glsl.vec3;
// 
// 
// 
// public class DC_VoronoiseFunc  extends DC_BaseFunc {
// 
// 	/*
// 	 * Variation : dc_voronise
// 	 * Autor: Jesus Sosa
// 	 * Date: February 12, 2019
// 	 */
// 
// 
// 
// 	private static final long serialVersionUID = 1L;
// 
// 
// 	private static final String PARAM_ZOOM = "zoom";
// 	private static final String PARAM_DELTAX = "pX";
// 	private static final String PARAM_DELTAY = "pY";
// 
// 
// 	double zoom = 8.0;
//     double deltaX=0.5;
// 	double deltaY=0.5;
// 
// 	
// 	private static final String[] additionalParamNames = { PARAM_ZOOM,PARAM_DELTAX,PARAM_DELTAY};
// 	    
// 	  
// 	public vec3 getRGBColor(double xp,double yp)
// 	{
// 
// 		vec2 st=new vec2(xp,yp);
// 		vec3 col=new vec3(0.0);
// 	    st=st.multiply(zoom);
// 	    double n = G.iqnoise(st, deltaX, deltaY);
// 
// 	    col = new vec3(n);
// 		return col;
// 	}
//  	
// 	public String getName() {
// 		return "dc_voronoise";
// 	}
// 
// 	public String[] getParameterNames() {
// 		return joinArrays(additionalParamNames, paramNames);
// 	}
// 
// 
// 	public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
// 		return joinArrays(new Object[] { zoom,deltaX, deltaY},super.getParameterValues());
// 	}
// 	
// 	public void setParameter(String pName, double pValue) {
// 		if (PARAM_ZOOM.equalsIgnoreCase(pName)) 
// 		{	   zoom =  pValue;
// 
// 	    }
// 		else if (pName.equalsIgnoreCase(PARAM_DELTAX)) {
// 			deltaX = Tools.limitValue(pValue, 0.0 , 1.0);
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_DELTAY)) {
// 			deltaY = Tools.limitValue(pValue, 0.0 , 1.0);
// 		}
// 		else
// 			super.setParameter(pName, pValue);
// 	}
// 
// 	@Override
// 	public boolean dynamicParameterExpansion() {
// 		return true;
// 	}
// 
// 	@Override
// 	public boolean dynamicParameterExpansion(String pName) {
// 		// preset_id doesn't really expand parameters, but it changes them; this will make them refresh
// 		return true;
// 	}	
// 	
// }
// 
// 
