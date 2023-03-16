#pragma once
#include <gtkmm.h>
#include <memory>
#include <string>

namespace gip
{
    class UserDataProvider
    {
    public:
        explicit UserDataProvider(Gtk::Window *window)
            : window_(window)
        {
        }

        bool request_rotation(double *out_rotation);
        bool request_resize_dims(size_t *out_width, size_t *out_height);
        bool request_input_image_path(std::string* out_path);
        bool request_output_image_path(std::string* out_path);

    private:
        Gtk::Window *window_;
    };
} // namespace gip
