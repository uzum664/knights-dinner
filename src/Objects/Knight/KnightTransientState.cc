#include "Knight.h"
#include "KnightState.h"
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
	// если не голодны или рассказали хотя бы 1 историю, возвращаемся в ожидание
	if( !knight->isHungry() && knight->toldStory() )
	{
		changeState( knight, KnightWaitingState::Instance() );
		return;
	}
	// если нет разрешения обедать то болтаем
	if( !knight->hasPermision() )
	{
		ostringstream os;
		os << knight << "::step() нет разрешения" <<  endl;
		cout << os.str();
		changeState( knight, KnightTalkState::Instance() );
		return;
	}
	// если не голодны, болтаем
	if( !knight->isHungry() )
	{
		ostringstream os;
		os << knight << "::step() не голоден" <<  endl;
		cout << os.str();
		changeState( knight, KnightTalkState::Instance() );
		return;
	}
	// если ножи одинаковые, болтаем
	if( !knight->isKnifesDifferent() )
	{
		ostringstream os;
		os << knight << "::step() ножи одинаковые" <<  endl;
		cout << os.str();
		changeState( knight, KnightTalkState::Instance() );
		return;
	}
	
	// если ножи заняты, болтаем
	if( !knight->isKnifesAvailable() )
	{
		ostringstream os;
		os << knight << "::step() ножи заняты" <<  endl;
		cout << os.str();
		changeState( knight, KnightTalkState::Instance() );
		return;
	}
	
	changeState( knight, KnightEatState::Instance() );
}
// ---------------------------------------------------------------------------
