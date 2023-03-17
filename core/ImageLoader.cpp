#include "ImageLoader.h"
#include <Magick++.h>
#include "Image.h"

namespace gip
{
    void initialize_image_library(const char *path)
    {
        Magick::InitializeMagick(path);
    }

    std::unique_ptr<IImage> ImageLoader::load_image(const std::string &path)
    {
        return std::make_unique<gip::Image>(std::make_unique<Magick::Image>(path));
    }

    void ImageLoader::store_image(const IImage *image, const std::string &path)
    {
        image->get_low_level_interface()->write(path);
    }
} // namespace gip
