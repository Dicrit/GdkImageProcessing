#include "Application.h"
#include <gtkmm.h>
#include "MainWindow.h"

namespace gip
{
    int Application::run(int argc, char **argv)
    {
        auto app = Gtk::Application::create("org.gtkmm.examples.base");
        return app->make_window_and_run<MyWindow>(argc, argv);
    }

} // namespace gip