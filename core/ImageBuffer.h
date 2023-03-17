#pragma once
#include <memory>

namespace Magick
{
    class Blob;
}

namespace gip
{
    class IImage;
    class ImageBuffer
    {
    public:
        explicit ImageBuffer(gip::IImage &image);
        ~ImageBuffer();
        const void* data() const;
        size_t size() const;

    private:
    std::unique_ptr<Magick::Blob> blob_;
    };
} // namespace gip
