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
		typedef int Owner;
		Owner getOwner() const { return owner_; }; // Получить владельца
		bool isBusy() const { return owner_ != NULL; };
		bool take( const Owner& owner ); // занять место
		bool free(); // освободить место
		bool swapKnifes(); // поменять ножи местами на конкретном месте
		bool isKnifesDifferent() const; // проверить что ножи разные
		Table::Knifes::iterator getLeftKnife() const; // Получить итератор на левый нож
		Table::Knifes::iterator getRightKnife() const; // Получить итератор на правый нож
		bool isLeftKnifeTaken() const; // Проверить, что левый нож взят со стола
		bool isRightKnifeTaken() const; // Проверить, что правый нож взят со стола
		bool takeLeftKnife() const; // Взять левый нож со стола
		bool takeRightKnife() const; // Взять правый нож со стола
		bool putLeftKnife() const; // Положить левый нож на стол
		bool putRightKnife() const; // Положить правый нож на стол
		
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
		Owner owner_; // Хозяин места (место занято если не NULL)
		int num_; // номер места
};

}
#endif //_Place_H_