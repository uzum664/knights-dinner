#include "Knife.h"
#include "Configuration.h"
#include <errno.h>
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
Knife::Knife()
{
	int status = pthread_mutex_init(&taken_mutex_, NULL);
	if (status != 0) {
		ostringstream os;
		os << "Knife(): error: can't create mutex, status = " << status;
		throw Exception( os.str() );
	}
}
//---------------------------------------------------------------------------------------
Knife::~Knife()
{
	int status = pthread_mutex_destroy(&taken_mutex_);
	if (status != 0) {
		ostringstream os;
		os << "Knife(): error: can't destroy mutex, status = " << status;
		throw Exception( os.str() );
	}
}
//---------------------------------------------------------------------------------------
bool Knife::take()
{
	bool ret = false;
	pthread_mutex_lock(&taken_mutex_);
	if( !taken_ )
	{
		taken_ = true;
		ret = true;
	}
	pthread_mutex_unlock(&taken_mutex_);
	return ret;
}
//---------------------------------------------------------------------------------------
bool Knife::put()
{
	bool ret = false;
	pthread_mutex_lock(&taken_mutex_);
	if( taken_ )
	{
		taken_ = false;
		ret = true;
	}
	// посылаем сигнал, если кто то ждет
	pthread_cond_signal(&taken_cond_);
	pthread_mutex_unlock(&taken_mutex_);
	return ret;
}
//---------------------------------------------------------------------------------------
bool Knife::lookFor( const int& ms )
{
	pthread_mutex_lock(&taken_mutex_);
	
	if( !taken_ )
	{
		pthread_mutex_unlock(&taken_mutex_);
		return true;
	}
	
	struct timespec stime;
	int now = time(NULL);
	stime.tv_sec = now + ms / 1000;
	if( pthread_cond_timedwait(&taken_cond_, &taken_mutex_, &stime) == ETIMEDOUT )
	{
		pthread_mutex_unlock(&taken_mutex_);
		return false;
	}
	
	pthread_mutex_unlock(&taken_mutex_);
	return true;
}
//---------------------------------------------------------------------------------------
bool Knife::isTaken()
{
	bool taken;
	pthread_mutex_lock(&taken_mutex_);
	taken = taken_;
	pthread_mutex_unlock(&taken_mutex_);
	return taken;
}
//---------------------------------------------------------------------------------------
std::ostream& knights::operator<<(std::ostream& os, Knife& knife)
{
	return os << knife.type_;
}
//---------------------------------------------------------------------------------------
std::ostream& knights::operator<<(std::ostream& os, Knife* knife)
{
	if( knife )
		return os << knife->type_;
	return os << "";
}
//---------------------------------------------------------------------------------------