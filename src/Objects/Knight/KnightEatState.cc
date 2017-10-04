#include "Knight.h"
#include "KnightState.h"
#include "Place.h"
#include <unistd.h>
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// ---------------------------------------------------------------------------
KnightEatState* KnightEatState::inst_ = NULL;
// ---------------------------------------------------------------------------
KnightEatState::KnightEatState()
{
}
// ---------------------------------------------------------------------------
KnightEatState::~KnightEatState()
{
}
// ---------------------------------------------------------------------------
KnightEatState* KnightEatState::Instance()
{
	if( inst_ == NULL )
		inst_ =  new KnightEatState();
	return inst_;
}
// ---------------------------------------------------------------------------
void KnightEatState::Destroy()
{
	if( inst_ )
		delete inst_;
	inst_ = NULL;
}
// ---------------------------------------------------------------------------
void KnightEatState::step( Knight* knight )
{
	eat(knight);
	
	usleep( knight->getEatTimeout() * 1000 ) ;
	
	// Поели, положини ножи на место
	Place* place = getPlace(knight);
	place->putLeftKnife();
	place->putRightKnife();
	  
	changeState( knight, KnightTransientState::Instance() );
}
// ---------------------------------------------------------------------------
