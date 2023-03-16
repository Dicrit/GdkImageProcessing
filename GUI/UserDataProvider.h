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

        bool request_rotation(double *out_rotation)
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

        bool request_resize_dims(size_t *out_width, size_t *out_height)
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
                auto entry_label= std::make_unique<Gtk::Label>(label);
                entry_box->pack_end(entry);
                entry_box->pack_end(*entry_label);
                dialog_content->pack_end(*entry_box);
                widget_store.push_back(std::move(entry_box));
                widget_store.push_back(std::move(entry_label));
            };
            Gtk::Entry width_entry;
            Gtk::Entry height_entry;
            add_entry(width_entry, "width:");
            add_entry(height_entry, "height:");

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

    private:
        Gtk::Window *window_;
    };
} // namespace gip
