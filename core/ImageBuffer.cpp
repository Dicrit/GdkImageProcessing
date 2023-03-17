#include "ImageBuffer.h"
#include <Magick++.h>
#include "IImage.h"

namespace gip
{
    ImageBuffer::ImageBuffer(gip::IImage &image)
        : blob_(new Magick::Blob)
    {
        image.get_low_level_interface()->write(blob_.get());
    }

    ImageBuffer::~ImageBuffer(){}

    const void *ImageBuffer::data() const
    {
        return blob_->data();
    }

    size_t ImageBuffer::size() const
    {
        return blob_->length();
    }
} // namespace gip
