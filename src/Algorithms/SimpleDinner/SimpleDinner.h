#ifndef _SimpleDinner_H_
#define _SimpleDinner_H_

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
*/

class SimpleDinner
{
	public:
		SimpleDinner( const int& num = 5 );
		virtual ~SimpleDinner();
		void loop(); // цикл обеда
		void start(); // начать обед ( просто выдаем разрешение рыцарем кушать ) 
		void stop(); // остановить обед ( отбираем разрешение )
		bool addKnight( const std::string& name ); // добавить рыцаря и посадить за стол
	protected:
		
	private:
		Table* table; // стол
		int place_num_; // кол-во мест за столом
		typedef std::list<Knight*> Knights;
		Knights knights; // список рыцарей
};

}
#endif //_SimpleDinner_H_