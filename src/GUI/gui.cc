// --------------------------------------------------------------------------
#include "MainWindow.h"
#include "Configuration.h"
#include <iostream>
// --------------------------------------------------------------------------
using namespace knights;
using namespace std;
// --------------------------------------------------------------------------
int main(int argc, char **argv)
{   
	Gtk::Main Kit(argc, (char**&)argv);

	if (!g_thread_supported())
	{
		g_thread_init(NULL);
	}
	
	try
	{
		string guifile  = "gui.glade";
		string gladedir = "./";
		string svgdir   = "svg/";

		MainWindow* mw = MainWindow::Instance(gladedir, guifile, svgdir);
		Kit.run(*mw->w);
	}
	catch(Glib::Error& ex)
	{
		std::locale ru_locale;
		cerr << "(gui): " << ex.what() << " (locale=" << ru_locale.name() << ")" << endl;
	}
	catch(Exception& ex)
	{
		cerr << "(GUI): " << ex.what() << endl;
	}
	catch(std::exception& ex)
	{
		cerr << "(GUI): " << ex.what() << endl;
	}
	catch(...)
	{
		cerr << "(GUI): catch ..." << endl;
	}

	return 0;
}
