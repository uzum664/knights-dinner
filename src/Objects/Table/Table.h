#ifndef _Table_H_
#define _Table_H_

#include <list>
#include <map>
#include <string>
#include <iostream>

namespace knights
{

class Knife;
class Place;

/*!
	Класс Стол - описывает структуру круглого стола,
	предоставляет интерфейс через который Рыцари могут взаимодействовать с окружением.
	За столом можно:
		- найти свободное место
		- имея указатель на место пользоваться ножами
*/

class Table
{
	public:
		static Table* Instance( const int& num );
		static Table* Instance();
		void Destroy();
		virtual ~Table();
		const std::string textDraw() const; // рисуем стол (размещение и ножи), пока в тексте
		typedef std::list<Knife*> Knifes;
		typedef std::list<Place*> Places;
		Knifes getKnifes() { return knifes_; } // Получить список ножей
		Places getPlaces() { return places_; } // Получить список мест
		bool take( const Knifes::iterator it ); // Взять нож со стола
		bool put( const Knifes::iterator it ); // Положить нож на стол
		bool swapKnifes( const Knifes::iterator left, const Knifes::iterator right ); // поменять ножи местами
		Place* findFreePlace() const; // Найти совбодное место за столом
		
		
	protected:
		Table( const int& num );
		Knifes::iterator addKnife( const std::string& type ); // добавить нож
		Knifes::iterator addOtherKnife( const Knifes::iterator it ); // добавить нож другого типа
		friend std::ostream& operator<<( std::ostream& os, Table& table );
		friend std::ostream& operator<<( std::ostream& os, Table* table );
		
	private:
		static Table* inst;
		Places places_; // места за столом
		Knifes knifes_; // ножи за столом
};

}
#endif //_Table_H_