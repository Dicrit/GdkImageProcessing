#pragma once
#include <memory>
#include <gtkmm/builder.h>
#include <gtkmm/image.h>
#include "UserDataProvider.h"
#include "IImageContainer.h"

namespace gip
{

    class MainWindowController
    {
    public:
        MainWindowController(Gtk::Builder* builder, std::unique_ptr<IImageContainer> image, UserDataProvider* user_data_provider);
        ~MainWindowController();
    private:
        void on_open_image_clicked();
        void on_save_image_clicked();
        void on_rotate_button_clicked();
        void on_resize_button_clicked();
        void on_watermark_button_clicked();

        void update_image();

        std::unique_ptr<IImageContainer> image_;
        Gtk::Image *image_preview_;
        UserDataProvider* user_data_provider_;
    };
} // namespace gip
