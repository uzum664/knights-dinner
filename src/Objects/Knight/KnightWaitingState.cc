#include "Knight.h"
#include "KnightState.h"
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
	if( !hasPlace(knight) )
		return;
	
	changeState( knight, KnightTransientState::Instance() );
}
// ---------------------------------------------------------------------------
