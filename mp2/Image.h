#ifndef IMAGE_H
#define IMAGE_H
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;
using namespace std;

class Image : public PNG{
public:
  Image();
  Image(unsigned int width, unsigned int height);
  Image(Image const & other);
  //~Image();
  //Image const & operator= (Image const & other);
  void 	lighten();
  void 	lighten(double amount);
  void 	darken();
  void 	darken(double amount);
  void 	saturate();
  void 	saturate (double amount);
  void 	desaturate ();
  void 	desaturate (double amount);
  void 	grayscale ();
  void 	rotateColor (double degrees);
  void 	illinify ();
  void 	scale (double factor);
  void 	scale (unsigned w, unsigned h);


};

#endif
