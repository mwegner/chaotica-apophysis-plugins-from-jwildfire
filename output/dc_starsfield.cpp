#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: dc_starsfield

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/DC_StarsFieldFunc.java

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

#define APO_VARIABLE_PREFIX "dc_starsfield_"
#include "plugin.h"

APO_PLUGIN("dc_starsfield");
APO_VARIABLES(


);


double hash11 (Variation* vp, double p) {

		    p = G.fract(p * 35.35);
		    p += G.dot(p, p + 45.85);
		    return G.fract(p * 7858.58);
}

double hash21 (Variation* vp, vec2 p) {

		    p = G.fract(p.multiply( new vec2(451.45, 231.95)));
		    p = p.plus(G.dot(p, p.plus( 78.78)));
		    return G.fract(p.x * p.y);
}

double layer (Variation* vp, vec2 uv) {


		    double c = 0.0;

		    uv = uv.multiply(5.0);

		    vec2 i = G.floor(uv);
		    vec2 f = G.fract(uv).multiply(zdistance).minus( 1.0);

		    vec2 p = hash22(i).multiply(0.3); 
		    double d = G.length(f.minus(p) );
		    c += G.smoothstep(.1 + .8 * hash21(vp, i), .01, d);
		    c *= (1.0 / d) * .2;

		    return c;
}


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
// import js.glsl.mat2;
// 
// import js.glsl.vec2;
// import js.glsl.vec3;
// import js.glsl.vec4;
// 
// 
// 
// public class DC_StarsFieldFunc  extends DC_BaseFunc {
// 
// 	/*
// 	 * Variation : dc_starsfield
// 	 * Date: February 13, 2019
// 	 * Author:Jesus Sosa
// 	 */
// 
// 
// 
// 	private static final long serialVersionUID = 1L;
// 
// 
// 	private static final String PARAM_SEED = "Seed";
// 	private static final String PARAM_TIME = "time";
// 	private static final String PARAM_ZDISTANCE = "Z distance";
// 	private static final String PARAM_GLOW = "Glow";
// 
// 
// 	private int seed = 10000;
// 
// 
// 	double time=0.0;
//     double zdistance=2.0;
//     double glow=2.0;
// 
// 	  
// 		Random randomize=new Random(seed);
// 		
// 	 	long last_time=System.currentTimeMillis();
// 	 	long elapsed_time=0;
// 	
// 
// 
// 
// 	private static final String[] additionalParamNames = { PARAM_SEED,PARAM_TIME,PARAM_ZDISTANCE,PARAM_GLOW};
// 
// 
// 	
// 	  public mat2 rotate(double a) {
// 		    double c = G.cos(a);
// 		    double s = G.sin(a);
// 		    return new mat2(c, s, -s, c);
// 		}
// 
// 
// 		// one dimensional | 1 in 1 out
// 		public double hash11(double p) {
// 		    p = G.fract(p * 35.35);
// 		    p += G.dot(p, p + 45.85);
// 		    return G.fract(p * 7858.58);
// 		}
// 
// 		// two dimensional | 2 in 1 out
// 		public double hash21(vec2 p) {
// 		    p = G.fract(p.multiply( new vec2(451.45, 231.95)));
// 		    p = p.plus(G.dot(p, p.plus( 78.78)));
// 		    return G.fract(p.x * p.y);
// 		}
// 
// 		// two dimensional | 2 in 2 out
// 		public vec2 hash22(vec2 p) 
// 		{
// 			vec3 t1=new vec3(p.x,p.y,p.x);
// 			t1=t1.multiply(new vec3(451.45, 231.95, 7878.5));
// 		    vec3 q = G.fract(t1);
// 		    q = q.add(G.dot(q, q.add( 78.78)));
// 		    return G.fract(new vec2(q.x,q.z).multiply( q.y));
// 		}
// 
// 		public double layer(vec2 uv) {
// 
// 		    double c = 0.;
// 
// 		    uv = uv.multiply(5.);
// 
// 		    vec2 i = G.floor(uv);
// 		    vec2 f = G.fract(uv).multiply(zdistance).minus( 1.);
// 
// 		    vec2 p = hash22(i).multiply(0.3); 
// 		    double d = G.length(f.minus(p) );
// 		    c += G.smoothstep(.1 + .8 * hash21(i), .01, d);
// 		    c *= (1. / d) * .2;
// 
// 		    return c;
// 		}
// 
// 
// 		public vec3 render(vec2 uv) {
// 
// 		    vec3 col = new vec3(0.);
// 		    uv = uv.times(rotate(time ));
// 			uv = uv.plus(new vec2(G.cos(time ), G.sin(time)).multiply(2.0));
// 		    
// 		    for (double i = 0.; i < 1.; i += .1) {
// 
// 		        uv = uv.times(rotate(hash11(i) * 6.28));
// 		        
// 		        double t = G.fract(i - time );
// 		        double s = G.smoothstep(0., 1., t);
// 		        double f = G.smoothstep(0., 1., t);
// 		        f *= G.smoothstep(1., 0., t);
// 		        
// 		        vec2 k = hash22(new vec2(i, i * 5.)).multiply(0.1);
// 		        double l = layer((uv.minus(k)).multiply( s));
// 		        
// 		        col = col.add(G.mix(new vec3(.0, .0, 0), new vec3(1., 1.0, 1.0), l).multiply(f));
// 
// 		    }
// 
// 		    double t1= glow*hash21( uv.plus(time));
// 		    col = col.add( new vec3(t1));
// 		    return col;
// 
// 		}
// 
// 
// 	public vec3 getRGBColor(double xp,double yp)
// 	{
// 
// 		
// 		vec2 uv = new vec2( xp,yp);
// 		vec3 col= render(uv);
// 
// 		return col;
// 	}
//  
// 	
// 
// 	public String getName() {
// 		return "dc_starsfield";
// 	}
// 
// 	public String[] getParameterNames() {
// 		return joinArrays(additionalParamNames, paramNames);
// 	}
// 
// 
// 	public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
// 		return joinArrays(new Object[] { seed, time,zdistance,glow},super.getParameterValues());
// 	}
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
// 			time = pValue;
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_ZDISTANCE)) {
// 			zdistance =Tools.limitValue(pValue, 2.0 , 150.0);
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_GLOW)) {
// 			glow=Tools.limitValue(pValue, 0.0 , 1.0);
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
