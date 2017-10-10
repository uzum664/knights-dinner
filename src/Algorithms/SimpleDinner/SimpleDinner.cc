#include "SimpleDinner.h"
#include "Table/Table.h"
#include "Knight/Knight.h"
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
SimpleDinner::SimpleDinner( const int& num ) :
	place_num_(num)
{
	table = Table::Instance(5);
}
//---------------------------------------------------------------------------------------
SimpleDinner::~SimpleDinner()
{
	for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		if( *it )
			delete *it;
}
//---------------------------------------------------------------------------------------
void SimpleDinner::loop()
{
	// цикл обеда, пока просто всех ждем
	for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		Knight::lookFor( *it );
}
//---------------------------------------------------------------------------------------
void SimpleDinner::start()
{
	cout << table << endl;
	for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
	{
		(*it)->permit(true);
		(*it)->putOn(table->findFreePlace());
	}
}
//---------------------------------------------------------------------------------------
void SimpleDinner::stop()
{
	for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		(*it)->permit(false);
}
//---------------------------------------------------------------------------------------
bool SimpleDinner::addKnight( const std::string& name )
{
	if( knights.size() >= place_num_ )
		return false;
	Knight* knight = new Knight( name );
	knight->run();
	knights.push_back( knight );
	return true;
}
//---------------------------------------------------------------------------------------