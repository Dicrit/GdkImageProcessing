#pragma once
#include <glibmm/refptr.h>
#include <gdkmm/pixbuf.h>
#include "IImageContainer.h"
#include "ImageLoader.h"

namespace gip
{
    class Image;
    class ImageAdapter : public IImageContainer
    {
    public:
        virtual ~ImageAdapter();
        virtual void load_image(const std::string path);
        virtual bool loaded() const;
        virtual gip::IImage *image();
        virtual void save_image(const std::string path);
        virtual void apply_watermark(const std::string watermark_path);
        virtual Glib::RefPtr<Gdk::Pixbuf> get_pixbuf();

    private:
        gip::ImageLoader loader_;
        std::unique_ptr<gip::IImage> image_;
    };
} // namespace gip
