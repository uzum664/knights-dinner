// --------------------------------------------------------------------------
#include "SimpleDinner.h"
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
		SimpleDinner sd;
	}
	catch(std::exception& ex)
	{
		cerr << "(SimpleDinner): " << ex.what() << endl;
	}
	catch(...)
	{
		cerr << "(SimpleDinner): catch ..." << endl;
	}

	return 0;
}
