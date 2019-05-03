#include "cs225/PNG.h"
#include <list>
#include <iostream>

#include "colorPicker/ColorPicker.h"
#include "imageTraversal/ImageTraversal.h"

#include "Point.h"
#include "Animation.h"
#include "FloodFilledImage.h"

using namespace cs225;

/**
 * Constructs a new instance of a FloodFilledImage with a image `png`.
 *
 * @param png The starting image of a FloodFilledImage
 */
FloodFilledImage::FloodFilledImage(const PNG & png) {
  /** @todo [Part 2] */
  start_ = png;

}

/**
 * Adds a flood fill operation to the FloodFillImage.  This function must store the operation,
 * which will be used by `animate`.
 *
 * @param traversal ImageTraversal used for this FloodFill operation.
 * @param colorPicker ColorPicker used for this FloodFill operation.
 */
void FloodFilledImage::addFloodFill(ImageTraversal & traversal, ColorPicker & colorPicker) {
  /** @todo [Part 2] */
  travList_.push_back(&traversal);
  pickerList_.push_back(&colorPicker);
}

/**
 * Creates an Animation of frames from the FloodFill operations added to this object.
 *
 * Each FloodFill operation added by `addFloodFill` is executed based on the order
 * the operation was added.  This is done by:
 * 1. Visiting pixels within the image based on the order provided by the ImageTraversal iterator and
 * 2. Updating each pixel to a new color based on the ColorPicker
 *
 * While applying the FloodFill to the image, an Animation is created by saving the image
 * after every `frameInterval` pixels are filled.  To ensure a smooth Animation, the first
 * frame is always the starting image and the final frame is always the finished image.
 *
 * (For example, if `frameInterval` is `4` the frames are:
 *   - The initial frame
 *   - Then after the 4th pixel has been filled
 *   - Then after the 8th pixel has been filled
 *   - ...
 *   - The final frame, after all pixels have been filed)
 */
Animation FloodFilledImage::animate(unsigned frameInterval) {
  Animation animation;
  /** @todo [Part 2] */
  animation.addFrame(start_); // add the initial frame

  while(!travList_.empty())
  {
    ImageTraversal & trav = *(travList_.front());

    // get the corresponding colorPicker
    ColorPicker & currPicker = *(pickerList_.front());
    unsigned count = 1; // keep track of number of pixels visited

    for(const Point & p : trav){

      *(start_.getPixel(p.x, p.y)) = currPicker.getColor(p.x,p.y);

      if(count % frameInterval == 0){
        // add the image to frame every frameInterval
        animation.addFrame(start_);
      }

      count++;
    }

    // before starting next FloodFill, add the final frame
    animation.addFrame(start_);

    // Pop out the colorPicker and move it to the back(preserve the original pickerList_)
    travList_.pop_front();
    pickerList_.pop_front();
  }

  return animation;
}
