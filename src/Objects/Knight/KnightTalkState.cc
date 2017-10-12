#include "Knight.h"
#include "KnightState.h"
#include <unistd.h>
#include <sstream>
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// ---------------------------------------------------------------------------
KnightTalkState* KnightTalkState::inst_ = NULL;
// ---------------------------------------------------------------------------
KnightTalkState::KnightTalkState()
{
}
// ---------------------------------------------------------------------------
KnightTalkState::~KnightTalkState()
{
}
// ---------------------------------------------------------------------------
KnightTalkState* KnightTalkState::Instance()
{
	if( inst_ == NULL )
		inst_ =  new KnightTalkState();
	return inst_;
}
// ---------------------------------------------------------------------------
void KnightTalkState::Destroy()
{
	if( inst_ )
		delete inst_;
	inst_ = NULL;
}
// ---------------------------------------------------------------------------
bool KnightTalkState::activate( Knight* knight )
{
	// рассказываем сначала, что бы алгоритму было проще подсчитывать приоритеты
	tellStory(knight);
	
	// выставляем время окончания рассказа
	setStateEndTime( knight, time(NULL) + knight->getTalkTimeout() );
	
	ostringstream os;
	os << knight << "::activate()" <<  endl;
	cout << os.str();
	return true;
}
// ---------------------------------------------------------------------------
bool KnightTalkState::deactivate( Knight* knight )
{
	// Ждать ножи актуально только в состоянии разговора, поэтому если вышли то сбрасываем флаг, не путаем других рыцарей
	if( isKnifesDifferent(knight) )
		resetWaitingDifferentKnifes(knight);
	
	// Поели, положили ножи на место
	// Если нужно поменяли ножи местами
	if( needSwapKnifes(knight) )
		swapKnifes(knight);
	
	putKnifes(knight);
	return true;
}
// ---------------------------------------------------------------------------
void KnightTalkState::step( Knight* knight )
{
	// проверяем кончился ли рассказ
	if( isStateEndTime( knight, time(NULL) ) )
	{
		changeState( knight, KnightTransientState::Instance() );
		return;
	}
	
	// если ножи разные то сбрасываем флаг
	// иначе запрашиваем соседей на смену ножей
	if( isKnifesDifferent(knight) )
	{
		resetWaitingDifferentKnifes(knight);
	}
	else if( !isWaitingDifferentKnifes(knight) )
	{
		ostringstream os;
		os << *knight << " ask for swapping knifes" << endl;
		cout << os.str();
		setWaitingDifferentKnifes(knight);
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
