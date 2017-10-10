#include "SimpleDinner.h"
#include "Table/Table.h"
#include "Knight/Knight.h"
#include <unistd.h>
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
SimpleDinner::SimpleDinner( const int& num ) :
	place_num_(num)
{
	table = Table::Instance(5);
}
//---------------------------------------------------------------------------------------
SimpleDinner::~SimpleDinner()
{
	for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		if( *it )
			delete *it;
}
//---------------------------------------------------------------------------------------
void SimpleDinner::loop()
{
	while( true )
	{
		bool anyoneHungry = false;
		bool someoneNotToldStory = false;
		
		Knight* prev = knights.back();
		Knight* next = NULL;
		for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		{
			Knights::iterator nextIt = it;
			nextIt++;
			if( nextIt == knights.end() )
				next = knights.front();
			else
				next = *nextIt;
			
			// проверяем что хоть кто то голоден
			if( (*it)->isHungry() )
				anyoneHungry = true;
			// проверяем что хоть кто то не расказывал историю
			if( !(*it)->toldStory() )
				someoneNotToldStory = true;
			
			// проверяем что рыцарю нужен другой тип ножа, запрашиваем у соседей поочереди
			// если у соседей нашелся подходящий нож то флаг ожидания ножа сбрасываем
			if( (*it)->isWaitingDifferentKnifes() && ( prev->askSwapKnifes() || next->askSwapKnifes() ) )
				(*it)->resetWaitingDifferentKnifes();
			
			prev = *it;
		}
		
		if( !anyoneHungry && !someoneNotToldStory )
			break;
		
		usleep(100000);
	}
}
//---------------------------------------------------------------------------------------
void SimpleDinner::start()
{
	cout << table << endl;
	for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		(*it)->permit(true);
}
//---------------------------------------------------------------------------------------
void SimpleDinner::stop()
{
	for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		(*it)->permit(false);
}
//---------------------------------------------------------------------------------------
bool SimpleDinner::addKnight( const std::string& name )
{
	if( knights.size() >= place_num_ )
		return false;
	Knight* knight = new Knight( name );
	knight->putOn( table->findFreePlace() );
	knight->run();
	knights.push_back( knight );
	return true;
}
//---------------------------------------------------------------------------------------