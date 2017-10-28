#ifndef _HungrySimpleDinner_H_
#define _HungrySimpleDinner_H_

#include "Dinner.h"
#include "Knight/Knight.h"

namespace knights
{

/*!
	Алгоритм обеда: 
		как SimpleDinner только у соседей проверяем что они менее голодные.
*/

class HungrySimpleDinner :
	public Dinner
{
	public:
		HungrySimpleDinner( const int& num = 5 );
		HungrySimpleDinner( const Dinner& dinner );
		virtual ~HungrySimpleDinner();
		virtual void step(); // шаг обеда
		
	protected:
		
	private:
};


}
#endif //_HungrySimpleDinner_H_