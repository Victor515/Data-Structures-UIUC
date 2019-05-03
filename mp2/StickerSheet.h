#ifndef STICKERSHEET_H
#define STICKERSHEET_H

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"

class StickerSheet{

public:
  StickerSheet (const Image &picture, unsigned max);
  ~StickerSheet ();
  StickerSheet (const StickerSheet &other);
  const StickerSheet & 	operator= (const StickerSheet &other);
  void 	changeMaxStickers (unsigned max);
  int 	addSticker (Image &sticker, unsigned x, unsigned y);
  bool 	translate (unsigned index, unsigned x, unsigned y);
  void 	removeSticker (unsigned index);
  Image * 	getSticker (unsigned index) const;
  Image 	render () const;
  struct Coordinates{
    unsigned x_;
    unsigned y_;
    Coordinates(unsigned x, unsigned y){
      x_ = x;
      y_ = y;
    }
  };

private:
  Image  base_;
  unsigned max_;
  unsigned currIndex; // the next layer to add
                      // stickers(in other words, there are stickers
                      // from 0 to currIndex - 1
  Image** stickers;
  Coordinates** location;




};

#endif
