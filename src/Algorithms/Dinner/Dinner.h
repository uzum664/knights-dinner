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
		Dinner( const Dinner& dinner );
		virtual ~Dinner(); // в деструкторе если счетчик dinner_counter_ обнуляется то удаляется окружение (стол, рыцари)
		virtual void step(){}; // шаг обеда
		virtual void start(); // начать обед ( просто выдаем разрешение рыцарем кушать и запускаем поток если не был запущен)
		virtual void stop(); // остановить обед ( отбираем разрешение )
		virtual bool addKnight( const std::string& name ); // добавить рыцаря и посадить за стол
		virtual bool addHungryKnight( const std::string& name ); // добавить рыцаря с уровнем голода и посадить за стол
		int getPlaceNum() { return place_num_; } // Получить количество мест за столом
		void waitThread();
		typedef std::list<Knight*> Knights;
		Knights getKnights() { return knights_; } // Получить список рыцарей
		virtual const std::string getName() { return "???Dinner"; }
		
	protected:
		void thread(); // поток обеда обеда
		friend void* dinner_thread( void* param );
		static Knights knights_; // список рыцарей
		
	private:
		bool running_; // флаг что уже запущен поток
		Table* table_; // стол
		int place_num_; // кол-во мест за столом
		pthread_t thread_;
		pthread_attr_t thread_attr_;
		static unsigned int dinner_counter_; // кол-во обедов (счетчик для удаления рыцарей когда будут удалены все экземпляры обедов)
};

}
#endif //_Dinner_H_