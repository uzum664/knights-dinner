// -------------------------------------------------------------------------
#include "Configuration.h"
#include <fstream>
// -------------------------------------------------------------------------
using namespace std;
// -------------------------------------------------------------------------
namespace knights
{

Exception::Exception(std::string description) throw() : description_(description)
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
bool MessageQueue::empty()
{
	MessageQueue* queue_ = Instance();
	return queue_->messages_.empty();
}
// -------------------------------------------------------------------------
void MessageQueue::push( const Message& message )
{
	MessageQueue* queue_ = Instance();
	queue_->messages_.push(message);
}
// -------------------------------------------------------------------------
MessageQueue::Message MessageQueue::pop()
{
	MessageQueue* queue_ = Instance();
	Message message = queue_->messages_.front();
	queue_->messages_.pop();
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
