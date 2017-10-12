#include "Knight.h"
#include "KnightState.h"
#include "Place.h"
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
	// пытаемся взять ножи
	if( !place->takeLeftKnife() )
		return false;
	
	if( !place->takeRightKnife() )
	{
		place->putLeftKnife();
		return false;
	}
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
	return true;
}
// ---------------------------------------------------------------------------
bool KnightState::swapKnifes( Knight* knight )
{
	if( !knight->has_left_knife_ || !knight->has_right_knife_ )
		return false;
	Place* place = getPlace(knight);
	ostringstream os;
	os << *knight << " swap knifes" << endl;
	cout << os.str();
	knight->need_swap_knifes_ = false; 
	place->swapKnifes();
	return true;
}
// ---------------------------------------------------------------------------
