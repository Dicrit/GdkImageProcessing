#pragma once
#include "IImage.h"
#include <gdkmm/pixbuf.h>
#include <string>

namespace gip
{
    class IImageAdapter
    {
    public:
        virtual ~IImageAdapter() {}
        virtual void load_image(const std::string path) = 0;
        virtual bool loaded() const = 0;
        virtual gip::IImage *image() = 0;
        virtual void save_image(const std::string path) = 0;
        virtual void apply_watermark(const std::string watermark_path) = 0;
        virtual Glib::RefPtr<Gdk::Pixbuf> get_pixbuf() = 0;
    };
} // namespace gip
