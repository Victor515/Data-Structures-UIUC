#include "StickerSheet.h"
#include "Image.h"

int main() {

  Image base;
  Image sticker1;
  Image sticker2;
  Image sticker3;

  base.readFromFile("base.png");
  sticker1.readFromFile("sticker1.png");
  sticker2.readFromFile("sticker2.png");
  sticker3.readFromFile("sticker3.png");

  StickerSheet* sheet = new StickerSheet(base, 5);
  sheet->addSticker(sticker1, 775, 300);
  sheet->addSticker(sticker2, 760, 600);
  sheet->addSticker(sticker3, 736, 1200);

  Image output = sheet->render();
  output.writeToFile("myImage.png");
  delete sheet;
  return 0;
}
