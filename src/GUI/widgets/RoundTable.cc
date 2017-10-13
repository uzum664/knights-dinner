#include <iostream>
#include <gdkmm.h>
#include "RoundTable.h"
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// -------------------------------------------------------------------------
#define INIT_UTIMEDIAGRAM_PROPERTIES() \

// -------------------------------------------------------------------------
void
RoundTable::constructor()
{
	cout << "RoundTable::constructor()" << endl;
}
// -------------------------------------------------------------------------
RoundTable::RoundTable() :
	Glib::ObjectBase("roundtable")
	//, INIT_UTIMEDIAGRAM_PROPERTIES()
{
	constructor();
}
// -------------------------------------------------------------------------
RoundTable::RoundTable(Gtk::Fixed::BaseObjectType* gobject) :
	Gtk::Fixed(gobject)
	//, INIT_UTIMEDIAGRAM_PROPERTIES()
{
	constructor();
}
// -------------------------------------------------------------------------
RoundTable::~RoundTable()
{
}
// -------------------------------------------------------------------------
void RoundTable::on_add(Gtk::Widget* w)
{
	Gtk::Fixed::on_add(w);
}
// -------------------------------------------------------------------------
