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
	setStateEndTime( time(NULL) + knight->getWaitingTimeout() );
	
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
	// принудительное ожидание (пауза)
	if( knight->isWaiting() )
		return;
	
	// если не заняли место остаемся в ожидании
	if( !knight->hasPlace() )
		return;
	
	// если голодны или не рассказали хотя бы 1 историю 
	if( knight->isHungry() || !knight->toldStory() )
	{
		changeState( knight, KnightTransientState::Instance() );
		return;
	}
	
	// проверяем время ожидания
	if( isStateEndTime( time(NULL) ) )
	{
		changeState( knight, KnightTransientState::Instance() );
		return;
	}
	
	// Если нужно поменяли ножи местами
	if( !knight->needSwapKnifes() )
		return;
	
	if( !takeKnifes(knight) )
		return;
	swapKnifes(knight);
	putKnifes(knight);
	
}
// ---------------------------------------------------------------------------
