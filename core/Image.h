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

    class Image : public IImage
    {
    public:
        explicit Image(const std::string &path);
        void store_to_file(const std::string& path);
        void rotate(double degree);
        void resize(size_t width, size_t height);
        size_t width() const;
        size_t heigth() const;
        Magick::Image* get_low_level_interface() const;
        ~Image();
    private:
        std::unique_ptr<Magick::Image> image_;
    };
} // namespace gip
