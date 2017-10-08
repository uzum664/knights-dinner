#include "Knight.h"
#include "KnightState.h"
#include "Place.h"
#include <sstream>
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// ---------------------------------------------------------------------------
KnightTransientState* KnightTransientState::inst_ = NULL;
// ---------------------------------------------------------------------------
KnightTransientState::KnightTransientState()
{
}
// ---------------------------------------------------------------------------
KnightTransientState::~KnightTransientState()
{
}
// ---------------------------------------------------------------------------
KnightTransientState* KnightTransientState::Instance()
{
	if( inst_ == NULL )
		inst_ =  new KnightTransientState();
	return inst_;
}
// ---------------------------------------------------------------------------
void KnightTransientState::Destroy()
{
	if( inst_ )
		delete inst_;
	inst_ = NULL;
}
// ---------------------------------------------------------------------------
void KnightTransientState::step( Knight* knight )
{
	Place* place = getPlace(knight);
	
	// если не голодны, болтаем
	if( !knight->isHungry() )
	{
		changeState( knight, KnightTalkState::Instance() );
		return;
	}
	// если ножи одинаковые, болтаем
	if( !place->isKnifesDifferent() )
	{
		// запрашиваем соседей на смену ножей
		// place->queryOtherLeftKnife();
		// place->queryOtherRightKnife();
		ostringstream os;
		os << *knight << " ask for swapping knifes" << endl;
		cout << os.str();
		knight->setWaitingDifferentKnifes( true );
		changeState( knight, KnightTalkState::Instance() );
		return;
	}
	// если левый нож занят, болтаем
	if( !place->takeLeftKnife() )
	{
		changeState( knight, KnightTalkState::Instance() );
		return;
	}
	// если правый нож занят, болтаем
	if( !place->takeRightKnife() )
	{
		place->putLeftKnife();
		changeState( knight, KnightTalkState::Instance() );
		return;
	}
	  
	changeState( knight, KnightEatState::Instance() );
}
// ---------------------------------------------------------------------------
