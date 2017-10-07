// --------------------------------------------------------------------------
#include "SimpleDinner.h"
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
		SimpleDinner dinner;
		dinner.addKnight("Артур");
		dinner.addKnight("Ричард");
		dinner.addKnight("Ланселот");
		dinner.addKnight("Робин");
		dinner.addKnight("Гивеон");
		dinner.start();
		dinner.loop();
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
