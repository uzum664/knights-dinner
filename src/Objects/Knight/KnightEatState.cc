#include "Knight.h"
#include "KnightState.h"
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
bool KnightEatState::activate( Knight* knight )
{
	// если не смогли взять ножи (кто то успел раньше?)
	if( !takeKnifes(knight) )
		return false;
	
	ostringstream os;
	os << knight << "::activate()" <<  endl;
	cout << os.str();
	return true;
}
// ---------------------------------------------------------------------------
bool KnightEatState::deactivate( Knight* knight )
{
	putKnifes(knight);
	return true;
}
// ---------------------------------------------------------------------------
void KnightEatState::step( Knight* knight )
{
	eat(knight);
	
	usleep( knight->getEatTimeout() * 1000 ) ;
	
	// Поели, положили ножи на место
	// Если нужно поменяли ножи местами
	if( needSwapKnifes(knight) )
		swapKnifes(knight);
	  
	changeState( knight, KnightTransientState::Instance() );
}
// ---------------------------------------------------------------------------
