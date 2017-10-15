// --------------------------------------------------------------------------
#include "HungrySimpleDinner.h"
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
		HungrySimpleDinner dinner;
		dinner.addHungryKnight("   Артур");
		dinner.addHungryKnight("  Ричард");
		dinner.addHungryKnight("Ланселот");
		dinner.addHungryKnight("   Робин");
		dinner.addHungryKnight("  Гивеон");
		dinner.start();
		dinner.waitThread();
	}
	catch(std::exception& ex)
	{
		cerr << "(HungrySimpleDinner): " << ex.what() << endl;
	}
	catch(...)
	{
		cerr << "(HungrySimpleDinner): catch ..." << endl;
	}

	return 0;
}
