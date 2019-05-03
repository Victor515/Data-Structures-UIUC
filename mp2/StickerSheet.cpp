#include <cstddef>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
#include "StickerSheet.h"

using namespace std;
using namespace cs225;



StickerSheet::StickerSheet (const Image &picture, unsigned max) :base_(picture){
  max_ = max;
  stickers = new Image *[max_];
  location = new Coordinates *[max_];
  currIndex = 0;

}

StickerSheet::~StickerSheet (){
  //delete images stored in stickers, and then delete stickers itself
  //do the same for location
  for(unsigned i = 0; i < currIndex; i++){
    delete stickers[i];
    delete location[i];
  }

  delete [] stickers;
  delete [] location;

}

StickerSheet::StickerSheet(const StickerSheet &other) :base_(other.base_){

  this->max_ = other.max_;
  this->currIndex = other.currIndex;

  //deepcopy all sticker images and their coordinates from other
  stickers = new Image *[max_];
  location = new Coordinates *[max_];
  for(unsigned i = 0; i < currIndex; i++){
    stickers[i] = new Image(*other.stickers[i]);
    location[i] = new Coordinates(other.location[i]->x_, other.location[i]->y_);
  }



}

const StickerSheet & 	StickerSheet::operator= (const StickerSheet &other){
  // to check we do not assign to ourselves
  if(this == &other){
    return *this;
  }

  else{
    for(unsigned i = 0; i < currIndex; i++){
      delete stickers[i];
      delete location[i];
    }

    delete [] stickers;
    delete [] location;
    // code above could be written into a function

    this->base_ = other.base_;
    this->max_ = other.max_;
    this->currIndex = other.currIndex;

    //deepcopy all sticker images and their coordinates from other
    stickers = new Image *[max_];
    location = new Coordinates *[max_];
    for(unsigned i = 0; i < currIndex; i++){
      stickers[i] = new Image(*other.stickers[i]);
      location[i] = new Coordinates(other.location[i]->x_, other.location[i]->y_);
    }

    return *this;
  }
}

void 	StickerSheet::changeMaxStickers (unsigned max){

  if(currIndex < max){

  // no stikcers will be lost in this case
     Image** newStickers = new Image* [max];
     Coordinates** newLocation = new Coordinates* [max];

     for(unsigned i = 0; i < currIndex; i++){
       newStickers[i] = new Image(*stickers[i]);
       newLocation[i] = new Coordinates(location[i]->x_, location[i]->y_);
     }

     for(unsigned i = 0; i < currIndex; i++){
       delete stickers[i];
       delete location[i];
     }

     delete [] stickers;
     stickers = newStickers;
     delete [] location;
     location = newLocation;
     max_ = max;

  }

  else{
    // the new maximum number of stickers is smaller
    // than the current number number of stickers

    Image** newStickers = new Image* [max];
    Coordinates** newLocation = new Coordinates* [max];

    // the number of picture could be stored is max
    for(unsigned i = 0; i < max; i++){
      newStickers[i] = new Image(*stickers[i]);
      newLocation[i] = new Coordinates(location[i]->x_, location[i]->y_);
    }

    for(unsigned i = 0; i < currIndex; i++){
      delete stickers[i];
      delete location[i];
    }

    delete [] stickers;
    stickers = newStickers;
    delete [] location;
    location = newLocation;
    max_ = max;
    currIndex = max; // currIndex is now equal to max

  }

}

int StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){
  // check out of bound
  if(base_.width() < x + sticker.width() ||
  base_.height() < y + sticker.height()){
    return -1; // do not add sticker out of bound
  }

  // check whether number of images reach max
  if(currIndex + 1 > max_){
    changeMaxStickers(max_ * 2);
  }

  stickers[currIndex] = new Image(sticker);
  location[currIndex] = new Coordinates(x, y);
  currIndex++;

  return (currIndex - 1);
}

bool 	StickerSheet::translate (unsigned index, unsigned x, unsigned y){

  // check whether the layer is valid
  if(index > currIndex - 1){
    return false;
  }

  location[index]->x_ = x;
  location[index]->y_ = y;
  return true;
}

void 	StickerSheet::removeSticker (unsigned index){
  if(index < currIndex){
    delete stickers[index];
    delete location[index];

  for(unsigned i = index; i < currIndex - 1; i++){

    stickers[i] = stickers[i + 1];
    location[i] = location[i + 1];
  }

    currIndex --;
  }

}

Image * 	StickerSheet::getSticker (unsigned index) const{
  if(index < currIndex){
    return stickers[index];
  }

  else{
    return NULL;
  }
}

Image 	StickerSheet::render () const{
  Image sheet = Image(base_);

  // for each level from 0 to currIndex - 1
  for(unsigned i = 0; i < currIndex; i++){
    for(unsigned x = 0; x < stickers[i]->width(); x++){
      for(unsigned y = 0; y < stickers[i]->height(); y++){
        // correspond to location in base image
        unsigned currX = x + location[i]->x_;
        unsigned currY = y + location[i]->y_;

        HSLAPixel * pixel_sticker = stickers[i]->getPixel(x, y);
        HSLAPixel * pixel_sheet = sheet.getPixel(currX, currY);

        if(pixel_sticker->a > 0){
          *pixel_sheet = *pixel_sticker;
        }
      }
    }
  }

  return sheet;
}
