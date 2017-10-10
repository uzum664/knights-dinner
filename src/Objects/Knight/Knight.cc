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
{
	state_ = KnightWaitingState::Instance();
	state_->activate(this);
}
//---------------------------------------------------------------------------------------
Knight::~Knight()
{
}
//---------------------------------------------------------------------------------------
void Knight::lookFor(Knight* knight)
{
	int status = pthread_join(knight->thread_, NULL);
	if( status != 0 )
	{
		ostringstream os;
		os << "main(): error: can't join fknife_thread, status = " << status;
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
	while( hunger > 0 )
	{
		// обернул в ostringstream что бы логи рыцарей не накладывались друг на друга
		ostringstream os;
		os << *this << " hunger=" << hunger << " stories=" << story_num_ << " eatings=" << meal_num_ << endl;
		cout << os.str();
		pthread_mutex_lock(&mutex_);
		// Рыцарь выполняет действия в зависимости от состояния
		state_->step(this);
		pthread_mutex_unlock(&mutex_);
		usleep( getPollTimeout() * 1000 ) ;
	}
	ostringstream os;
	os << *this << " ends dinner ("<< " hunger=" << hunger << " stories=" << story_num_ << " eatings=" << meal_num_ << ")" << endl;
	cout << os.str();
}
//---------------------------------------------------------------------------------------
void Knight::permit( bool permition )
{
	pthread_mutex_lock(&mutex_);
	// если забрали разрешение обедать переходим в ожидании
	if( !permition && has_permition_ )
		changeState( KnightWaitingState::Instance() );
	has_permition_ = permition;
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
	if( place && place->take() )
	{
		place_ = place;
		pthread_mutex_unlock(&mutex_);
		return true;
	}
	pthread_mutex_unlock(&mutex_);
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