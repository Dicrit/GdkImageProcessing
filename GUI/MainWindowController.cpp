#include "MainWindowController.h"
#include <gtkmm/button.h>
#include <gdkmm/general.h>


namespace gip
{
    MainWindowController::MainWindowController(
        Gtk::Builder *builder,
        std::unique_ptr<IImageContainer> image,
        UserDataProvider *user_data_provider)
        : image_(std::move(image)), user_data_provider_(user_data_provider)
    {
        builder->get_widget("ImagePreview", image_preview_);

        auto connect_button_signal = [builder, this](const char *button_name, auto fnc)
        {
            Gtk::Button *btn;
            builder->get_widget(button_name, btn);
            if (!btn)
            {
                throw std::runtime_error("BtnLoadImage widget not found");
            }
            btn->signal_clicked().connect(sigc::mem_fun(*this, fnc));
        };
        connect_button_signal("BtnLoadImage", &MainWindowController::on_open_image_clicked);
        connect_button_signal("BtnSaveImage", &MainWindowController::on_save_image_clicked);
        connect_button_signal("BtnRotateImage", &MainWindowController::on_rotate_button_clicked);
        connect_button_signal("BtnResizeImage", &MainWindowController::on_resize_button_clicked);
        connect_button_signal("BtnWatermark", &MainWindowController::on_watermark_button_clicked);
    }

    MainWindowController::~MainWindowController() {}

    void MainWindowController::on_open_image_clicked()
    {
        std::string filepath;
        if (!user_data_provider_->request_input_image_path(&filepath))
        {
            return;
        }
        try
        {
            image_->load_image(filepath);
            update_image();
        }
        catch (const std::exception &ex)
        {
            // TODO: log erorr
            return;
        }
    }

    void MainWindowController::on_save_image_clicked()
    {
        if (!image_->loaded())
        {
            return;
        }
        std::string filename;
        if (!user_data_provider_->request_output_image_path(&filename))
        {
            return;
        }

        try
        {
            image_->save_image(filename);
        }
        catch (const std::exception &ex)
        {
            // TODO: log erorr
            return;
        }
    }

    void MainWindowController::on_rotate_button_clicked()
    {
        if (!image_->loaded())
        {
            return;
        }
        double degrees = 0;
        if (user_data_provider_->request_rotation(&degrees))
        {
            image_->image()->rotate(degrees);
            update_image();
        }
    }

    void MainWindowController::on_resize_button_clicked()
    {
        if (!image_->loaded())
        {
            return;
        }
        size_t width = image_->image()->width(), height = image_->image()->heigth();
        if (user_data_provider_->request_resize_dims(&width, &height))
        {
            image_->image()->resize(width, height);
            update_image();
        }
    }

    void MainWindowController::on_watermark_button_clicked()
    {
        if (!image_->loaded())
        {
            return;
        }
        std::string filename;
        if (!user_data_provider_->request_input_image_path(&filename))
        {
            return;
        }
        try
        {
            image_->apply_watermark(filename);
            update_image();
        }
        catch (const std::exception &ex)
        {
            // TODO: log erorr
            return;
        }
    }

    void MainWindowController::update_image()
    {
        if (!image_->loaded())
        {
            image_preview_->clear();
            return;
        }

        Glib::RefPtr<Gdk::Pixbuf> buf = image_->get_pixbuf();
        auto surface = Gdk::Cairo::create_surface_from_pixbuf(buf, 1);
        image_preview_->set(surface);
    }

} // namespace gip
