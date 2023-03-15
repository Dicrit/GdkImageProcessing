#include "MainWindowController.h"
#include "Image.h"

namespace gip
{
    MainWindowController::MainWindowController(Gtk::Builder *builder)
    {
        Gtk::Button *btn;
        builder->get_widget("BtnLoadImage", btn);
        if (!btn)
        {
            throw std::runtime_error("BtnLoadImage widget not found");
        }
        // btn.set_margin(10);
        btn->signal_clicked().connect(sigc::mem_fun(*this,
                                                    &MainWindowController::on_open_image_clicked));
    }

    class ImageVisitor : public IImageVisitor
    {
    public:
        virtual void access_buffer(const void *data, const size_t length) override
        {
            auto loader = Gdk::PixbufLoader::create();
            loader->write(static_cast<const unsigned char *>(data), length);
            buf_ = loader->get_pixbuf();
        }

        Gdk::Pixbuf &buffer()
        {
            return *(buf_.get());
        }

    private:
        Glib::RefPtr<Gdk::Pixbuf> buf_;
    };

    void
    MainWindowController::on_open_image_clicked()
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
            gip::Image image(filename);
            //for future. Try to get the buffer and show it on UI.
            ImageVisitor visitor;
            image.accept(&visitor);
        }
        catch (const std::exception &ex)
        {
            return;
        }
    }

} // namespace gip
