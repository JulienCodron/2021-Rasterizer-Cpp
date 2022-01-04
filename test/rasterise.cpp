#include "../src/scene.h"

int main(int argc, const char * argv[])
{ 
  aline::Scene scene;
  scene.initialise(argc, argv);
  scene.run();

  // return 0 means OK.
  return 0;
}
