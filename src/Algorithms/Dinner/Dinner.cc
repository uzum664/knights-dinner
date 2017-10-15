#include "Dinner.h"
#include "Table/Table.h"
#include "Knight/HungryKnight.h"
#include "Configuration.h"
#include <unistd.h>
#include <sstream>
//---------------------------------------------------------------------------------------
using namespace std;
using namespace knights;
//---------------------------------------------------------------------------------------
Dinner::Dinner( const int& num ) :
	running_(false)
	,place_num_(num)
{
	table = Table::Instance(5);
}
//---------------------------------------------------------------------------------------
Dinner::~Dinner()
{
	stop();
	for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		if( *it )
			delete *it;
}
//---------------------------------------------------------------------------------------
void* knights::dinner_thread( void* param )
{
	Dinner* dinner = reinterpret_cast<Dinner*>(param);
	if( dinner )
		dinner->thread();
}
//---------------------------------------------------------------------------------------
void Dinner::waitThread()
{
	int status = pthread_join(thread_, NULL);
	if( status != 0 )
	{
		ostringstream os;
		os << "main(): error: can't join thread, status = " << status;
		throw Exception( os.str() );
	}
}
//---------------------------------------------------------------------------------------
void Dinner::start()
{
	if( running_ )
		return;
	
	cout << table << endl;
	for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
	{
		(*it)->permit(true);
		(*it)->putOn(table->findFreePlace());
	}
	
	pthread_attr_init(&thread_attr_);
	int status = pthread_create( &thread_, &thread_attr_, &knights::dinner_thread, this);
	if( status != 0 ) {
		ostringstream os;
		os << "run(): error: can't create thread, status = " << status;
		throw Exception( os.str() );
	}
	running_ = true;
}
//---------------------------------------------------------------------------------------
void Dinner::stop()
{
	for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		(*it)->permit(false);
	
	// прерываем поток
	if( running_ )
	{
		int status = pthread_cancel(thread_);
		if( status != 0 )
		{
			ostringstream os;
			os << "main(): error: can't cancel thread, status = " << status;
			throw Exception( os.str() );
		}
	}
}
//---------------------------------------------------------------------------------------
void Dinner::thread()
{
	int begin = time(NULL);
	int prev = begin;
	while( true )
	{
		step();
		bool anyoneHungry = false;
		bool someoneNotToldStory = false;
		
		for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
		{
			// проверяем что хоть кто то голоден
			if( (*it)->isHungry() )
				anyoneHungry = true;
			// проверяем что хоть кто то не расказывал историю
			if( !(*it)->toldStory() )
				someoneNotToldStory = true;
		}
		
		if( !anyoneHungry && !someoneNotToldStory )
			break;
		
		int now = time(NULL);
		
		if( ( prev + 3 ) <= now )
		{
			ostringstream os;
			for(Knights::iterator it = knights.begin() ; it != knights.end(); ++it )
				os << (*it)->textStatistic() << endl;
			cout << os.str();
			prev = now;
		}
		
		usleep(100000);
	}
	ostringstream os;
	os << "Dinner ends in " << ( time(NULL) - begin ) << " sec" << endl;
	cout << os.str();
	running_ = false;
}
//---------------------------------------------------------------------------------------
bool Dinner::addKnight( const std::string& name )
{
	if( knights.size() >= getPlaceNum() )
		return false;
	Knight* knight = new Knight( name );
	knight->run();
	knights.push_back( knight );
	return true;
}
//---------------------------------------------------------------------------------------
bool Dinner::addHungryKnight( const std::string& name )
{
	if( knights.size() >= getPlaceNum() )
		return false;
	Knight* knight = new HungryKnight( name, 10, 0.25 );
	knight->run();
	knights.push_back( knight );
	return true;
}
//---------------------------------------------------------------------------------------