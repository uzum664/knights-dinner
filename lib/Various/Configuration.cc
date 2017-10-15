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
