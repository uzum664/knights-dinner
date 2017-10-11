#ifndef _SimpleDinner_H_
#define _SimpleDinner_H_

#include "Dinner.h"

namespace knights
{

/*!
	Алгоритм простого обеда: 
		на каждый шаг проверяем хватаетли рыцарю обоих ножей, если нет, то запрашиваем их у соседа, если у него есть оба ножа (сначала у предыдущего соседа, потом у следующего)
*/

class SimpleDinner :
	public Dinner
{
	public:
		SimpleDinner( const int& num = 5 );
		virtual ~SimpleDinner();
		virtual void step(); // шаг обеда
	protected:
		
	private:
};

}
#endif //_SimpleDinner_H_