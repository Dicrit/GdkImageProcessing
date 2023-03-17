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

    Image::~Image() {}

    void Image::store_to_file(const std::string &path)
    {
        image_->write(path);
    }

    void Image::rotate(double degree)
    {
        image_->rotate(degree);
    }

    void Image::resize(size_t width, size_t height)
    {
        image_->resize(Magick::Geometry(width, height));
    }

    size_t Image::width() const
    {
        return image_->size().width();
    }
    size_t Image::heigth() const
    {
        return image_->size().height();
    }

    Magick::Image* Image::get_low_level_interface() const
    {
        return image_.get();
    }

} // namespace gip
