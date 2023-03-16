#include "Application.h"
#include <gtkmm.h>
#include <memory.h>
#include "MainWindowController.h"
#include "UserDataProvider.h"

namespace gip
{
    int Application::run(int argc, char **argv)
    {
        auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

        std::unique_ptr<Gtk::Window> window_guard;
        Gtk::Window *window = nullptr;

        // Glib::RefPtr<Gtk::Builder> r;
        auto builder = Gtk::Builder::create_from_file("MainWindow.xml");
        builder->get_widget("MainWindow", window);
        if (!window)
        {
            return -1;
        }
        window_guard.reset(window);
        UserDataProvider user_data_provider{window};
        MainWindowController ctrl(builder.get(), &user_data_provider);

        return app->run(*window);
    }

} // namespace gip