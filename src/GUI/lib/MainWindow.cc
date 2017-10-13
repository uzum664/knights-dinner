#include "MainWindow.h"
#include <libglademm.h>
#include <assert.h>
#include <iostream>
// ------------------------------------------------------------------------------
using namespace std;
using namespace knights;

MainWindow* knights::gwindow = NULL;
// ------------------------------------------------------------------------------
MainWindow::MainWindow (string gladedir, string guifile, string svgdir) :
	progress(0),
	alignment(0.5, 0.5, 0, 0)
{
	splash.modify_bg(Gtk::STATE_NORMAL, Gdk::Color("#000000"));
	alignment.add(bar);
	splash.add(alignment);
	splash.set_default_size(1280, 1024);
	//splash.maximize();
	splash.show_all();

	draw_splash(0);

	Glib::RefPtr<Gnome::Glade::Xml> gxml = Gnome::Glade::Xml::create(gladedir + guifile);
	
	gxml->get_widget("window1", w);
	assert( w != 0 );
	w->signal_show().connect( sigc::mem_fun(*this, &MainWindow::on_show) );

	draw_splash(1);
}
//---------------------------------------------------------------------------------------
MainWindow::~MainWindow()
{
	delete w;
}
//---------------------------------------------------------------------------------------
MainWindow* MainWindow::Instance(string gladedir, string guifile, string svgdir)
{
	if(!gwindow)
		gwindow = new MainWindow(gladedir, guifile, svgdir);

	return gwindow;
}
//---------------------------------------------------------------------------------------
void MainWindow::draw_splash(const double& perc)
{
	bar.set_fraction(perc);
	while(Gtk::Main::events_pending())
	{
		Gtk::Main::iteration();
	}
}
//---------------------------------------------------------------------------------------
void MainWindow::on_show()
{
	cout << "MainWindow::on_show()" << endl;
	splash.hide();
}
//---------------------------------------------------------------------------------------