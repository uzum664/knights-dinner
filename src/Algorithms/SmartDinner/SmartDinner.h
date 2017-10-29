#ifndef _SmartDinner_H_
#define _SmartDinner_H_

#include "Dinner.h"
#include "Knight/Knight.h"

namespace knights
{

/*!
	Алгоритм обеда:
		выдает строго max_permitions_ разрешений (следит что бы не выдавалось соседям и рыцарям с одинаковыми ножами)
		формируем очередь HungerQuery, по которой выдаем 1ое разрешение
		остальные разрешения выдается отталкиваясь от 1ого
*/

class SmartDinner :
	public Dinner
{
	public:
		SmartDinner( const int& num = 5 );
		SmartDinner( const Dinner& dinner );
		virtual ~SmartDinner();
		virtual void step(); // шаг обеда
		virtual void start(); // начать обед
		virtual const std::string getName() { return "SmartDinner"; }
		
		class HungerQuery
		{
			public:
				bool operator()( Knight*& left, Knight*& right) const { return left->getHunger() > right->getHunger(); } // Сначала идут более голодные рыцари
		};
		
	protected:
		typedef std::list<Knight*> HungryKnights;
		HungryKnights hungryKnights; // список рыцарей отсортированный по голоду
		
	private:
		unsigned int max_permitions_;
};

}
#endif //_SmartDinner_H_