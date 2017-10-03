#ifndef _Place_H_
#define _Place_H_

#include <iostream>
#include "Table.h"

namespace knights
{

class Knife;

/*!
	Класс Место за столом - хранит данные о месте занимаемым рыцарем:
		- занято ли
		- какие ножи лежат справа и слева
*/

class Place
{
	public:
		virtual ~Place();
		bool isBusy() const { return busy_; };
		void take() { busy_ = true; };
		void free() { busy_ = false; };
		bool swapKnifes(); // поменять ножи местами на конкретном месте
		bool isKnifesDifferent() const; // проверить что ножи разные
		Table::Knifes::iterator getLeftKnife() const; // Получить итератор на левый нож
		Table::Knifes::iterator getRightKnife() const; // Получить итератор на правый нож
		
	protected:
		Place( Table* table ); // Место создается за столом
		Place(); // Здесь выбросится исключение
		friend std::ostream& operator<<(std::ostream& os, Place& place );
		friend std::ostream& operator<<(std::ostream& os, Place* place );
		
	private:
		friend class Table;
		Table* table_; // Стол которому принадлежит место
		Table::Knifes::iterator right_knife_; // Нож cправа
		Table::Knifes::iterator left_knife_; // Нож слева
		bool busy_; // место занято
		int num_; // номер места
};

}
#endif //_Place_H_