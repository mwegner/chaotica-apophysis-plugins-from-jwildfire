#define PLUGIN_WARNING "_WARNING_empty_shim_for_jw_workflow"
/*
    Apophysis Plugin: dc_grid3D

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/DC_Grid3DFunc.java

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

#define APO_VARIABLE_PREFIX "dc_grid3D_"
#include "plugin.h"

APO_PLUGIN("dc_grid3D");
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
// import js.glsl.mat2;
// import js.glsl.mat3;
// import js.glsl.vec2;
// import js.glsl.vec3;
// import js.glsl.vec4;
// 
// 
// 
// public class DC_Grid3DFunc  extends DC_BaseFunc {
// 
// 	/*
// 	 * Variation : dc_grid3D
// 	 * Date: February 13, 2019
// 	 * Author:Jesus Sosa
// 	 */
// 
// 
// 
// 	private static final long serialVersionUID = 1L;
// 
// 
// 	private static final String PARAM_ZOOM = "zoom";
// 	private static final String PARAM_SEED = "Seed";
// 	private static final String PARAM_TIME = "time";
// 
// 
// 
// 
// 	double zoom=1.;
// 	private int seed = 10000;
// 	double time=200.;
// 
// 
// 	Random randomize=new Random(seed);
// 	
//  	long last_time=System.currentTimeMillis();
//  	long elapsed_time=0;
// 	
// 
// 
// 
// 	private static final String[] additionalParamNames = { PARAM_ZOOM,PARAM_SEED,PARAM_TIME};
// 
// 
// 
// 
// 		public vec3 field(vec3 p) {
// 			p = p.multiply(0.1);
// 			double f = .1;
// 			for (int i = 0; i < 3; i++) 
// 			{
// 				p = new vec3(p.y,p.z,p.x); //*mat3(.8,.6,0,-.6,.8,0,0,0,1);
// //				p += vec3(.123,.456,.789)*float(i);
// 				p = G.abs(G.fract(p).minus(0.5));
// 				p = p.multiply(2.0);
// 				f *= 2.0;
// 			}
// 			p = p.multiply(p);
// 			return G.sqrt(p.add(new vec3(p.y,p.z,p.x))).division(f).minus(.05);
// 		}
// 		
// 	public vec3 getRGBColor(double xp,double yp)
// 	{
// 
// 		
// 		// a raymarching experiment by kabuto
// 		//fork by tigrou ind (2013.01.22)
// 		// slow mod by kapsy1312.tumblr.com
// 
// 
// 	        int MAXITER = 30;
// 
// 	        vec2 p=new vec2(xp,yp).multiply(zoom);
// 			vec3 dir = G.normalize(new vec3(p.x,p.y,1.));
// 			double a = time * 0.021;
// 			vec3 pos =new vec3(0.0,time*0.1,0.0);
// 			
// 			dir = dir.times(new mat3(1,0,0,0,G.cos(a),-G.sin(a),0,G.sin(a),G.cos(a)));
// 			dir = dir.times(new mat3(G.cos(a),0,-G.sin(a),0,1,0,G.sin(a),0,G.cos(a)));
// 			vec3 color = new vec3(0);
// 			
// 			for (int i = 0; i < MAXITER; i++) {
// 				vec3 f2 = field(pos);
// 				double f = G.min(G.min(f2.x,f2.y),f2.z);
// 				
// 				pos = pos.add(dir.multiply(f));
// 				vec3 t0=new vec3( ((double) MAXITER-i)).division(f2.add(0.1));
// 				color = color.add(t0);
// 			}
// 			vec3 color3=new vec3(1.0).minus(new vec3(1.0).division((new vec3(1.0).add(color.multiply(.09/(double)(MAXITER*MAXITER))))));
// 
// 			// color3 = color3.multiply(color3);
// 			return new vec3( color3.r+color3.g+color3.b);
// 		}
// 
// 	public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) 
// 	{
// 
//         vec3 color=new vec3(0.0); 
// 		 vec2 uV=new vec2(0.),p=new vec2(0.);
// 	       int[] tcolor=new int[3];  
// 
// 
// 		 
// 	     if(colorOnly==1)
// 		 {
// 			 uV.x=pAffineTP.x;
// 			 uV.y=pAffineTP.y;
// 		 }
// 		 else
// 		 {
// 	   			 uV.x=2.0*pContext.random()-1.0;
// 				 uV.y=2.0*pContext.random()-1.0;
// 		}
//         
//         color=getRGBColor(uV.x,uV.y);
//         tcolor=dbl2int(color);
//         
//         //z by color (normalized)
//         double z=greyscale(tcolor[0],tcolor[1],tcolor[2]);
//         
//         if(gradient==0)
//         {
//   	  	
//     	  pVarTP.rgbColor  =true;;
//     	  pVarTP.redColor  =tcolor[0];
//     	  pVarTP.greenColor=tcolor[1];
//     	  pVarTP.blueColor =tcolor[2];
//     		
//         }
//         else if(gradient==1)
//         {
// 
//             	Layer layer=pXForm.getOwner();
//             	RGBPalette palette=layer.getPalette();      	  
//           	    RGBColor col=findKey(palette,tcolor[0],tcolor[1],tcolor[2]);
//           	    
//           	  pVarTP.rgbColor  =true;;
//           	  pVarTP.redColor  =col.getRed();
//           	  pVarTP.greenColor=col.getGreen();
//           	  pVarTP.blueColor =col.getBlue();
// 
//         }
//         else 
//         {
//         	pVarTP.color=z;
//         }
// 
//         pVarTP.x+= pAmount*(uV.x);
//         pVarTP.y+= pAmount*(uV.y);
//         
//         
// 	    double dz = z * scale_z + offset_z;
// 	    if (reset_z == 1) {
// 	      pVarTP.z = dz;
// 	    }
// 	    else {
// 	      pVarTP.z += dz;
// 	    }
// 	}
// 	
// 
// 	public String getName() {
// 		return "dc_grid3D";
// 	}
// 
// 	public String[] getParameterNames() {
// 		return joinArrays(additionalParamNames, paramNames);
// 	}
// 
// 
// 	public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
// 		return joinArrays(new Object[] { zoom,seed, time},super.getParameterValues());
// 	}
// 
// 	public void setParameter(String pName, double pValue) {
// 		if (pName.equalsIgnoreCase(PARAM_ZOOM)) {
// 			zoom = Tools.limitValue(pValue, 0.01 , 1000.0);
// 		}
// 		else if (PARAM_SEED.equalsIgnoreCase(pName)) 
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
