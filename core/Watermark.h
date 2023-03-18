#pragma once
#include <string>
#include <memory>

namespace Magick
{
    class Image;
}

namespace gip
{
    class IImage;

    class Watermark
    {
    public:
        explicit Watermark(const std::string &path);
        ~Watermark();

        void apply_to_image(gip::IImage &image);

    private:
        std::unique_ptr<Magick::Image> watermark_image_;
    };
} // namespace gip
