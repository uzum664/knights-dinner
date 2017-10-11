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
SimpleDinner::~SimpleDinner()
{
}
//---------------------------------------------------------------------------------------
void SimpleDinner::step()
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