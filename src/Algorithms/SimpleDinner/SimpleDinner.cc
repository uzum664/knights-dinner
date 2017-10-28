#include "SimpleDinner.h"
#include "Knight/Knight.h"
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
SimpleDinner::SimpleDinner( const int& num ) :
	Dinner(num)
{
}
//---------------------------------------------------------------------------------------
SimpleDinner::SimpleDinner( const Dinner& dinner ) :
	Dinner(dinner)
{
}
//---------------------------------------------------------------------------------------
SimpleDinner::~SimpleDinner()
{
}
//---------------------------------------------------------------------------------------
void SimpleDinner::step()
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
		if( (*it)->isWaitingDifferentKnifes() && ( prev->askSwapKnifes() || next->askSwapKnifes() ) );
		
		prev = *it;
	}
}
//---------------------------------------------------------------------------------------