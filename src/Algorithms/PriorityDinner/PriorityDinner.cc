#include "PriorityDinner.h"
#include "Knight/HungryKnight.h"
#include "Configuration.h"
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
PriorityDinner::PriorityDinner( const int& num ) :
	Dinner(num)
	,max_permitions_(num / 2) // инициализируем максимально возможным кол-вом пар разных ножей
{
	ostringstream os;
	os << "Новый алгоритм 'Обед с приоритетами'";
	cout << os.str() << endl;
	MessageQueue::push(os.str());
}
//---------------------------------------------------------------------------------------
PriorityDinner::PriorityDinner( const Dinner& dinner ) :
	Dinner(dinner)
	,max_permitions_(getPlaceNum() / 2)
{
	ostringstream os;
	os << "Алгоритм изменен на 'Обед с приоритетами'";
	cout << os.str() << endl;
	MessageQueue::push(os.str());
}
//---------------------------------------------------------------------------------------
PriorityDinner::~PriorityDinner()
{
}
//---------------------------------------------------------------------------------------
void PriorityDinner::start()
{
	// наполняем список сортируемый по голоду
	for(Knights::iterator it = knights_.begin() ; it != knights_.end(); ++it )
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
	Knight* prev = knights_.back();
	Knight* next = NULL;
	for(Knights::iterator it = knights_.begin() ; it != knights_.end(); ++it )
	{
		Knights::iterator nextIt = it;
		nextIt++;
		if( nextIt == knights_.end() )
			next = knights_.front();
		else
			next = *nextIt;
		
		// проверяем что рыцарю нужен другой тип ножа и что ему разрешено кушать, запрашиваем у соседей поочереди
		!(*it)->hasDifferentKnifes() && (*it)->isWaitingDifferentKnifes() && (*it)->hasPermision() && ( prev->askSwapKnifes() || next->askSwapKnifes() );
		
		prev = *it;
	}
}
//---------------------------------------------------------------------------------------