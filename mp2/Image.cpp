#include <cmath>
#include <cstdlib>
#include "Image.h"
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;
using namespace std;

Image::Image():PNG(){
}

Image::Image(unsigned int width, unsigned int height):PNG(width, height){

}


Image::Image(Image const & other):PNG(other){

}




void 	Image::lighten(){
  lighten(0.1);
}

void 	Image::lighten(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel *pixel = this->getPixel(x, y);

      // judge if original luminance is greater than 1 - amount, if so, set luminance to 1
      if(pixel->l > 1.0 - amount){
        pixel->l = 1.0;
      }
      else{
        pixel->l += amount;
      }

    }
  }

}

void 	Image::darken(){
  darken(0.1);
}

void 	Image::darken(double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel *pixel = this->getPixel(x, y);

      // judge if original luminance is smaller than the amount, if so, set luminance to 0
      if(pixel->l < amount){
        pixel->l = 0.0;
      }
      else{
        pixel->l -= amount;
      }

    }
  }
}

void 	Image::saturate(){
  saturate(0.1);
}

void 	Image::saturate (double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel *pixel = this->getPixel(x, y);

      // judge if original saturation is greater than 1 - amount, if so, set luminance to 1
      if(pixel->s > 1.0 - amount){
        pixel->s = 1.0;
      }
      else{
        pixel->s += amount;
      }

    }
  }
}

void 	Image::desaturate (){
  desaturate(0.1);
}

void 	Image::desaturate (double amount){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel *pixel = this->getPixel(x, y);

      // judge if original saturation is smaller than the amount, if so, set luminance to 0
      if(pixel->s < amount){
        pixel->s = 0.0;
      }
      else{
        pixel->s -= amount;
      }

    }
  }
}

void 	Image::grayscale (){
  desaturate(1.0);
}

void 	Image::rotateColor (double degrees){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel *pixel = this->getPixel(x, y);

      // rotate color clockwise
      if(pixel->h + degrees >  360.0){
        pixel->h = pixel->h + degrees -360.0;
      }
      else if(pixel->h + degrees <  0.0){
        pixel->h = pixel->h + degrees + 360.0;
      }
      else{
        pixel->h += degrees;
      }

    }
  }
}

void 	Image::illinify (){
  for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      HSLAPixel *pixel = this->getPixel(x, y);

      //calculate the difference from pixel's hue to orange and blue
      int hue = pixel->h;
      int distanceToOrange = std::min(std::abs(hue-11), std::abs(360 - hue + 11));
      int distanceToBlue = std::min(std::abs(hue-216), std::abs(hue + 144));

      if(distanceToOrange >= distanceToBlue){
        //if the hue value is closer to blue
        pixel->h = 216;
      }
      else{
        pixel->h = 11;
      }
    }
  }
}

void 	Image::scale(double factor){
  // check for errors
  if(factor <= 0.0){
    return;
  }

  int original_h = this->height();
  int original_w = this->width();

  // calculate the height and width of result iamge, create the image
  int result_h = (int)original_h * factor;
  int result_w = (int)original_w * factor;
  Image *result = new Image(result_w, result_h);

  unsigned pixel_x;
  unsigned pixel_y;

  //loop through the result iamge to resample
  for (unsigned x = 0; x < result->width(); x++) {
    for (unsigned y = 0; y < result->height(); y++) {
      pixel_x = (int)floor(x / factor);
      pixel_y = (int)floor(y / factor);
      HSLAPixel *pixel_res = result->getPixel(x, y);
      HSLAPixel *pixel_ori = this->getPixel(pixel_x, pixel_y);
      *pixel_res = *pixel_ori;
    }
  }

  *this = *result;
  delete result;

}

void 	Image::scale(unsigned w, unsigned h){
  // check for errors
  if(w <= 0 || h <= 0){
    return;
  }

  //edit: fit imaage within the size(w * h)

  double factor_w = (double)w / this->width();
  double factor_h = (double)h / this->height();

  if(factor_w >= factor_h){
    scale(factor_h);
  }

  else{
    scale(factor_w);
  }
}
