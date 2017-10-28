#include "StatisticInterface.h"
#include "Knight/Knight.h"
#include "Knife/Knife.h"
#include "Table/Place.h"
#include <iostream>
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// -------------------------------------------------------------------------
StatisticInterface* StatisticInterface::stats_interface_ = NULL;
// -------------------------------------------------------------------------
StatisticInterface::StatisticInterface( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml, Dinner* const dinner ) :
	stats_(NULL)
{
	if( !gladexml )
	{
		cerr << "StatisticInterface(): Wrong glade!" << endl;
		throw;
	}
	gladexml->get_widget("statistic1", stats_);
	if( !stats_ )
	{
		cerr << "StatisticInterface(): No 'statistic1' in glade!" << endl;
		throw;
	}
	if( !dinner )
	{
		cerr << "StatisticInterface(): No dinner object!" << endl;
		throw;
	}
	// наполняем список рыцарей
	Dinner::Knights knights = dinner->getKnights();
	for(Dinner::Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		knights_.push_back(KnightInfo(*it));
	// подключаем отложенную инициализацию
	stats_->signal_realize().connect( sigc::mem_fun( this, &StatisticInterface::init) );
	// цикл алгоритма обновления
	Glib::signal_timeout().connect( sigc::mem_fun( this, &StatisticInterface::poll ), getPollTimeout() );
}
// -------------------------------------------------------------------------
StatisticInterface::~StatisticInterface()
{
}
// -------------------------------------------------------------------------
StatisticInterface*  StatisticInterface::Instance( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml, Dinner* const dinner )
{
	if( !stats_interface_ )
		stats_interface_ = new StatisticInterface(gladexml, dinner);
	return stats_interface_;
}
// -------------------------------------------------------------------------
void StatisticInterface::init()
{
	// добавляем рыцарей в таблицу в том порядке, как сидят
	for(Knights::iterator it = knights_.begin() ; it != knights_.end(); ++it )
		it->row = stats_->addRow();
}
// -------------------------------------------------------------------------
bool StatisticInterface::poll()
{
	for(Knights::iterator it = knights_.begin() ; it != knights_.end(); ++it )
	{
		Statistic::ColumnsPack pack;
		ostringstream os;
		os << it->knight->getName();
		pack.name = os.str();
		switch( it->knight->getState() )
		{
			case Knight::WAITING:
				pack.state = "ожидает";
				break;
			case Knight::EAT:
				pack.state = "кушает";
				break;
			case Knight::TALK:
				pack.state = "рассказывает";
				break;
		}
		Place* place = it->knight->getPlace();
		if( place )
		{
			if( dynamic_cast<FoodKnife*>(*place->getLeftKnife()) )
				pack.left_knife = Statistic::FOOD_KNIFE;
			else if( dynamic_cast<CutterKnife*>(*place->getLeftKnife()) )
				pack.left_knife = Statistic::CUTTER_KNIFE;
			
			if( dynamic_cast<FoodKnife*>(*place->getRightKnife()) )
				pack.right_knife = Statistic::FOOD_KNIFE;
			else if( dynamic_cast<CutterKnife*>(*place->getRightKnife()) )
				pack.right_knife = Statistic::CUTTER_KNIFE;
		}
		
		pack.meals = it->knight->getMeals();
		pack.stories = it->knight->getStories();
		stats_->updateRow(it->row, pack);
	}
	// не заканчиваем цикл вызова
	return true;
}
// -------------------------------------------------------------------------