#include "StatisticInterface.h"
#include <iostream>
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// -------------------------------------------------------------------------
StatisticInterface* StatisticInterface::stats_interface_ = NULL;
// -------------------------------------------------------------------------
StatisticInterface::StatisticInterface( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml )
//	stats_(NULL)
{
	if( !gladexml )
	{
		cerr << "StatisticInterface(): Wrong glade!" << endl;
		throw;
	}
	/*gladexml->get_widget("statistic1", stats_);
	if( !stats_ )
	{
		cerr << "StatisticInterface(): No 'statistic1' in glade!" << endl;
		throw;
	}*/
	Glib::signal_timeout().connect( sigc::mem_fun( this, &StatisticInterface::poll ), getPollTimeout() );
}
// -------------------------------------------------------------------------
StatisticInterface::~StatisticInterface()
{
}
// -------------------------------------------------------------------------
StatisticInterface*  StatisticInterface::Instance( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml )
{
	if( !stats_interface_ )
		stats_interface_ = new StatisticInterface(gladexml);
	return stats_interface_;
}
// -------------------------------------------------------------------------
bool StatisticInterface::poll()
{
	// не заканчиваем цикл вызова
	return true;
}
// -------------------------------------------------------------------------