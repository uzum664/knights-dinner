// --------------------------------------------------------------------------
#include "Knife.h"
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
		Knife obj;
	}
	catch(std::exception& ex)
	{
		cerr << "(Knife): " << ex.what() << endl;
	}
	catch(...)
	{
		cerr << "(Knife): catch ..." << endl;
	}

	return 0;
}
