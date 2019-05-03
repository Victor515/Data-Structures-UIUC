
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.

  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */
  PNG p004;       p004.readFromFile("./004.png");
  PNG p005;  p005.readFromFile("./005.png");
  PNG p006; p006.readFromFile("./006.png");


  FloodFilledImage image(p004);
  DFS dfs(p004, Point(0, 0), 10000.0);
  DFS bfs(p004, Point(0, 0), 10000.0);
  MyColorPicker step1(p005);
  MyColorPicker step2(p006);
  HSLAPixel white(0,0,1);
  SolidColorPicker empty(white);

  image.addFloodFill(bfs, empty);
  image.addFloodFill(bfs, step1);
  image.addFloodFill(bfs, empty);
  image.addFloodFill(bfs, step2);
  Animation animation = image.animate(10000);
  std::cout<<"I am here at line 42"<<std::endl;

  PNG lastFrame = animation.getFrame(animation.frameCount() - 1 );
  std::cout<<"I am here at line 45"<<std::endl;
  lastFrame.writeToFile("myFloodFill.png");
  std::cout<<"I am here at line 47"<<std::endl;
  animation.write("charmander_evolution.gif");
  std::cout<<"I am here at line 49"<<std::endl;
  return 0;
}
