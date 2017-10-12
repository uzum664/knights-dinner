#include "PriorityDinner.h"
#include "Knight/HungryKnight.h"
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
PriorityDinner::PriorityDinner( const int& num ) :
	Dinner(num)
	,max_permitions_(num / 2) // инициализируем максимально возможным кол-вом пар разных ножей
{
}
//---------------------------------------------------------------------------------------
PriorityDinner::~PriorityDinner()
{
}
//---------------------------------------------------------------------------------------
void PriorityDinner::start()
{
	// наполняем список сортируемый по голоду
	for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		hungryKnights.push_back( *it );
	Dinner::start();
}
//---------------------------------------------------------------------------------------
void PriorityDinner::step()
{
	// расчитываем приоритеты и раздаем разрешение
	int maxPermitions = max_permitions_; 
	hungryKnights.sort(HungerQuery());
	for(HungryKnights::iterator it = hungryKnights.begin(); it != hungryKnights.end(); ++it, --maxPermitions )
	{
		(*it)->permit( ( maxPermitions > 0 ) && (*it)->isHungry() );
		// так как приоритетный рыцарь может не иметь возможности поесть(нехватает разных ножей), сохраняем его право для другого рыцаря 
		if( !(*it)->hasDifferentKnifes() )
			maxPermitions++;
	}
	
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
		
		// проверяем что рыцарю нужен другой тип ножа и что ему разрешено кушать, запрашиваем у соседей поочереди
		if( (*it)->isWaitingDifferentKnifes() && (*it)->hasPermision() && ( prev->askSwapKnifes() || prev->askSwapKnifes() ) );
		
		prev = *it;
	}
}
//---------------------------------------------------------------------------------------