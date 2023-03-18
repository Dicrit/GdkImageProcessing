#pragma once
#include <string>

namespace Magick
{
    class Image;
}

namespace gip
{
    class IImage
    {
    public:
        virtual ~IImage() {}
        virtual void rotate(double degree) = 0;
        virtual void resize(size_t width, size_t height) = 0;
        virtual size_t width() const = 0;
        virtual size_t heigth() const = 0;
        virtual Magick::Image* get_low_level_interface() = 0;
    };
} // namespace gip
