// --------------------------------------------------------------------------
#include "PriorityDinner.h"
#include <iostream>
#include <error.h>
#include "Knight/Knight.h"
// --------------------------------------------------------------------------
using namespace std;
using namespace knights;
// --------------------------------------------------------------------------
int main(int argc, char **argv)
{   
	try
	{
		PriorityDinner dinner;
		dinner.addKnight("Артур");
		dinner.addKnight("Ричард");
		dinner.addKnight("Ланселот");
		dinner.addKnight("Робин");
		dinner.addKnight("Гивеон");
		dinner.start();
	}
	catch(std::exception& ex)
	{
		cerr << "(PriorityDinner): " << ex.what() << endl;
	}
	catch(...)
	{
		cerr << "(PriorityDinner): catch ..." << endl;
	}

	return 0;
}
