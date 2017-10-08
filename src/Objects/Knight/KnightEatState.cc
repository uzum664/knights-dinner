#include "Knight.h"
#include "KnightState.h"
#include "Place.h"
#include <unistd.h>
#include <sstream>
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
	
	// Поели, положили ножи на место
	Place* place = getPlace(knight);
	// Если нужно поменяли ножи местами
	if( knight->needSwapKnifes() )
	{
		ostringstream os;
		os << *knight << " swap knifes" << endl;
		cout << os.str();
		knight->setSwapKnifes( false );
		place->swapKnifes();
	}
	place->putLeftKnife();
	place->putRightKnife();
	  
	changeState( knight, KnightTransientState::Instance() );
}
// ---------------------------------------------------------------------------
