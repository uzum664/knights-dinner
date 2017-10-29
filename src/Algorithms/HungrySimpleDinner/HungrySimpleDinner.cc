#include "HungrySimpleDinner.h"
#include "Knight/HungryKnight.h"
#include "Configuration.h"
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
HungrySimpleDinner::HungrySimpleDinner( const int& num ) :
	Dinner(num)
{
	ostringstream os;
	os << "Новый алгоритм 'Обед голодных рыцарей'";
	cout << os.str() << endl;
	MessageQueue::push(os.str());
}
//---------------------------------------------------------------------------------------
HungrySimpleDinner::HungrySimpleDinner( const Dinner& dinner ) :
	Dinner(dinner)
{
	ostringstream os;
	os << "Алгоритм изменен на 'Обед голодных рыцарей'";
	cout << os.str() << endl;
	MessageQueue::push(os.str());
}
//---------------------------------------------------------------------------------------
HungrySimpleDinner::~HungrySimpleDinner()
{
}
//---------------------------------------------------------------------------------------
void HungrySimpleDinner::step()
{
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