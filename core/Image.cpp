#include "Image.h"
#include <Magick++.h>

namespace gip
{
    void initialize_image_library(const char *path)
    {
        Magick::InitializeMagick(path);
    }

    Image::Image(const std::string &path)
    : image_(new Magick::Image(path))
    {
    }

    Image::~Image(){}

    void Image::accept(IImageVisitor *visitor)
    {
        Magick::Blob blob;
        image_->write(&blob);
        visitor->access_buffer(blob.data(), blob.length());
    }

} // namespace gip
