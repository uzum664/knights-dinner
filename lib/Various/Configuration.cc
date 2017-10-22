// -------------------------------------------------------------------------
#include "Configuration.h"
#include <fstream>
// -------------------------------------------------------------------------
using namespace std;
// -------------------------------------------------------------------------
namespace knights
{

Exception::Exception(const std::string& description) throw() : description_(description)
{
}
// -------------------------------------------------------------------------
const char* Exception::what() const throw()
{
	return description_.c_str();
}
// -------------------------------------------------------------------------
MessageQueue* MessageQueue::message_queue_ = NULL;
// -------------------------------------------------------------------------
MessageQueue* MessageQueue::Instance()
{
	if( !message_queue_ )
		message_queue_ = new MessageQueue();
	return message_queue_;
}
// -------------------------------------------------------------------------
MessageQueue::MessageQueue()
{
	int status = pthread_mutex_init(&mutex_, NULL);
	if (status != 0) {
		ostringstream os;
		os << "Knife(): error: can't create mutex, status = " << status;
		throw Exception( os.str() );
	}
}
// -------------------------------------------------------------------------
MessageQueue::~MessageQueue()
{
	int status = pthread_mutex_destroy(&mutex_);
	if (status != 0) {
		ostringstream os;
		os << "Knife(): error: can't destroy mutex, status = " << status;
		throw Exception( os.str() );
	}
}
// -------------------------------------------------------------------------
bool MessageQueue::empty()
{
	MessageQueue* queue_ = Instance();
	return queue_->messages_.empty();
}
// -------------------------------------------------------------------------
void MessageQueue::push( const std::string& text )
{
	Message msg(text);
	push(msg);
}
// -------------------------------------------------------------------------
void MessageQueue::push( Message& message )
{
	MessageQueue* queue_ = Instance();
	message.time_ = time(NULL);
	
	pthread_mutex_lock(&queue_->mutex_);
	queue_->messages_.push(message);
	pthread_mutex_unlock(&queue_->mutex_);
}
// -------------------------------------------------------------------------
Message MessageQueue::pop()
{
	MessageQueue* queue_ = Instance();
	
	pthread_mutex_lock(&queue_->mutex_);
	Message message = queue_->messages_.front();
	queue_->messages_.pop();
	pthread_mutex_unlock(&queue_->mutex_);
	
	return message;
}
// -------------------------------------------------------------------------
bool file_exist( const std::string& filename )
{
	std::ifstream file;
#ifdef HAVE_IOS_NOCREATE
	file.open( filename.c_str(), std::ios::in | std::ios::nocreate );
#else
	file.open( filename.c_str(), std::ios::in );
#endif
		bool result = false;
	if( file )
		result = true;
	file.close();
	return result;
}

}
// end of namespace
// -------------------------------------------------------------------------
