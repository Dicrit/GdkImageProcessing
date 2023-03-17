#include "UserDataProvider.h"
#include <gtkmm/messagedialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/window.h>
#include <gtkmm/filechooserdialog.h>

namespace gip
{
    bool UserDataProvider::request_rotation(double *out_rotation)
    {
        Gtk::MessageDialog dialog(*window_, "Enter rotation",
                                  false /* use_markup */, Gtk::MESSAGE_QUESTION,
                                  Gtk::BUTTONS_OK_CANCEL);
        Gtk::Entry entry;

        Gtk::Box *dialog_content = dialog.get_content_area();
        dialog_content->pack_end(entry);

        dialog.show_all();
        int response = dialog.run();
        if (response != Gtk::RESPONSE_OK)
        {
            return false;
        }
        double res = 0.0;
        try
        {
            res = std::stod(entry.get_text());
        }
        catch (const std::exception &ex)
        {
            // TODO: log
            return false;
        }
        *out_rotation = res;
        return true;
    }

    bool UserDataProvider::request_resize_dims(size_t *out_width, size_t *out_height)
    {
        Gtk::MessageDialog dialog(*window_, "Enter resize dimensions",
                                  false /* use_markup */, Gtk::MESSAGE_QUESTION,
                                  Gtk::BUTTONS_OK_CANCEL);

        Gtk::Box *dialog_content = dialog.get_content_area();
        std::vector<std::unique_ptr<Gtk::Widget>> widget_store;
        widget_store.reserve(4);
        auto add_entry = [dialog_content, &widget_store](Gtk::Entry &entry, const char *label)
        {
            auto entry_box = std::make_unique<Gtk::Box>(Gtk::ORIENTATION_HORIZONTAL);
            auto entry_label = std::make_unique<Gtk::Label>(label);
            entry_box->pack_end(entry);
            entry_box->pack_end(*entry_label);
            dialog_content->pack_end(*entry_box);
            widget_store.push_back(std::move(entry_box));
            widget_store.push_back(std::move(entry_label));
        };
        Gtk::Entry height_entry;
        Gtk::Entry width_entry;
        height_entry.set_text(std::to_string(*out_height));
        width_entry.set_text(std::to_string(*out_width));
        add_entry(height_entry, "height:");
        add_entry(width_entry, "width:");

        dialog.show_all();
        int response = dialog.run();
        if (response != Gtk::RESPONSE_OK)
        {
            return false;
        }

        size_t w = 0, h = 0;
        try
        {
            w = std::stoul(width_entry.get_text());
            h = std::stoul(height_entry.get_text());
        }
        catch (const std::exception &ex)
        {
            // TODO: log
            return false;
        }
        *out_width = w;
        *out_height = h;
        return true;
    }

    bool UserDataProvider::request_input_image_path(std::string *out_path)
    {
        Gtk::FileChooserDialog dialog("Please choose a file",
                                      Gtk::FILE_CHOOSER_ACTION_OPEN);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Open", Gtk::RESPONSE_OK);

        int result = dialog.run();
        if (result != Gtk::RESPONSE_OK)
        {
            return false;
        }

        *out_path = dialog.get_filename();
        return true;
    }

    bool UserDataProvider::request_output_image_path(std::string *out_path)
    {
        Gtk::FileChooserDialog dialog("Please choose a file",
                                      Gtk::FILE_CHOOSER_ACTION_SAVE);
        dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
        dialog.add_button("_Save", Gtk::RESPONSE_OK);

        int result = dialog.run();
        if (result != Gtk::RESPONSE_OK)
        {
            return false;
        }

        *out_path = dialog.get_filename();
        return true;
    }

} // namespace gip
