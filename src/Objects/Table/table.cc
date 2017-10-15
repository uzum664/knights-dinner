// --------------------------------------------------------------------------
#include "Table.h"
#include "Place.h"
#include "Configuration.h"
#include <iostream>
#include <error.h>
// --------------------------------------------------------------------------
using namespace std;
using namespace knights;
const int PLACE_NUM = 5;
// --------------------------------------------------------------------------
int main(int argc, char **argv)
{   
	try
	{
		Table* table = Table::Instance(PLACE_NUM);
		Place* places[PLACE_NUM + 1];
		Place::Owner owner;
		for( int i = 0; i < (PLACE_NUM + 1); ++i )
		{
			places[i] = table->findFreePlace();
			if( places[i] )
				places[i]->take(owner);
		}
		for( int i = 0; i < PLACE_NUM; ++i )
		{
			if( !places[i] )
			{
				ostringstream os;
				os << "main(): error: found NULL place = " << i;
				throw Exception( os.str() );
			}
		}
		if( places[PLACE_NUM] )
			throw Exception( "main(): error: 6th place not NULL???" );
		
		Knife* first = *places[0]->getLeftKnife();
		
		cout << table << endl;
		for( int i = 0; i < PLACE_NUM; ++i )
		{
			Table::Knifes::iterator left = places[i]->getLeftKnife();
			Table::Knifes::iterator right = places[i]->getLeftKnife();
			// проверяем что ножа два
			if( !*left || !*right )
			{
				ostringstream os;
				os << "main(): error: knifes != 2";
				throw Exception( os.str() );
			}
			places[i]->swapKnifes();
			cout << table << endl;
		}
		
		Knife* chkfirst = *places[0]->getLeftKnife();
		
		if( chkfirst != first )
		{
			ostringstream os;
			os << "main(): error: chkfirst != first" ;
			throw Exception( os.str() );
		}
		
		return 0;
	}
	catch(Exception& ex)
	{
		cerr << "(Table): " << ex.what() << endl;
	}
	catch(std::exception& ex)
	{
		cerr << "(Table): " << ex.what() << endl;
	}
	catch(...)
	{
		cerr << "(Table): catch ..." << endl;
	}

	return 1;
}
