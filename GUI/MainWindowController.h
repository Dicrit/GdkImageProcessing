#pragma once
#include <gtkmm.h>

namespace gip
{
    class MainWindowController
    {
    public:
        explicit MainWindowController(Gtk::Builder* builder);

    private:
        void on_open_image_clicked();
        void on_rotate_button_clicked();
        void on_resize_button_clicked();
    };
} // namespace gip
