#include "HungrySimpleDinner.h"
#include "Knight/HungryKnight.h"
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
HungrySimpleDinner::HungrySimpleDinner( const int& num ) :
	Dinner(num)
{
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
		if( (*it)->isWaitingDifferentKnifes() )
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