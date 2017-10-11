#include "Knight.h"
#include "KnightState.h"
#include <unistd.h>
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
void KnightTalkState::step( Knight* knight )
{
	tellStory(knight);
	
	usleep( knight->getTalkTimeout() * 1000 ) ;
	  
	changeState( knight, KnightTransientState::Instance() );
}
// ---------------------------------------------------------------------------
