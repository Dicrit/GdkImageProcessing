#include "ImageAdapter.h"
#include <gdkmm/pixbufloader.h>
#include "ImageBuffer.h"
#include "Watermark.h"

namespace gip
{
    ImageAdapter::~ImageAdapter() {}

    void ImageAdapter::load_image(const std::string path)
    {
        image_ = loader_.load_image(path);
    }

    bool ImageAdapter::loaded() const
    {
        return image_.get();
    }

    gip::IImage *ImageAdapter::image()
    {
        return image_.get();
    }

    void ImageAdapter::save_image(const std::string path)
    {
        loader_.store_image(image_.get(), path);
    }

    void ImageAdapter::apply_watermark(const std::string watermark_path)
    {
        gip::Watermark watermark(watermark_path);
        watermark.apply_to_image(*image_);
    }

    Glib::RefPtr<Gdk::Pixbuf> ImageAdapter::get_pixbuf()
    {
        ImageBuffer buffer(*image_);
        auto loader = Gdk::PixbufLoader::create();
        loader->write(static_cast<const unsigned char *>(buffer.data()), buffer.size());
        loader->close();
        return loader->get_pixbuf();
    }
} // namespace gip
