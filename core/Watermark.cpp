#include "Watermark.h"
#include <Magick++.h>
#include "IImage.h"

namespace gip
{
    Watermark::Watermark(const std::string &path)
        : watermark_image_(new Magick::Image(path))
    {}

    Watermark::~Watermark(){}

    void Watermark::apply_to_image(const gip::IImage &image)
    {
        Magick::Image *img = image.get_low_level_interface();
        img->artifact("compose:args", "25%");
        img->composite(*watermark_image_, MagickCore::GravityType::SouthGravity, MagickCore::CompositeOperator::DissolveCompositeOp);
    }

} // namespace gip
