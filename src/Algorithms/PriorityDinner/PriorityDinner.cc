#include "PriorityDinner.h"
#include "Knight/HungryKnight.h"
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
PriorityDinner::PriorityDinner( const int& num ) :
	Dinner(num)
{
}
//---------------------------------------------------------------------------------------
PriorityDinner::~PriorityDinner()
{
}
//---------------------------------------------------------------------------------------
void PriorityDinner::step()
{
	// считаем что рыцари сидят по порядку
	// пока рассадка идет через вызов table->findFreePlace() который должен выдавать по порядку
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
		
		// проверяем что рыцарю нужен другой тип ножа, запрашиваем у соседей поочереди
		// если у соседей нашелся подходящий нож то флаг ожидания ножа сбрасываем
		if( (*it)->isWaitingDifferentKnifes() && ( prev->askSwapKnifes() || next->askSwapKnifes() ) )
			(*it)->resetWaitingDifferentKnifes();
		
		prev = *it;
	}
}
//---------------------------------------------------------------------------------------
bool PriorityDinner::addKnight( const std::string& name )
{
	if( knights.size() >= getPlaceNum() )
		return false;
	Knight* knight = new HungryKnight( name, 4 );
	knight->run();
	knights.push_back( knight );
	return true;
}
//---------------------------------------------------------------------------------------