#ifndef _PriorityDinner_H_
#define _PriorityDinner_H_

#include "Dinner.h"
#include "Knight/Knight.h"

namespace knights
{

/*!
	Алгоритм обеда: 
*/

class PriorityDinner :
	public Dinner
{
	public:
		PriorityDinner( const int& num = 5 );
		PriorityDinner( const Dinner& dinner );
		virtual ~PriorityDinner();
		virtual void step(); // шаг обеда
		virtual void start(); // начать обед
		
	protected:
		typedef std::list<Knight*> HungryKnights;
		HungryKnights hungryKnights; // список рыцарей отсортированный по голоду
		
	private:
		unsigned int max_permitions_;
};

class HungerQuery
{
	public:
		bool operator()( Knight*& left, Knight*& right) const { return left->getHunger() > right->getHunger(); } // Сначала идут более голодные рыцари
};


}
#endif //_PriorityDinner_H_