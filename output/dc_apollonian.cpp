#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: dc_apollonian

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/DC_ApollonianFunc.java

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

#define APO_VARIABLE_PREFIX "dc_apollonian_"
#include "plugin.h"

APO_PLUGIN("dc_apollonian");
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
// import org.jwildfire.create.tina.base.Flame;
// import org.jwildfire.create.tina.base.Layer;
// import org.jwildfire.create.tina.base.XForm;
// import org.jwildfire.create.tina.base.XYZPoint;
// import org.jwildfire.create.tina.palette.RGBColor;
// import org.jwildfire.create.tina.palette.RGBPalette;
// import org.jwildfire.create.tina.render.FlameRenderer;
// 
// import js.glsl.G;
// import js.glsl.mat3;
// import js.glsl.vec2;
// import js.glsl.vec3;
// 
// 
// 
// public class DC_ApollonianFunc  extends DC_BaseFunc {
// 
// 	/*
// 	 * Variation : dc_apollonian
// 	 * Autor: Jesus Sosa
// 	 * Date: February 12, 2019 
// 	 */
// 
// 
// 
// 	private static final long serialVersionUID = 1L;
// 
// 	private static final String PARAM_SEED = "seed";
// 	private static final String PARAM_TIME = "time";
// 
// 
// 	private int seed = 10000;
// 	double time=0.0;
// 
// 	
// 
// 
// 	Random randomize=new Random(seed);
// 	
//  	long last_time=System.currentTimeMillis();
//  	long elapsed_time=0;
// 	
// 	
// 	private static final String[] additionalParamNames = { PARAM_SEED,PARAM_TIME};
// 
// 	public vec3 getRGBColor(double xp,double yp)
// 	{
// 
// 		vec2 uv=new vec2(xp,yp);
// 		vec3 col=new vec3(0.0);
// 
// 	    double t = 0.05*time;
// 	    
// 	    mat3 m = G.rot(new vec3(t).add( new vec3(1,2,3)));
// 	    double k = 1.2+0.1*G.sin(0.1*time);
// 	    
// 	    double f1=(2.+0.25*G.sin(0.3*time));
//         vec2 v2=new vec2(2.0).multiply(uv);
// 	    vec3 v = m.times(f1).times( new vec3(v2 ,0.0) );
//         vec3 v3=G.sin(G.app(v,k,m));	    
// 	    col =v3.multiply(new vec3(0.6)).add(new vec3(0.5));
// 		
// 		return col;
// 	}
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
// 	public String getName() {
// 		return "dc_apollonian";
// 	}
// 
// 	public String[] getParameterNames() {
// 	    return joinArrays(additionalParamNames, paramNames);
// 	}
// 
// 
// 	public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
// 		return joinArrays(new Object[] { seed,time},super.getParameterValues());
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
// 			time = pValue;
// 		}
// 	    else
// 	        super.setParameter(pName, pValue);
// 
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
