#include "Dinner.h"
#include "Table/Table.h"
#include "Knight/Knight.h"
#include <unistd.h>
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
Dinner::Dinner( const int& num ) :
	place_num_(num)
{
	table = Table::Instance(5);
}
//---------------------------------------------------------------------------------------
Dinner::~Dinner()
{
	for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		if( *it )
			delete *it;
}
//---------------------------------------------------------------------------------------
void Dinner::loop()
{
	while( true )
	{
		step();
		bool anyoneHungry = false;
		bool someoneNotToldStory = false;
		
		for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		{
			// проверяем что хоть кто то голоден
			if( (*it)->isHungry() )
				anyoneHungry = true;
			// проверяем что хоть кто то не расказывал историю
			if( !(*it)->toldStory() )
				someoneNotToldStory = true;
		}
		
		if( !anyoneHungry && !someoneNotToldStory )
			break;
		
		usleep(100000);
	}
}
//---------------------------------------------------------------------------------------
void Dinner::start()
{
	cout << table << endl;
	for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
	{
		(*it)->permit(true);
		(*it)->putOn(table->findFreePlace());
	}
	loop();
}
//---------------------------------------------------------------------------------------
void Dinner::stop()
{
	for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		(*it)->permit(false);
}
//---------------------------------------------------------------------------------------
bool Dinner::addKnight( const std::string& name )
{
	if( knights.size() >= place_num_ )
		return false;
	Knight* knight = new Knight( name );
	knight->run();
	knights.push_back( knight );
	return true;
}
//---------------------------------------------------------------------------------------