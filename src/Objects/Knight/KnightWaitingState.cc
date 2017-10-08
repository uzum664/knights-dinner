#include "Knight.h"
#include "KnightState.h"
#include "Place.h"
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
void KnightWaitingState::step( Knight* knight )
{
	// если не заняли место остаемся в ожидании
	if( !knight->hasPlace() )
		return;
	// если нет разрешения обедать остаемся в ожидании
	if( !knight->hasPermision() )
		return;
	
	// если голодны или не рассказали хотя бы 1 историю 
	if( knight->isHungry() || !knight->toldStory() )
	{
		changeState( knight, KnightTransientState::Instance() );
		return;
	}
	
	Place* place = getPlace(knight);
	// Если нужно поменяли ножи местами
	if( !needSwapKnifes(knight) )
		return;
	
	// пытаемся взять ножи
	if( !place->takeLeftKnife() )
		return;
	
	if( !place->takeRightKnife() )
	{
		place->putLeftKnife();
		return;
	}
	ostringstream os;
	os << *knight << " swap knifes" << endl;
	cout << os.str();
	resetSwapKnifes(knight);
	place->swapKnifes();
	place->putLeftKnife();
	place->putRightKnife();
}
// ---------------------------------------------------------------------------
