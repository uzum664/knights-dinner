// --------------------------------------------------------------------------
#include "Knight.h"
#include "Table.h"
#include <iostream>
#include "Configuration.h"
// --------------------------------------------------------------------------
using namespace std;
using namespace knights;
// --------------------------------------------------------------------------
int main(int argc, char **argv)
{   
	try
	{
		Table* table = Table::Instance(2);
		Knight knight1("Артур");
		Knight knight2("Ричард");
		knight1.putOn(table->findFreePlace());
		knight2.putOn(table->findFreePlace());
		knight1.run();
		knight2.run();
		knight1.permit(true);
		knight2.permit(true);
		// Ждем пока наедятся
		Knight::lookFor(&knight1);
		Knight::lookFor(&knight2);
	}
	catch(Exception& ex)
	{
		cerr << "(Knight): " << ex.what() << endl;
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
