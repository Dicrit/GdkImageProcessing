#include "Application.h"
#include "CoreLibrary.h"

int main(int argc, char *argv[])
{
  //Is needed on some OS's
  gip::initialize_image_library(argv[0]);

  gip::Application app;
  app.run(argc, argv);
}
