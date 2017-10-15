#include "TableInterface.h"
#include "Knight/Knight.h"
#include "Knife/Knife.h"
#include "Table/Table.h"
#include "Table/Place.h"
#include <iostream>
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// -------------------------------------------------------------------------
TableInterface* TableInterface::table_interface_ = NULL;
// -------------------------------------------------------------------------
TableInterface::TableInterface( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml ) :
	gui_table_(NULL)
{
	if( !gladexml )
	{
		cerr << "TableInterface(): Wrong glade!" << endl;
		throw;
	}
	gladexml->get_widget("roundtable1", gui_table_);
	if( !gui_table_ )
	{
		cerr << "TableInterface(): No 'roundtable1' in glade!" << endl;
	//	throw;
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
	Table* table = Table::Instance();
	if( !table )
		return true;
	int i = 0;
	for( Table::Places::iterator it = table->places_.begin() ; it != table->places_.end(); ++it, ++i )
	{
		if( !*it )
			continue;
		if( (*it)->isLeftKnifeTaken() )
		{
			ostringstream os;
			os << "TableInterface" << "::poll() нож " << (i-1) << " занят" <<  endl;
			cout << os.str();
		}
		if( (*it)->isRightKnifeTaken() )
		{
			ostringstream os;
			os << "TableInterface" << "::poll() нож " << i << " занят" <<  endl;
			cout << os.str();
		}
	}
	i = 0;
	for(Table::Knifes::iterator it = table->knifes_.begin() ; it != table->knifes_.end(); ++it, ++i )
	{
		if( !*it )
			continue;
	}
	
	// не заканчиваем цикл вызова
	return true;
}
// -------------------------------------------------------------------------