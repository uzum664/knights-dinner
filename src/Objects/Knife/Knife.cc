#include "Knife.h"
#include "Configuration.h"
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
Knife::Knife() :
	taken_(false)
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
	pthread_mutex_unlock(&taken_mutex_);
	return ret;
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