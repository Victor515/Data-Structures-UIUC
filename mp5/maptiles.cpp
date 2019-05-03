/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage> const& theTiles)
{
    /**
     * @todo Implement this function!
     */
    // check for errors
    if(theTiles.empty() || theSource.getRows() == 0 || theSource.getColumns() == 0){
      return NULL;
    }

    // create the result mosaiccanvas
    MosaicCanvas * result = new MosaicCanvas(theSource.getRows(), theSource.getColumns());

    // build a map from average color to original tileimage
    // also build a k-d tree from theTiles
    map<Point<3>, TileImage> colorToTile;
    vector<Point<3>> colorPoints;
    for(auto it = theTiles.begin(); it != theTiles.end(); it++){
      // map building
      colorToTile.insert(pair<Point<3>, TileImage>(PixelToPoint(it->getAverageColor()), *it ));

      // build the vector for k-d tree
      HSLAPixel avgColor = it->getAverageColor();
      colorPoints.push_back(PixelToPoint(avgColor));
      //colorPoints.back().print();
    }

    // finally build a k-d tree
    KDTree<3> tree(colorPoints);

    for(int r = 0; r < theSource.getRows(); r++){
      for(int c = 0; c < theSource.getColumns(); c++){
        // convert average HSLAPixel color to a point color
        Point<3> region_color = PixelToPoint( theSource.getRegionColor(r, c) );

        // find its nearest neighbor in k-d tree
        Point<3> nearest = tree.findNearestNeighbor(region_color);

        // find the best match tileimage
        TileImage match = colorToTile[nearest];
        result->setTile(r, c, match);

      }
    }

    return result;


}

Point<3> PixelToPoint(HSLAPixel pixel){
  Point<3> temp((double)pixel.h / 360, (double)pixel.s, (double)pixel.l);
  //temp.print();
  return temp;
}

HSLAPixel PointToPixel(Point<3> point){
  //point.print();
  HSLAPixel temp((double)point[0] * 360, (double)point[1], (double)point[2]);
  return temp;
}
