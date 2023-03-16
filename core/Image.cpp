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

    void Image::accept(IImageVisitor *visitor)
    {
        Magick::Blob blob;
        image_->write(&blob);
        visitor->access_buffer(blob.data(), blob.length());
    }

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

    void Image::add_watermark(const std::string &path)
    {
        Magick::Image watermark(path);
        // logo.artifact();
        // logo.composite(watermark, GravityType::South, CompositeOperator::DissolveCompositeOp);
        image_->artifact("compose:args", "25%");
        image_->composite(watermark, MagickCore::GravityType::SouthGravity, MagickCore::CompositeOperator::DissolveCompositeOp);
    }

    size_t Image::width() const
    {
        return image_->size().width();
    }
    size_t Image::heigth() const
    {
        return image_->size().height();
    }

} // namespace gip
