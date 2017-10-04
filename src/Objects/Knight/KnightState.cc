#include "Knight.h"
#include "KnightState.h"
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
