// --------------------------------------------------------------------------
#include "Table.h"
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
		Table obj;
	}
	catch(std::exception& ex)
	{
		cerr << "(Table): " << ex.what() << endl;
	}
	catch(...)
	{
		cerr << "(Table): catch ..." << endl;
	}

	return 0;
}
