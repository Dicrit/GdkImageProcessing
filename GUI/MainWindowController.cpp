#include "MainWindowController.h"
#include "Image.h"

namespace gip
{
    class ImageVisitor : public IImageVisitor
    {
    public:
        virtual void access_buffer(const void *data, const size_t length) override
        {
            auto loader = Gdk::PixbufLoader::create();
            loader->write(static_cast<const unsigned char *>(data), length);
            loader->close();
            buf_ = loader->get_pixbuf();
        }

        Glib::RefPtr<Gdk::Pixbuf> buffer()
        {
            return buf_;
        }

    private:
        Glib::RefPtr<Gdk::Pixbuf> buf_;
    };

    MainWindowController::MainWindowController(Gtk::Builder *builder, UserDataProvider *user_data_provider)
        : user_data_provider_(user_data_provider)
    {
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

        builder->get_widget("ImagePreview", image_preview_);
    }

    MainWindowController::~MainWindowController() {}

    void MainWindowController::on_open_image_clicked()
    {
        Gtk::FileChooserDialog dialog("Please choose a file",
                                      Gtk::FILE_CHOOSER_ACTION_OPEN);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Open", Gtk::RESPONSE_OK);

        int result = dialog.run();
        if (result != Gtk::RESPONSE_OK)
        {
            return;
        }

        std::string filename = dialog.get_filename();
        try
        {
            image_ = std::make_unique<gip::Image>(filename);
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
        if (!image_)
        {
            return;
        }
        Gtk::FileChooserDialog dialog("Please choose a file",
                                      Gtk::FILE_CHOOSER_ACTION_SAVE);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Save", Gtk::RESPONSE_OK);

        int result = dialog.run();
        if (result != Gtk::RESPONSE_OK)
        {
            return;
        }

        std::string filename = dialog.get_filename();
        try
        {
            image_->store_to_file(filename);
        }
        catch (const std::exception &ex)
        {
            // TODO: log erorr
            return;
        }
    }

    void MainWindowController::on_rotate_button_clicked()
    {
        if (!image_)
        {
            return;
        }
        double degrees = 0;
        if (user_data_provider_->request_rotation(&degrees))
        {
            image_->rotate(degrees);
            update_image();
        }
    }

    void MainWindowController::on_resize_button_clicked()
    {
        if (!image_)
        {
            return;
        }
        size_t width = image_->width(), height = image_->heigth();
        if (user_data_provider_->request_resize_dims(&width, &height))
        {
            image_->resize(width, height);
            update_image();
        }
    }

    void MainWindowController::update_image()
    {
        if(!image_)
        {
            image_preview_->clear();
            return;
        }
        ImageVisitor visitor;
        image_->accept(&visitor);
        auto surface = Gdk::Cairo::create_surface_from_pixbuf(visitor.buffer(), 1);
        image_preview_->set(surface);
    }

} // namespace gip
