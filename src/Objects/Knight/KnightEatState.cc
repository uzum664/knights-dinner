#include "Knight.h"
#include "KnightState.h"
#include "Configuration.h"
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
	
	// едим сначала, что бы алгоритму было проще подсчитывать приоритеты
	eat(knight);
	MESSAGE(knight, " кушает");
	
	// выставляем время окончания приема пищи
	setStateEndTime( time(NULL) + knight->getEatTimeout() );
	
	// сбрасываем флаг, чтоб иметь возможность поменять ножи
	resetSwappedKnifes(knight);
	
	ostringstream os;
	os << knight << "::activate()" <<  endl;
	cout << os.str();
	return true;
}
// ---------------------------------------------------------------------------
bool KnightEatState::deactivate( Knight* knight )
{
	// Поели, положили ножи на место
	// Если нужно поменяли ножи местами
	if( knight->needSwapKnifes() )
		swapKnifes(knight);
	
	putKnifes(knight);
	return true;
}
// ---------------------------------------------------------------------------
void KnightEatState::step( Knight* knight )
{
	// проверяем кончилась ли еда
	if( isStateEndTime( time(NULL) ) )
	{
		changeState( knight, KnightTransientState::Instance() );
		return;
	}
}
// ---------------------------------------------------------------------------
