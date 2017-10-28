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
	hunger_(1)
	,running_(false)
	,name_(name)
	,has_right_knife_(false)
	,has_left_knife_(false)
	,meal_num_(0)
	,story_num_(0)
	,has_permition_(false)
	,waiting_(false)
	,place_(NULL)
	,waiting_knifes_(false)
	,need_swap_knifes_(false)
	,swapped_knifes_(false)
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
	int status = pthread_mutex_destroy(&mutex_);
	if (status != 0) {
		ostringstream os;
		os << "Knife(): error: can't destroy mutex, status = " << status;
		throw Exception( os.str() );
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
		pthread_mutex_lock(&mutex_);
		// Рыцарь выполняет действия в зависимости от состояния
		state_->step(this);
		pthread_mutex_unlock(&mutex_);
		usleep( getPollTimeout() * 1000 ) ;
	}
}
//---------------------------------------------------------------------------------------
std::string Knight::textStatistic()
{
	ostringstream os;
	// лочим mutex что бы гарантировать что в поток os попадут актуальные данные
	pthread_mutex_lock(&mutex_);
	os << *this << ":\thunger=" << hunger_ << "\t meals=" << meal_num_ << "\tstories=" << story_num_ << "\tpermition=" << has_permition_;
	os << "\tleft=" << has_left_knife_ << "\t right=" << has_right_knife_ << "\twaiting=" << waiting_knifes_ << "\tneed_swap=" << need_swap_knifes_;
	pthread_mutex_unlock(&mutex_);
	return os.str();
}
//---------------------------------------------------------------------------------------
void Knight::permit( bool permition )
{
	pthread_mutex_lock(&mutex_);
	has_permition_ = permition;
	pthread_mutex_unlock(&mutex_);
}
//---------------------------------------------------------------------------------------
void Knight::wait( bool set )
{
	pthread_mutex_lock(&mutex_);
	waiting_ = set;
	if( waiting_ )
		changeState( KnightWaitingState::Instance() );
	pthread_mutex_unlock(&mutex_);
}
//---------------------------------------------------------------------------------------
bool Knight::putOn( Place* place )
{
	pthread_mutex_lock(&mutex_);
	// если меняем место то переходим в ожидании -> оттуда попадем в переходный
	changeState( KnightWaitingState::Instance() );
	// освобождаем место если уже сидели
	if( place_ )
		place_->free();
	place_ = NULL;
	// пробуем занять место
	if( place && place->take(reinterpret_cast<Place::Owner>(this)) )
	{
		place_ = place;
		pthread_mutex_unlock(&mutex_);
		return true;
	}
	pthread_mutex_unlock(&mutex_);
	return false;
}
//---------------------------------------------------------------------------------------
bool Knight::askSwapKnifes()
{
	pthread_mutex_lock(&mutex_);
	if( !place_ )
	{
		pthread_mutex_unlock(&mutex_);
		return false;
	}
	if( !place_->isKnifesDifferent() )
	{
		pthread_mutex_unlock(&mutex_);
		return false;
	}
	if( swapped_knifes_ )
	{
		pthread_mutex_unlock(&mutex_);
		return false;
	}
	need_swap_knifes_ = true;
	pthread_mutex_unlock(&mutex_);
	return true;
}
//---------------------------------------------------------------------------------------
bool Knight::hasDifferentKnifes()
{
	pthread_mutex_lock(&mutex_);
	if( !place_ )
	{
		pthread_mutex_unlock(&mutex_);
		return false;
	}
	if( !place_->isKnifesDifferent() )
	{
		pthread_mutex_unlock(&mutex_);
		return false;
	}
	pthread_mutex_unlock(&mutex_);
	return true;
}
//---------------------------------------------------------------------------------------
Knight::State Knight::getState()
{
	KnightState* state = state_; // копируем указатель в локальную переменную (атомарная операция)
	if( dynamic_cast<KnightWaitingState*>(state) )
		return WAITING;
	else if( dynamic_cast<KnightEatState*>(state) )
		return EAT;
	else if( dynamic_cast<KnightTalkState*>(state) )
		return TALK;
	else if( dynamic_cast<KnightTransientState*>(state) )
		return TRANSIENT;
	return WAITING;
}
// ---------------------------------------------------------------------------
bool Knight::isKnifesAvailable()
{
	Place* place = place_; // копируем указатель в локальную переменную (атомарная операция)
	if( place->isLeftKnifeTaken() || place->isRightKnifeTaken() )
		return false;
	return true;
}
// ---------------------------------------------------------------------------
bool Knight::isKnifesDifferent()
{
	Place* place = place_; // копируем указатель в локальную переменную (атомарная операция)
	return place->isKnifesDifferent();
}
//---------------------------------------------------------------------------------------
void Knight::changeState( KnightState* state )
{
	KnightState* old = state_;
	state_ = state;

	try
	{
		old->deactivate(this);
		if( !state_->activate(this) )
			throw Exception("activate failed!");
	}
	catch (Exception& ex)
	{
		ostringstream os;
		os << (*this) << "(changeState): " << ex.what() << endl;
		cerr << os.str();
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