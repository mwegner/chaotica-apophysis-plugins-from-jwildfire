#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
/*
    Apophysis Plugin: dc_acrilic

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/DC_AcrilicFunc.java

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

#define APO_VARIABLE_PREFIX "dc_acrilic_"
#include "plugin.h"

APO_PLUGIN("dc_acrilic");
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
// import js.glsl.vec2;
// import js.glsl.vec3;
// 
// 
// 
// public class DC_AcrilicFunc  extends DC_BaseFunc {
// 
// 	/*
// 	 * Variation : dc_acrilic
// 	 * Date: February 12, 2019
// 	 * Jesus Sosa
// 	 */
// 
// 
// 
// 	private static final long serialVersionUID = 1L;
// 
// 
// 	private static final String PARAM_SEED = "Seed";
// 	private static final String PARAM_TIME = "time";
// 	private static final String PARAM_ZOOM = "zoom";
// 	private static final String PARAM_STEPS = "Steps";
// 	private static final String PARAM_P1 = "p1";
// 	private static final String PARAM_P2 = "p2";
// 	private static final String PARAM_P3 = "p3";
// 	private static final String PARAM_P4 = "p4";
// 	private static final String PARAM_P5 = "p5";
// 	private static final String PARAM_P6 = "p6";
// 	private static final String PARAM_FR = "Red Fac.";
// 	private static final String PARAM_FG = "Green Fac.";
// 	private static final String PARAM_FB = "Blue Fac.";
// 
// 
// 	private int seed = 10000;
// 	double time=0.0;
// 	double zoom=0.7;
// 	int steps=10;
// 	double p1=12.0; 
// 	double p2=12.0;  
// 	double p3=12.0;
// 	double p4=12.0;
// 	double p5=75;
// 	double p6=75;
//     double FR=1.0,FG=1.0,FB=1.0;
// 
// 	
// 	  
// 	Random randomize=new Random(seed);
// 
// 	
//  	long last_time=System.currentTimeMillis();
//  	long elapsed_time=0;
// 
// 	private static final String[] additionalParamNames = { PARAM_SEED,PARAM_TIME,PARAM_ZOOM,PARAM_STEPS,PARAM_P1,PARAM_P2,PARAM_P3,PARAM_P4,PARAM_P5,PARAM_P6,
// 			PARAM_FR,PARAM_FG,PARAM_FB};
// 
// 
// 	  public double sq(double x) {
// 			return x*x;
// 		}
// 
// 	  
// 	public vec3 getRGBColor(double xp,double yp)
// 	{
// 
// 		vec2 p = new vec2(zoom* xp, zoom*yp);
//         vec3 col=new vec3(0.0);
//         
// 	    for(int j = 0; j < 3; j++){
// 	        for(int i = 1; i < steps; i++){
// 	            p.x += 0.1 / (i + j) * G.sin(i * p1 * p.y + time + G.cos((time / (p2 * i)) * i + j));
// 	            p.y += 0.1 / (i + j) * G.cos(i * p3 * p.x + time + G.sin((time / (p4 * i)) * i + j));
// 	        }
// 	        if(j==0)
// 	        	col.x=G.sin(p5*sq(p.x)) + G.sin(p6*sq(p.y));
// 	        if(j==1)
// 	        	col.y=G.sin(p5*sq(p.x)) + G.sin(p6*sq(p.y));
// 	        if(j==2)
// 	        	col.z = G.sin(p5*sq(p.x)) + G.sin(p6*sq(p.y));
// 	    }
// 	    col=new vec3( G.cos(col.x*FR), G.cos(col.y*FG), G.cos(col.z*FB));
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
// 	   			 uV.x=pContext.random()-0.5;
// 				 uV.y=pContext.random()-0.5;
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
// 	public String getName() {
// 		return "dc_acrilic";
// 	}
// 
// 	@Override
// 	  public String[] getParameterNames() {
// 		    return joinArrays(additionalParamNames, paramNames);
// 		  }
// 	
// 	  @Override 
// 	public Object[] getParameterValues() { //re_min,re_max,im_min,im_max,
// 		return joinArrays(new Object[] { seed, time,zoom,steps,p1,p2,p3,p4,p5,p6,FR,FG,FB},super.getParameterValues());
// 	}
// 
// 	public void setParameter(String pName, double pValue) {
//  if (PARAM_SEED.equalsIgnoreCase(pName)) 
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
// 		else if (pName.equalsIgnoreCase(PARAM_ZOOM)) {
// 			zoom = pValue;
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_STEPS)) {
// 			steps =(int)Tools.limitValue(pValue, 3 , 100);
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_P1)) {
// 			p1 =Tools.limitValue(pValue, 1. , 100.);
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_P2)) {
// 			p2=Tools.limitValue(pValue, 1. , 100.);
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_P3)) {
// 			p3=Tools.limitValue(pValue, 1. , 100.);
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_P4)) {
// 			p4=Tools.limitValue(pValue, 1. , 100.);
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_P5)) {
// 			p5=Tools.limitValue(pValue, 1. , 100.);
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_P6)) {
// 			p6= Tools.limitValue(pValue, 1. , 100.);
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_FR)) {
// 			FR =Tools.limitValue(pValue, 0.0 , 5.0);
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_FG)) {
// 			FG =Tools.limitValue(pValue, 0.0 , 5.0);
// 		}
// 		else if (pName.equalsIgnoreCase(PARAM_FB)) {
// 			FB =Tools.limitValue(pValue, 0.0 , 5.0);
// 		}
// 	    else
// 	        super.setParameter(pName, pValue);
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
