#include "CoreLibrary.h"
#include <Magick++.h>

namespace gip
{
    void initialize_image_library(const char *path)
    {
        Magick::InitializeMagick(path);
    }
} // namespace gip
