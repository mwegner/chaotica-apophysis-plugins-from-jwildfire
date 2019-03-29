#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"
#define PLUGIN_WARNING "NOTE_modded_for_jwildfire_workflow"

// note this isn't fully working, just put in here to save progress
// if anyone sees this, I'm curious if you can spot what's wrong!

/*
    Apophysis Plugin: arctruchet

    Port of: https://github.com/thargor6/JWildfire/blob/master/src/org/jwildfire/create/tina/variation/ArcTruchetFunc.java

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

typedef struct {
    double tilt;
    double thickness;
    double radius;
} Tile;

typedef struct
{
	int seed;
	double thickness;
	int TilesPerRow;
	int TilesPerColumn;
	double _radius = 0.25;
	double _tileSize;
	int _numberTiles;
	int* _tiltArray;

} Variables;

#define LIFETIME_EVENTS
#define APO_VARIABLE_PREFIX "arctruchet_"
#include "plugin.h"

APO_PLUGIN("arctruchet");
APO_VARIABLES(
	VAR_INTEGER(seed, 10000),
	VAR_REAL(thickness, 0.025),
	VAR_INTEGER(TilesPerRow, 10),
	VAR_INTEGER(TilesPerColumn, 10)

);

int    PluginVarTerminate(Variation* vp)
{
    if (VAR(_tiltArray) && *VAR(_tiltArray)) {
        free((void*) VAR(_tiltArray));
        VAR(_tiltArray) = NULL;
    }

    return TRUE;
}

int    PluginVarInitialize(Variation* vp)
{
    return TRUE;
}

void arc(Variation* vp, Tile* tile, Point* p, double thickness, double phi1, double phi2)
{
    double _phi10, _phi20, _gamma, _delta;
    double r, Phi, sinPhi, cosPhi;

    _phi10 = M_PI * phi1 / 180.0;
    _phi20 = M_PI * phi2 / 180.0;
    _delta = _phi20 - _phi10;
    _gamma = tile->thickness * (2.0 * tile->radius + tile->thickness) / (tile->radius + tile->thickness);
    r = tile->radius + tile->thickness - _gamma * GOODRAND_01();
    Phi = _phi10 + _delta * GOODRAND_01();
    sinPhi = sin(Phi);
    cosPhi = cos(Phi);
    double xp, yp;
    xp = r * cosPhi;
    yp = r * sinPhi;
    double ang = tile->tilt * M_PI / 180.0;
    p->x = (float) (xp * cos(ang) + yp * sin(ang));
    p->y = (float) (-xp * sin(ang) + yp * cos(ang));

    double radio = tile->radius;

    if (floor(phi2) == 270)
        radio = -tile->radius;

    p->x = (float) (radio * cos(ang) + radio * sin(ang));
    p->y = (float) (-radio * sin(ang) + radio * cos(ang));
}

int PluginVarPrepare(Variation* vp)
{
    VAR(_radius) = 0.25;
    GOODRAND_SEED(VAR(seed));

    //VAR(_tileSize) = (float) size / VAR(TilesPerRow) ;
    VAR(_tileSize) = 2.0 * VAR(_radius);
    VAR(_numberTiles) = VAR(TilesPerRow) * VAR(TilesPerColumn);

    if (VAR(_tiltArray) && *VAR(_tiltArray)) {
        free((void*) VAR(_tiltArray));
        VAR(_tiltArray) = NULL;
    }

    VAR(_tiltArray) = (int*) malloc(VAR(_numberTiles) * sizeof(int));

    for (int i = 0; i < VAR(TilesPerRow); i++)
      for (int j = 0; j < VAR(TilesPerColumn); j++)
        VAR(_tiltArray)[j * VAR(TilesPerRow) + i] = GOODRAND_0X(4);

    return TRUE;
}

int PluginVarCalc(Variation* vp)
{
    int i = GOODRAND_0X(VAR(TilesPerRow));
    int j = GOODRAND_0X(VAR(TilesPerColumn));
    float x = (float) ((float) i * VAR(_tileSize) + VAR(_tileSize) / 2.0);
    float y = (float) ((float) j * VAR(_tileSize) + VAR(_tileSize) / 2.0);

    Tile tile;
    tile.thickness = VAR(thickness);
    tile.radius = VAR(_radius);

    //tile.rotate(tiltArray[j * VAR(TilesPerRow) + i]);
    tile.tilt = VAR(_tiltArray)[j * VAR(TilesPerRow) + i] * 90.0;

    Point p;

    if(GOODRAND_01() < 0.5)
    {
        arc(vp, &tile, &p, VAR(thickness), 0.0, 90.0);
    }
    else
    {
        arc(vp, &tile, &p, VAR(thickness), 180.0, 270.0);
    }

    FPx += VVAR * (p.x + x - VAR(_tileSize) * VAR(TilesPerRow) / 2.0);
    FPy += VVAR * (p.y + y - VAR(_tileSize) * VAR(TilesPerColumn) / 2.0);
    if (true /* pContext\.isPreserveZCoordinate() */) {
      FPz += VVAR * FTz;
    }


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
// import java.io.Serializable;
// import java.util.Random;
// 
// import static org.jwildfire.base.mathlib.MathLib.*;
// 
// 
// /**
//  * variation "arctruchet"
//  *
//  * @author Jesus Sosa
//  * @date August 30, 2018
//  * <p>
//  * Parameters
//  * <p>
//  * seed:       random control
//  * thickness:  arc thickness from 0.0 to 1.0
//  * TilesPerRow: Number of tiles per row (from 1 to 100)
//  * TilesPerColumn: Number of tiles per column (from 1 to 100)
//  */
// 
// public class ArcTruchetFunc extends VariationFunc {
//   private static final long serialVersionUID = 1L;
// 
//   private static final String PARAM_SEED = "seed";
//   private static final String PARAM_THICKNESS = "thickness";
//   private static final String PARAM_TILESPERROW = "TilesPerRow";
//   private static final String PARAM_TILESPERCOLUMN = "TilesPerColumn";
// 
//   private static final String[] paramNames = {PARAM_SEED, PARAM_THICKNESS, PARAM_TILESPERROW, PARAM_TILESPERCOLUMN};
// 
//   private int seed = 10000;
//   private double thickness = 0.025;
// 
//   private int numberTilesPerRow = 10;
//   private int numberTilesPerColumn = 10;
//   private double radius = 0.25;
// 
//   Random randomize;
// 
//   private double tileSize;
//   private int numberTiles;
//   private int[] tiltArray;
// 
//   private static class Point implements Serializable {
//     private static final long serialVersionUID = 1L;
// 
//     private double x, y;
//   }
// 
// 
//   static public class Tile {
// 
//     double tilt;
//     double thickness;
//     double radius;
// 
//     // Constructor
//     Tile(Random randomize, double thickness, double radius) {
// 
//       this.thickness = thickness;
//       this.radius = radius;
//     }
// 
//     public void rotate(int nveces) {
//       tilt = nveces * 90.0;
//     }
// 
//     void arc(FlameTransformationContext pContext, Point p, double thickness, double phi1, double phi2, double tilt, double radius) {
//       double _phi10, _phi20, _gamma, _delta;
//       double r, Phi, sinPhi, cosPhi;
// 
//       _phi10 = M_PI * phi1 / 180.0;
//       _phi20 = M_PI * phi2 / 180.0;
//       _delta = _phi20 - _phi10;
//       _gamma = thickness * (2.0 * radius + thickness) / (radius + thickness);
//       r = radius + thickness - _gamma * pContext.random();
//       Phi = _phi10 + _delta * pContext.random();
//       sinPhi = sin(Phi);
//       cosPhi = cos(Phi);
//       double xp, yp;
//       xp = r * cosPhi;
//       yp = r * sinPhi;
//       double ang = tilt * Math.PI / 180.0;
//       p.x = (float) (xp * Math.cos(ang) + yp * Math.sin(ang));
//       p.y = (float) (-xp * Math.sin(ang) + yp * Math.cos(ang));
// 
//       double radio = radius;
//       ;
//       if (phi2 == 270)
//         radio = -radius;
// 
//       Point d = new Point();
//       d.x = (float) (radio * Math.cos(ang) + radio * Math.sin(ang));
//       d.y = (float) (-radio * Math.sin(ang) + radio * Math.cos(ang));
// 
//       p.x -= d.x;
//       p.y -= d.y;
//     }
// 
//     public Point display(FlameTransformationContext pContext) {
//       Point toolPoint = new Point();
// 
//       if (Math.random() < 0.5) {
//         arc(pContext, toolPoint, thickness, 0.0, 90.0, tilt, radius);
//       } else {
//         arc(pContext, toolPoint, thickness, 180.0, 270.0, tilt, radius);
// 
//       }
//       return toolPoint;
//     }
//   }
// 
//   @Override
//   public void transform(FlameTransformationContext pContext, XForm pXForm, XYZPoint pAffineTP, XYZPoint pVarTP, double pAmount) {
// 
//     int i = (int) (randomize.nextDouble() * numberTilesPerRow);
//     int j = (int) (randomize.nextDouble() * numberTilesPerColumn);
//     float x = (float) (i * tileSize + tileSize / 2);
//     float y = (float) (j * tileSize + tileSize / 2);
//     Tile tile = new Tile(randomize, thickness, radius);
//     tile.rotate(tiltArray[j * numberTilesPerRow + i]);
// 
//     Point p = tile.display(pContext);
//     pVarTP.x += pAmount * (p.x + x - tileSize * numberTilesPerRow / 2.0);
//     pVarTP.y += pAmount * (p.y + y - tileSize * numberTilesPerColumn / 2.0);
//     if (pContext.isPreserveZCoordinate()) {
//       pVarTP.z += pAmount * pAffineTP.z;
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
//     return new Object[]{seed, thickness, numberTilesPerRow, numberTilesPerColumn};
//   }
// 
//   @Override
//   public void setParameter(String pName, double pValue) {
//     if (PARAM_SEED.equalsIgnoreCase(pName))
//       seed = (int) limitVal(pValue, 0, 100000);
//     else if (PARAM_THICKNESS.equalsIgnoreCase(pName))
//       thickness = limitVal(pValue, 0.0, 1.0);
//     else if (PARAM_TILESPERROW.equalsIgnoreCase(pName))
//       numberTilesPerRow = (int) limitVal(pValue, 1, 100);
//     else if (PARAM_TILESPERCOLUMN.equalsIgnoreCase(pName))
//       numberTilesPerColumn = (int) limitVal(pValue, 1, 100);
//     else
//       throw new IllegalArgumentException(pName);
//   }
// 
//   @Override
//   public String getName() {
//     return "arctruchet";
//   }
// 
//   @Override
//   public void init(FlameTransformationContext pContext, Layer pLayer, XForm pXForm, double pAmount) {
//     randomize = new Random(seed);
//     randomize.nextDouble();
// 
//     //tileSize = (float) size / numberTilesPerRow ;
//     tileSize = 2.0 * radius;
//     numberTiles = numberTilesPerRow * numberTilesPerColumn;
//     tiltArray = new int[numberTiles];
// 
//     for (int i = 0; i < numberTilesPerRow; i++)
//       for (int j = 0; j < numberTilesPerColumn; j++)
//         tiltArray[j * numberTilesPerRow + i] = (int) (randomize.nextDouble() * 4);
//   }
// }
// 
