#ifndef _Dinner_H_
#define _Dinner_H_

#include <list>
#include <string>

namespace knights
{

class Table;
class Knight;

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
		virtual void start(); // начать обед ( просто выдаем разрешение рыцарем кушать ) 
		virtual void stop(); // остановить обед ( отбираем разрешение )
		virtual bool addKnight( const std::string& name ); // добавить рыцаря и посадить за стол
		int getPlaceNum() { return place_num_; } // Получить количество мест за столом
		
	protected:
		void loop(); // цикл обеда
		typedef std::list<Knight*> Knights;
		Knights knights; // список рыцарей
		
	private:
		Table* table; // стол
		int place_num_; // кол-во мест за столом
};

}
#endif //_Dinner_H_