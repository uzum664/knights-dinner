#include "Knight.h"
#include "KnightState.h"
#include <sstream>
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// ---------------------------------------------------------------------------
KnightWaitingState* KnightWaitingState::inst_ = NULL;
// ---------------------------------------------------------------------------
KnightWaitingState::KnightWaitingState()
{
}
// ---------------------------------------------------------------------------
KnightWaitingState::~KnightWaitingState()
{
}
// ---------------------------------------------------------------------------
KnightWaitingState* KnightWaitingState::Instance()
{
	if( inst_ == NULL )
		inst_ =  new KnightWaitingState();
	return inst_;
}
// ---------------------------------------------------------------------------
void KnightWaitingState::Destroy()
{
	if( inst_ )
		delete inst_;
	inst_ = NULL;
}
// ---------------------------------------------------------------------------
bool KnightWaitingState::activate( Knight* knight )
{
	// выставляем время окончания ожидания
	setStateEndTime( knight, time(NULL) + getWaitingTimeout(knight) );
	
	// сбрасываем флаг, чтоб иметь возможность поменять ножи
	resetSwappedKnifes(knight);
	
	ostringstream os;
	os << knight << "::activate()" <<  endl;
	cout << os.str();
	return true;
}
// ---------------------------------------------------------------------------
void KnightWaitingState::step( Knight* knight )
{
	// если не заняли место остаемся в ожидании
	if( !hasPlace(knight) )
		return;
	
	// если голодны или не рассказали хотя бы 1 историю 
	if( isHungry(knight) || !toldStory(knight) )
	{
		changeState( knight, KnightTransientState::Instance() );
		return;
	}
	
	// проверяем время ожидания
	if( isStateEndTime( knight, time(NULL) ) )
	{
		changeState( knight, KnightTransientState::Instance() );
		return;
	}
	
	// Если нужно поменяли ножи местами
	if( !needSwapKnifes(knight) )
		return;
	
	if( !takeKnifes(knight) )
		return;
	swapKnifes(knight);
	putKnifes(knight);
	
}
// ---------------------------------------------------------------------------
