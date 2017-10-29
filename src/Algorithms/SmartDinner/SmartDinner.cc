#include "SmartDinner.h"
#include "Knight/HungryKnight.h"
#include "Configuration.h"
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
SmartDinner::SmartDinner( const int& num ) :
	Dinner(num)
	,max_permitions_(num / 2) // инициализируем максимально возможным кол-вом пар разных ножей
{
	ostringstream os;
	os << "Новый алгоритм 'Умный обед'";
	cout << os.str() << endl;
	MessageQueue::push(os.str());
}
//---------------------------------------------------------------------------------------
SmartDinner::SmartDinner( const Dinner& dinner ) :
	Dinner(dinner)
	,max_permitions_(getPlaceNum() / 2)
{
	ostringstream os;
	os << "Алгоритм изменен на 'Умный обед'";
	cout << os.str() << endl;
	MessageQueue::push(os.str());
}
//---------------------------------------------------------------------------------------
SmartDinner::~SmartDinner()
{
}
//---------------------------------------------------------------------------------------
void SmartDinner::start()
{
	// наполняем список сортируемый по голоду
	for(Knights::iterator it = knights_.begin() ; it != knights_.end(); ++it )
		hungryKnights.push_back( *it );
	Dinner::start();
}
//---------------------------------------------------------------------------------------
void SmartDinner::step()
{
	int permitions = 0;
	// расчитываем приоритеты и выдаем 1ое разрешение
	hungryKnights.sort(HungerQuery());
	for( HungryKnights::iterator it = hungryKnights.begin(); it != hungryKnights.end(); ++it )
	{
		if( permitions < 1 && (*it)->hasDifferentKnifes() )
		{
			(*it)->permit(true);
			permitions++;
		}
		else
		{
			(*it)->permit(false);
		}
	}
	// считаем что рыцари сидят по порядку
	// пока рассадка идет через вызов table->findFreePlace() который должен выдавать по порядку
	Knight* prev = knights_.back();
	Knight* next = NULL;
	for( Knights::iterator it = knights_.begin() ; it != knights_.end(); ++it )
	{
		Knights::iterator nextIt = it;
		nextIt++;
		if( nextIt == knights_.end() )
			next = knights_.front();
		else
			next = *nextIt;
		
		// самый голодный уже получил разрешение
		// и у него уже должны быть оба ножа
		if( (*it)->hasPermision() )
		{
			prev = *it;
			continue;
		}
		// пока не выдали максимум разрешений
		if( permitions < max_permitions_ )
		{
			// выдаем только тем кто голоден, с ножами, и если рядом сидящим разрешение не выдавалось
			if( (*it)->isHungry() && (*it)->hasDifferentKnifes() && !prev->hasPermision() && !next->hasPermision() )
			{
				// так же сравниваем голод сидящих рядом
				if( (*it)->getHunger() >= prev->getHunger() || (*it)->getHunger() >= next->getHunger() )
				{
					(*it)->permit( true );
					permitions++;
				}
			}
		}
		// проверяем что рыцарю нужен другой тип ножа, запрашиваем у соседей поочереди
		if( !(*it)->hasDifferentKnifes() && (*it)->isWaitingDifferentKnifes() )
		{
			// запрашиваем только у того соседа который менее голодный
			// ну и естественно запрашивающий рыцарь должен быть голоднее
			if( prev->getHunger() <= next->getHunger() )
			{
				if( (*it)->getHunger() > prev->getHunger() && prev->askSwapKnifes() );
				else if ( ( (*it)->getHunger() > next->getHunger() ) && next->askSwapKnifes() );
			}
			else
			{
				if ( ( (*it)->getHunger() > next->getHunger() ) && next->askSwapKnifes() );
				else if( (*it)->getHunger() > prev->getHunger() && prev->askSwapKnifes() );
			}
		}
		prev = *it;
	}
}
//---------------------------------------------------------------------------------------