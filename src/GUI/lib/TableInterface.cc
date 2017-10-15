#include "TableInterface.h"
#include <iostream>
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// -------------------------------------------------------------------------
TableInterface* TableInterface::table_interface_ = NULL;
// -------------------------------------------------------------------------
TableInterface::TableInterface( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml ) :
	table_(NULL)
{
	if( !gladexml )
	{
		cerr << "TableInterface(): Wrong glade!" << endl;
		throw;
	}
	gladexml->get_widget("roundtable1", table_);
	if( !table_ )
	{
		cerr << "TableInterface(): No 'roundtable1' in glade!" << endl;
		throw;
	}
	Glib::signal_timeout().connect( sigc::mem_fun( this, &TableInterface::poll ), getPollTimeout() );
}
// -------------------------------------------------------------------------
TableInterface::~TableInterface()
{
}
// -------------------------------------------------------------------------
TableInterface*  TableInterface::Instance( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml )
{
	if( !table_interface_ )
		table_interface_ = new TableInterface(gladexml);
	return table_interface_;
}
// -------------------------------------------------------------------------
bool TableInterface::poll()
{
	// не заканчиваем цикл вызова
	return true;
}
// -------------------------------------------------------------------------