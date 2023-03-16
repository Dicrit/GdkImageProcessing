#pragma once
#include "IImage.h"
#include <string>
#include <memory>

namespace Magick
{
    class Image;
}

namespace gip
{
    void initialize_image_library(const char *path);

    struct IImageVisitor
    {
        virtual ~IImageVisitor(){};
        virtual void access_buffer(const void *data_, const size_t length) = 0;
    };

    class Image : public IImage
    {
    public:
        explicit Image(const std::string &path);
        void accept(IImageVisitor *visitor);
        void store_to_file(const std::string& path);
        void rotate(double degree);
        void resize(size_t width, size_t height);
        void add_watermark(const std::string& path);
        size_t width() const;
        size_t heigth() const;
        ~Image();

    private:
        std::unique_ptr<Magick::Image> image_;
    };
} // namespace gip
