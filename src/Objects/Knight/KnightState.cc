#include "Knight.h"
#include "KnightState.h"
#include "Place.h"
#include "Configuration.h"
#include <sstream>
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// ---------------------------------------------------------------------------
KnightState* KnightState::inst_ = NULL;
// ---------------------------------------------------------------------------
KnightState::KnightState()
{
}
// ---------------------------------------------------------------------------
KnightState::~KnightState()
{
}
// ---------------------------------------------------------------------------
KnightState* KnightState::Instance()
{
	if( inst_ == NULL )
		inst_ =  new KnightState();
	return inst_;
}
// ---------------------------------------------------------------------------
void KnightState::Destroy()
{
	if( inst_ )
		delete inst_;
	inst_ = NULL;
}
// ---------------------------------------------------------------------------
bool KnightState::activate( Knight* knight )
{
	ostringstream os;
	os << knight << "::activate()" <<  endl;
	cout << os.str();
	return true;
}
// ---------------------------------------------------------------------------
bool KnightState::deactivate( Knight* knight )
{
	return true;
}
// ---------------------------------------------------------------------------
void KnightState::changeState( Knight* knight, KnightState* m )
{
	knight->changeState(m);
}
// ---------------------------------------------------------------------------
KnightState* KnightState::getState( Knight* knight )
{
	return knight->state_;
}
// ---------------------------------------------------------------------------
bool KnightState::isKnifesAvailable( Knight* knight )
{
	Place* place = getPlace(knight);
	if( place->isLeftKnifeTaken() || place->isRightKnifeTaken() )
		return false;
	return true;
}
// ---------------------------------------------------------------------------
bool KnightState::isKnifesDifferent( Knight* knight )
{
	Place* place = getPlace(knight);
	return place->isKnifesDifferent();
}
// ---------------------------------------------------------------------------
bool KnightState::takeKnifes( Knight* knight )
{
	Place* place = getPlace(knight);
	// проверяем что правый нож не занят (иначе левый брать бесполезно)
	if( place->isRightKnifeTaken() )
		return false;
	// пытаемся взять ножи
	if( !place->takeLeftKnife() )
		return false;
	
	MESSAGE(knight, " взял нож слева");
	
	if( !place->takeRightKnife() )
	{
		MESSAGE(knight, " положил нож слева");
		place->putLeftKnife();
		return false;
	}
	
	MESSAGE(knight, " взял нож справа");
	
	knight->has_left_knife_ = true;
	knight->has_right_knife_ = true;
	return true;
}
// ---------------------------------------------------------------------------
bool KnightState::putKnifes( Knight* knight )
{
	if( !knight->has_left_knife_ || !knight->has_right_knife_ )
		return false;
	
	Place* place = getPlace(knight);
	place->putLeftKnife();
	place->putRightKnife();
	knight->has_left_knife_ = false;
	knight->has_right_knife_ = false;
	MESSAGE(knight, " положил нож слева");
	MESSAGE(knight, " положил нож справа");
	return true;
}
// ---------------------------------------------------------------------------
bool KnightState::swapKnifes( Knight* knight )
{
	if( !knight->has_left_knife_ || !knight->has_right_knife_ )
		return false;
	
	Place* place = getPlace(knight);
	knight->need_swap_knifes_ = false;
	knight->swapped_knifes_ = true;
	place->swapKnifes();
	MESSAGE(knight, " поменял ножи местам");
	
	return true;
}
// ---------------------------------------------------------------------------
