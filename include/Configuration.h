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
			Exception(std::string description) throw();
			virtual ~Exception() throw() {};
			virtual const char* what() const throw();
		protected:
			Exception(){};
		private:
			std::string description_;
	};
	// -----------------------------------------------------------------------------
	class MessageQueue
	{
		public:
			static MessageQueue* Instance();
			virtual ~MessageQueue() {}
			
			typedef std::string Message;
			static bool empty();
			static void push( const Message& message );
			static Message pop();
			
		protected:
			MessageQueue() {};
			
		private:
			static MessageQueue* message_queue_;
			std::queue<std::string> messages_;
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
