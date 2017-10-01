// --------------------------------------------------------------------------
#include "Knight.h"
#include <iostream>
#include <error.h>
// --------------------------------------------------------------------------
using namespace std;
using namespace knights;
// --------------------------------------------------------------------------
int main(int argc, char **argv)
{   
	try
	{
		Knight obj;
	}
	catch(std::exception& ex)
	{
		cerr << "(Knight): " << ex.what() << endl;
	}
	catch(...)
	{
		cerr << "(Knight): catch ..." << endl;
	}

	return 0;
}
