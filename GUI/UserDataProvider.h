#pragma once
#include <gtkmm.h>
#include <memory>

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

    private:
        Gtk::Window *window_;
    };
} // namespace gip
