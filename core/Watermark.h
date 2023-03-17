#pragma once
#include "IWatermark.h"
#include <string>
#include <memory>

namespace Magick
{
    class Image;
}

namespace gip
{
    class Image;

    class Watermark : public IWatermark
    {
    public:
        explicit Watermark(const std::string &path);
        ~Watermark();

        void apply_to_image(const gip::Image &image);

    private:
        std::unique_ptr<Magick::Image> watermark_image_;
    };
} // namespace gip
