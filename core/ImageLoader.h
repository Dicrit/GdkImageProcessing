#include "IImage.h"
#include <memory>

namespace gip
{
    class ImageLoader
    {
    public:
        std::unique_ptr<IImage> load_image(const std::string &path);
        void store_image(IImage *image, const std::string &path);
    };

} // namespace gip
