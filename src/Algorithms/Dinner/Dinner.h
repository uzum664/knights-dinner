#ifndef _Dinner_H_
#define _Dinner_H_

#include <list>
#include <string>
#include <pthread.h>

namespace knights
{

class Table;
class Knight;
void* dinner_thread( void* param );

/*!
	Алгоритм обеда: 
		- инициализирует стол
		- добавляет рыцарей за стол
		- выдает разрешения
		- в цикле обеда проверяется наелся ли каждый рыцарь, и рассказал ли он историю
*/

class Dinner
{
	public:
		Dinner( const int& num = 5 );
		virtual ~Dinner();
		virtual void step(){}; // шаг обеда
		virtual void start(); // начать обед ( просто выдаем разрешение рыцарем кушать и запускаем поток если не был запущен)
		virtual void stop(); // остановить обед ( отбираем разрешение )
		virtual bool addKnight( const std::string& name ); // добавить рыцаря и посадить за стол
		virtual bool addHungryKnight( const std::string& name ); // добавить рыцаря с уровнем голода и посадить за стол
		int getPlaceNum() { return place_num_; } // Получить количество мест за столом
		void waitThread();
		
	protected:
		void thread(); // поток обеда обеда
		friend void* dinner_thread( void* param );
		typedef std::list<Knight*> Knights;
		Knights knights; // список рыцарей
		
	private:
		bool running_; // флаг что уже запущен поток
		Table* table; // стол
		int place_num_; // кол-во мест за столом
		pthread_t thread_;
		pthread_attr_t thread_attr_;
};

}
#endif //_Dinner_H_