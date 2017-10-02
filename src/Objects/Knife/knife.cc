// --------------------------------------------------------------------------
#include "Knife.h"
#include "Configuration.h"
#include <iostream>
#include <error.h>
#include <pthread.h>
#include <unistd.h>
// --------------------------------------------------------------------------
using namespace std;
using namespace knights;
FoodKnife fknife;
CutterKnife cknife;
pthread_t fthread, cthread;
pthread_attr_t thread_attr;
#define FAILURE	reinterpret_cast<void*>(-11)
#define SUCCESS	reinterpret_cast<void*>(0)
//---------------------------------------------------------------------------------------
void* fknife_thread( void* param )
{
	// берем ножи сразу на 2 секунды
	if( !fknife.take() )
		return FAILURE;
	if( !cknife.take() )
		return FAILURE;
	cout << "fknife_thread " << ( fknife.isTaken()  ? "взял " : "положил ") << fknife << " нож" << endl; // 1 нож
	cout << "fknife_thread " << ( cknife.isTaken()  ? "взял " : "положил ") << cknife << " нож" << endl; // 2ой нож
	sleep(2);
	if( !fknife.put() )
		return FAILURE;
	if( !cknife.put() )
		return FAILURE;
	cout << "fknife_thread " << ( fknife.isTaken()  ? "взял " : "положил ") << fknife << " нож" << endl; // 1 нож
	cout << "fknife_thread " << ( cknife.isTaken()  ? "взял " : "положил ") << cknife << " нож" << endl; // 2ой нож
	return SUCCESS;
}
//---------------------------------------------------------------------------------------
void* cknife_thread( void* param )
{
	// берем ножи через 1 секунду
	sleep(1);
	if( fknife.take() )
		return FAILURE;
	if( cknife.take() )
		return FAILURE;
	cout << "cknife_thread не смог взять " << fknife << " нож" << endl; // 1 нож
	cout << "cknife_thread не смог взять " << cknife << " нож" << endl; // 2ой нож
	sleep(1);
	if( !fknife.take() )
		return FAILURE;
	if( !cknife.take() )
		return FAILURE;
	cout << "cknife_thread " << ( fknife.isTaken()  ? "взял " : "положил ") << fknife << " нож" << endl; // 1 нож
	cout << "cknife_thread " << ( cknife.isTaken()  ? "взял " : "положил ") << cknife << " нож" << endl; // 2ой нож
	return SUCCESS;
}
// --------------------------------------------------------------------------
int main(int argc, char **argv)
{   
	try
	{
		pthread_attr_init(&thread_attr);
		// запускаем поток1
		{
			int status = pthread_create(&fthread, &thread_attr, &fknife_thread, NULL);
			if (status != 0)
			{
				ostringstream os;
				os << "main(): error: can't create fknife_thread, status = " << status;
				throw Exception( os.str() );
			}
		}
		// запускаем поток2
		{
			int status = pthread_create(&cthread, &thread_attr, &cknife_thread, NULL);
			if (status != 0)
			{
				ostringstream os;
				os << "main(): error: can't create cknife_thread, status = " << status;
				throw Exception( os.str() );
			}
		}
		// ожидаем поток1
		{
			int result;
			int status = pthread_join(fthread, reinterpret_cast<void**>(&result));
			if (status != 0 )
			{
				ostringstream os;
				os << "main(): error: can't join fknife_thread, status = " << status;
				throw Exception( os.str() );
			}
			if ( reinterpret_cast<void*>(result) != SUCCESS )
			{
				ostringstream os;
				os << "main(): error: returned from fknife_thread = " << result;
				throw Exception( os.str() );
			}
		}
		// ожидаем поток2
		{
			int result;
			int status = pthread_join(cthread, reinterpret_cast<void**>(&result));
			if (status != 0 )
			{
				ostringstream os;
				os << "main(): error: can't join cknife_thread, status = " << status;
				throw Exception( os.str() );
			}
			if ( reinterpret_cast<void*>(result) != SUCCESS )
			{
				ostringstream os;
				os << "main(): error: returned from cknife_thread = " << result;
				throw Exception( os.str() );
			}
		}
		return 0;
	}
	catch(Exception& ex)
	{
		cerr << "(Knife): " << ex.what() << endl;
	}
	catch(std::exception& ex)
	{
		cerr << "(Knife): " << ex.what() << endl;
	}
	catch(...)
	{
		cerr << "(Knife): catch ..." << endl;
	}

	return 1;
}
