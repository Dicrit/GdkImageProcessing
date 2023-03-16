#pragma once
#include <gtkmm.h>
#include <memory>
#include "UserDataProvider.h"

namespace gip
{
    class Image;

    class MainWindowController
    {
    public:
        MainWindowController(Gtk::Builder* builder, UserDataProvider* user_data_provider);
        ~MainWindowController();
    private:
        void on_open_image_clicked();
        void on_save_image_clicked();
        void on_rotate_button_clicked();
        void on_resize_button_clicked();

        void update_image();

        std::unique_ptr<gip::Image> image_;
        Gtk::Image *image_preview_;
        UserDataProvider* user_data_provider_;
    };
} // namespace gip
