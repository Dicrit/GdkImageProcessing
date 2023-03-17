#include "IImage.h"
#include <memory>

namespace gip
{
void initialize_image_library(const char *path);

    class ImageLoader
    {
    public:
        std::unique_ptr<IImage> load_image(const std::string &path);
        void store_image(const IImage *image, const std::string &path);
    };

} // namespace gip
