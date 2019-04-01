#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: dc_menger

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/DC_MengerFunc.java

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

#define APO_VARIABLE_PREFIX "dc_menger_"
#include "plugin.h"

APO_PLUGIN("dc_menger");
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
// public class DC_MengerFunc  extends DC_BaseFunc {
// 
// 	/*
// 	 * Variation : dc_menger
// 	 * Autor: Jesus Sosa
// 	 * Date: February 12, 2019
// 	 */
// 
// 
// 
// 	private static final long serialVersionUID = 1L;
// 
// 	private static final String PARAM_ZOOM = "zoom";
// 	private static final String PARAM_LEVEL = "Level";
// 
// 
// 	private double zoom = 1.0;
// 	int level=3;
// 
// 	private static final String[] additionalParamNames = { PARAM_ZOOM,PARAM_LEVEL};
// 
// 	    
// 
// 	  public double sdBox(vec2 p, vec2 s) {
// 			p = G.abs(p).minus( s);
// 			return G.length(G.max(p, 0.0)) + G.min(G.max(p.x, p.y), 0.0);
// 		}
// 
// 		public double sdCross(vec2 p) {
// 			p = G.abs(p);
// 			return G.min(p.x, p.y) - 1.0;
// 		}
// 
// 		public double sierpinskiCarpet(vec2 p) {
// 			double d = sdBox(p, new vec2(1.0));
// 			
// 			double s = 1.0;
// 			for (int i = 0; i < level; i++) {
// 				vec2 a = G.mod(p.multiply( s), 2.0).minus( 1.0);
// 				vec2 r = new vec2(1.0).minus( G.abs(a).multiply(3.0));
// 				s *= 3.0;
// 				double c = sdCross(r) / s;
// 				d = G.max(d, c);
// 			}
// 			return d;
// 		}
// 	  
// 	public vec3 getRGBColor(double xp,double yp)
// 	{
// 
// 		vec2 p=new vec2(xp,yp).multiply(zoom);
// 		vec3 col=new vec3(0.0);
// 
//         double d=sierpinskiCarpet(p.multiply(1.3));
// 		col= d > 0.0 ? new vec3(0.0) : new vec3(1.0);
// 		return col;
// 	}
//  	
// 
// 	public String getName() {
// 		return "dc_menger";
// 	}
// 
// 	public String[] getParameterNames() {
// 		return joinArrays(additionalParamNames, paramNames);
// 	}
// 
// 
// 	public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
// 		return joinArrays(new Object[] { zoom,level},super.getParameterValues());
// 	}
// 
// 	
// 	public void setParameter(String pName, double pValue) {
// 		if (PARAM_ZOOM.equalsIgnoreCase(pName)) 
// 		{	   zoom =   pValue;
// 
// 	    }
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
