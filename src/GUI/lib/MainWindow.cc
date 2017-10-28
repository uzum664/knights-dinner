#include <libglademm.h>
#include <assert.h>
#include <iostream>
#include "MainWindow.h"
#include "TableInterface.h"
#include "JournalInterface.h"
#include "StatisticInterface.h"
#include "SimpleDinner/SimpleDinner.h"
#include "HungrySimpleDinner/HungrySimpleDinner.h"
#include "PriorityDinner/PriorityDinner.h"
#include <glade/glade.h>
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

	glade_xml_signal_connect(gxml->gobj(), "start", G_CALLBACK(MainWindow::on_start));
	glade_xml_signal_connect(gxml->gobj(), "stop", G_CALLBACK(MainWindow::on_stop));
	glade_xml_signal_connect(gxml->gobj(), "choose", G_CALLBACK(MainWindow::on_choose));
		
	dinner = new SimpleDinner();
	dinner->addHungryKnight("   Артур");
	dinner->addHungryKnight("  Ричард");
	dinner->addHungryKnight("Ланселот");
	dinner->addHungryKnight("   Робин");
	dinner->addHungryKnight("  Гивеон");
	
	// инициализируем обмен данных для RoundTable
	TableInterface::Instance( gxml );
	// инициализируем обмен данных для Журнала
	JournalInterface::Instance(gxml);
	// инициализируем обмен данных для Статистики
	StatisticInterface::Instance(gxml, dinner);
	
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
// -------------------------------------------------------------------------
bool MainWindow::on_start(GtkWidget* w)
{
	if( !gwindow )
		return true;
	gwindow->dinner->start();
	return false; // передаем вызов обработчику по умолчанию
}
// -------------------------------------------------------------------------
bool MainWindow::on_stop(GtkWidget* w)
{
	if( !gwindow )
		return true;
	gwindow->dinner->stop();
	return false; // передаем вызов обработчику по умолчанию
}
// -------------------------------------------------------------------------
bool MainWindow::on_choose(GtkWidget* w)
{
	if( !gwindow )
		return true;
	Gtk::RadioButton* widget = dynamic_cast<Gtk::RadioButton*>(Glib::wrap(w));
	//gwindow->dinner->stop();
	if( !widget || !widget->get_active() )
		return false;
	cout << "new algotithm=" << widget->get_name() << endl;
	Dinner* prev = gwindow->dinner;
	if( widget->get_name() == "simple_algorithm" )
		gwindow->dinner = new SimpleDinner(*gwindow->dinner);
	else if( widget->get_name() == "hungry_algorithm" )
		gwindow->dinner = new HungrySimpleDinner(*gwindow->dinner);
	else if( widget->get_name() == "priority_algorithm" )
		gwindow->dinner = new PriorityDinner(*gwindow->dinner);
	delete prev;
	//gwindow->dinner->start();
	return false; // передаем вызов обработчику по умолчанию
}
//---------------------------------------------------------------------------------------