#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: dc_turbulence

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/DC_TurbulenceFunc.java

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
	double _c = 1.0;
	double _inten = .05;

} Variables;

#define APO_VARIABLE_PREFIX "dc_turbulence_"
#include "plugin.h"

APO_PLUGIN("dc_turbulence");
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
// public class DC_TurbulenceFunc  extends DC_BaseFunc {
// 
// 	/*
// 	 * Variation : dc_turbulence
// 	 * Autor: Jesus Sosa
// 	 * Date: October 31, 2018
// 	 * Reference 
// 	 */
// 
// 
// 
// 	private static final long serialVersionUID = 1L;
// 
// 	private static final String PARAM_SEED = "seed";
// 	private static final String PARAM_TIME = "time";
// 	private static final String PARAM_ZOOM = "zoom";
// 	private static final String PARAM_LEVEL = "Level";
// 
// 
// 	private int seed = 10000;
//     double time=0.0;
//     double zoom=8.0;
// 	int level=3;
// 
// 	int gradient=0;
// 
// 	Random randomize=new Random(seed);
// 	
//  	long last_time=System.currentTimeMillis();
//  	long elapsed_time=0;
// 	
// 	
// 	private static final String[] additionalParamNames = { PARAM_SEED,PARAM_TIME,PARAM_ZOOM,PARAM_LEVEL};
// 
// 	   
// 	  
// 	public vec3 getRGBColor(double xp,double yp)
// 	{
// 
// 	//	vec2 p=new vec2(8.0*xp-20.0,8.0*yp-20.0);
// 		vec2 p=new vec2(xp,yp).multiply(zoom).minus(20.0);
// 		vec3 col=new vec3(0.0);
// 
// 
// 		vec2 ik = p;
// 		double c = 1.0;
// 		double inten = .05;
// 
// 		for (int n = 0; n < level; n++) 
// 		{
// 			double t = time * (1.0 - (3.0 / (double)(n+1)));
// 			ik = p.plus(new  vec2(G.cos(t - ik.x) + G.sin(t + ik.y), G.sin(t - ik.y) + G.cos(t + ik.x)));
// 			c += 1.0/G.length(new vec2(p.x / (G.sin(ik.x+t)/inten),p.y / (G.cos(ik.y+t)/inten)));
// 		}
// 		c /= (double)level;
// 		c = 1.5-G.sqrt(c);
// 		return new vec3(c*c*c*c);
// 	}
// 
// 
// 	public String getName() {
// 		return "dc_turbulence";
// 	}
// 
// 	public String[] getParameterNames() {
// 		return joinArrays(additionalParamNames, paramNames);
// 	}
// 
// 
// 	public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
// 		return joinArrays(new Object[] { seed,time,zoom,level},super.getParameterValues());
// 	}
// 
// 
// 	
// 	public void setParameter(String pName, double pValue) {
// 		if (PARAM_SEED.equalsIgnoreCase(pName)) 
// 		{	   seed =  (int) pValue;
// 	       randomize=new Random(seed);
// 	          long current_time = System.currentTimeMillis();
// 	          elapsed_time += (current_time - last_time);
// 	          last_time = current_time;
// 	          time = (double) (elapsed_time / 1000.0);
// 	    }
// 		else if (pName.equalsIgnoreCase(PARAM_TIME)) {
// 			time = Tools.limitValue(pValue, 1.0 , 1000.0);
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_ZOOM)) {
// 			zoom = pValue;
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_LEVEL)) {
// 			level = (int)Tools.limitValue(pValue, 1 , 5);
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
