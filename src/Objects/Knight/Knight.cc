#include "Knight.h"
#include "KnightState.h"
#include "Configuration.h"
#include "Place.h"
#include <unistd.h>
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
Knight::Knight( const std::string& name ) :
	running_(false)
	,name_(name)
	,has_right_knife_(false)
	,has_lelt_knife_(false)
	,meal_num_(0)
	,story_num_(0)
	,has_permition_(false)
	,hunger(1)
	,place_(NULL)
	,waiting_knifes_(false)
	,need_swap_knifes_(false)
{
	int status = pthread_mutex_init(&mutex_, NULL);
	if (status != 0) {
		ostringstream os;
		os << "Knife(): error: can't create mutex, status = " << status;
		throw Exception( os.str() );
	}
	state_ = KnightWaitingState::Instance();
	state_->activate(this);
}
//---------------------------------------------------------------------------------------
Knight::~Knight()
{
	int status = pthread_mutex_destroy(&mutex_);
	if (status != 0) {
		ostringstream os;
		os << "Knife(): error: can't destroy mutex, status = " << status;
		throw Exception( os.str() );
	}
	// прерываем поток
	if( running_ )
	{
		int status = pthread_cancel(thread_);
		if( status != 0 )
		{
			ostringstream os;
			os << "main(): error: can't cancel thread, status = " << status;
			throw Exception( os.str() );
		}
	}
	if( place_ )
	{
		place_->putLeftKnife();
		place_->putRightKnife();
	}
}
//---------------------------------------------------------------------------------------
void Knight::lookFor(Knight* knight)
{
	int status = pthread_join(knight->thread_, NULL);
	if( status != 0 )
	{
		ostringstream os;
		os << "main(): error: can't join thread, status = " << status;
		throw Exception( os.str() );
	}
}
//---------------------------------------------------------------------------------------
void* knights::knight_thread( void* param )
{
	Knight* knight = reinterpret_cast<Knight*>(param);
	if( knight )
		knight->thread();
}
//---------------------------------------------------------------------------------------
void Knight::run()
{
	if( running_ )
		return;
	pthread_attr_init(&thread_attr_);
	int status = pthread_create( &thread_, &thread_attr_, &knights::knight_thread, this);
	if( status != 0 ) {
		ostringstream os;
		os << "run(): error: can't create thread, status = " << status;
		throw Exception( os.str() );
	}
	running_ = true;
}
//---------------------------------------------------------------------------------------
void Knight::thread()
{
	// поток рыцаря, он всегда что нибудь делает, поток будет прерван в деструкторе рыцаря
	while( true )
	{
		// Рыцарь выполняет действия в зависимости от состояния
		state_->step(this);
		usleep( getPollTimeout() * 1000 ) ;
	}
}
//---------------------------------------------------------------------------------------
bool Knight::askSwapKnifes()
{
	if( !place_ )
		return false;
	if( !place_->isKnifesDifferent() )
		return false;
	setSwapKnifes( true );
	return true;
}
//---------------------------------------------------------------------------------------
void Knight::setSwapKnifes( bool swap )
{
	pthread_mutex_lock(&mutex_);
	need_swap_knifes_ = swap;
	pthread_mutex_unlock(&mutex_);
}
//---------------------------------------------------------------------------------------
bool Knight::needSwapKnifes()
{
	bool swap;
	pthread_mutex_lock(&mutex_);
	swap = need_swap_knifes_;
	pthread_mutex_unlock(&mutex_);
	return swap;
}
//---------------------------------------------------------------------------------------
void Knight::setWaitingDifferentKnifes( bool waiting )
{
	pthread_mutex_lock(&mutex_);
	waiting_knifes_ = waiting;
	pthread_mutex_unlock(&mutex_);
}
//---------------------------------------------------------------------------------------
bool Knight::isWaitingDifferentKnifes()
{
	bool waiting;
	pthread_mutex_lock(&mutex_);
	waiting = waiting_knifes_;
	pthread_mutex_unlock(&mutex_);
	return waiting;
}
//---------------------------------------------------------------------------------------
void Knight::permit( bool permition )
{
	// если забрали разрешение обедать переходим в ожидании
	if( !permition && has_permition_ )
		changeState( KnightWaitingState::Instance() );
	has_permition_ = permition;
}
//---------------------------------------------------------------------------------------
bool Knight::putOn( Place* place )
{
	// если меняем место то переходим в ожидании -> оттуда попадем в переходный
	changeState( KnightWaitingState::Instance() );
	// освобождаем место если уже сидели
	if( place_ )
		place_->free();
	// пробуем занять место
	if( place && place->take() )
	{
		place_ = place;
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------------
void Knight::changeState( KnightState* state )
{
	KnightState* old = state_;
	state_ = state;

	try
	{
		old->deactivate(this);
		state->activate(this);
	}
	catch (Exception& ex)
	{
		cerr << (*this) << "(changeState): " << ex.what() << endl;
		state_ = old;
		state_->activate(this);
	}
}
//---------------------------------------------------------------------------------------
std::ostream& knights::operator<<(std::ostream& os, Knight& knight)
{
	if( knight.state_ )
		return os << knight.name_ << "(" << knight.state_->stateName() << ")";
	return os << knight.name_ << "(???State)";
}
//---------------------------------------------------------------------------------------
std::ostream& knights::operator<<(std::ostream& os, Knight* knight)
{
	if( knight )
		return os << *knight;
	return os << "";
}
//---------------------------------------------------------------------------------------