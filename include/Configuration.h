#ifndef Configuration_H_
#define Configuration_H_
// -------------------------------------------------------------------------
#include <exception>
#include <sstream>
#include <queue>
// -------------------------------------------------------------------------
// вспомогательный define для вывода логов..
#define PRELOG myname << "(" << __FUNCTION__ << "): "
#define PRELOG_PF myname << "(" << __PRETTY_FUNCTION__ << "): "
// -------------------------------------------------------------------------
namespace knights
{
	class Exception : public std::exception
	{
		public:
			Exception(const std::string& description) throw();
			virtual ~Exception() throw() {};
			virtual const char* what() const throw();
		protected:
			Exception(){};
		private:
			std::string description_;
	};
	class MessageQueue;
	// -----------------------------------------------------------------------------
	// Сообщение - хранит текст и метку времени
	class Message
	{
		public:
			Message(const std::string& message ) : message_(message) {}
			virtual ~Message() {}
			time_t getTime() { return time_; }
			std::string getMessage() { return message_; }
			
		protected:
			Message() {};
			
		private:
			friend class MessageQueue;
			std::string message_;
			time_t time_;
	};
	// -----------------------------------------------------------------------------
	class MessageQueue
	{
		public:
			static MessageQueue* Instance();
			virtual ~MessageQueue();
			
			//typedef std::string Message;
			static bool empty();
			static void push( const std::string& text );
			static void push( Message& message );
			static Message pop(); // получить первое сообщение из очереди (в очереди сообщение удаляется)
			
		protected:
			MessageQueue();
			
		private:
			static MessageQueue* message_queue_;
			std::queue<Message> messages_;
			pthread_mutex_t mutex_; // mutex доступа к очереди
	};
	// -----------------------------------------------------------------------------
	inline long sign( const long v )
	{
		if( v < 0 )
			return -1;

		if( v > 0 )
			return 1;

		return 0;
	}
	// -----------------------------------------------------------------------------
	bool file_exist( const std::string& filename );
	// -----------------------------------------------------------------------------
}
// -------------------------------------------------------------------------
#endif // Configuration_H_
