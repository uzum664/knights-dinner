// -------------------------------------------------------------------------
#include "Configuration.h"
// -------------------------------------------------------------------------
using namespace std;
// -------------------------------------------------------------------------
namespace knights
{
	Exception::Exception(std::string description) throw() : description_(description)
	{
	}
	
	const char* Exception::what() const throw()
	{
		return description_.c_str();
	}
}
// end of namespace
// -------------------------------------------------------------------------
