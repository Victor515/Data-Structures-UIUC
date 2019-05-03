#include <string>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;
using namespace std;

void rotate(std::string inputFile, std::string outputFile){
  PNG* original = new PNG();

  //reads the image from inputFile
  original->readFromFile(inputFile);
  unsigned width = original->width();
  unsigned height = original->height();

  PNG* output = new PNG(width, height);

  for (unsigned x = 0; x < width; x++) {
    for (unsigned y = 0; y < height; y++) {

      HSLAPixel *pixel_ori = (*original).getPixel(x, y); //fetch the fixel at (x,y) on the original
      HSLAPixel *pixel_out = (*output).getPixel(width - 1- x, height - 1 - y);

      *pixel_out = *pixel_ori; // move the pixel at (x, y) on the original to (width - 1 - x, height - 1 - y) on the output
    }
  }

  output->writeToFile(outputFile);




  delete original;
  delete output;
}
