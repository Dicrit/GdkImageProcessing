#include "Image.h"
#include <Magick++.h>

namespace gip
{
    Image::Image(std::unique_ptr<Magick::Image> image)
        : image_(std::move(image))
    {
    }

    Image::~Image() {}

    void Image::rotate(double degree)
    {
        image_->rotate(degree);
    }

    void Image::resize(size_t width, size_t height)
    {
        Magick::Geometry geometry(width, height);
        geometry.aspect(true);
        image_->resize(geometry);
    }

    size_t Image::width() const
    {
        return image_->size().width();
    }
    size_t Image::heigth() const
    {
        return image_->size().height();
    }

    Magick::Image *Image::get_low_level_interface() const
    {
        return image_.get();
    }

} // namespace gip
