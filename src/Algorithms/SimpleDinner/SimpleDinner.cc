#include "SimpleDinner.h"
#include "Knight/Knight.h"
#include "Configuration.h"
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
SimpleDinner::SimpleDinner( const int& num ) :
	Dinner(num)
{
	ostringstream os;
	os << "Новый алгоритм 'Простой обед'";
	cout << os.str() << endl;
	MessageQueue::push(os.str());
}
//---------------------------------------------------------------------------------------
SimpleDinner::SimpleDinner( const Dinner& dinner ) :
	Dinner(dinner)
{
	ostringstream os;
	os << "Алгоритм изменен на 'Простой обед'";
	cout << os.str() << endl;
	MessageQueue::push(os.str());
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
		!(*it)->hasDifferentKnifes() && (*it)->isWaitingDifferentKnifes() && ( prev->askSwapKnifes() || next->askSwapKnifes() );
		
		prev = *it;
	}
}
//---------------------------------------------------------------------------------------