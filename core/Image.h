#pragma once
#include "IImage.h"
#include <memory>

namespace gip
{
    class Image : public IImage
    {
    public:
        explicit Image(std::unique_ptr<Magick::Image> image);
        void rotate(double degree) override;
        void resize(size_t width, size_t height) override;
        size_t width() const override;
        size_t heigth() const override;
        Magick::Image* get_low_level_interface() override;
        ~Image();
    private:
        std::unique_ptr<Magick::Image> image_;
    };
} // namespace gip
