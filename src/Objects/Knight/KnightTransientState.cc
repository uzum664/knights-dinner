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
	
	// если не голодны или рассказали хотя бы 1 историю, возвращаемся в ожидание
	if( !isHungry(knight) && toldStory(knight) )
	{
		changeState( knight, KnightWaitingState::Instance() );
		return;
	}
	// если нет разрешения обедать то болтаем
	if( !hasPermision(knight) )
	{
		changeState( knight, KnightTalkState::Instance() );
		return;
	}
	// если не голодны, болтаем
	if( !isHungry(knight) )
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
		setWaitingDifferentKnifes(knight);
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
