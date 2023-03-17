#include "Application.h"
#include "ImageLoader.h"

int main(int argc, char *argv[])
{
  gip::initialize_image_library(argv[0]);
  gip::Application app;
  app.run(argc, argv);
}
