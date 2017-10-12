#ifndef _PriorityDinner_H_
#define _PriorityDinner_H_

#include "Dinner.h"

namespace knights
{

/*!
	Алгоритм простого обеда: 
		на каждый шаг проверяем хватаетли рыцарю обоих ножей, если нет, то запрашиваем их у соседа, если у него есть оба ножа (сначала у предыдущего соседа, потом у следующего)
*/

class PriorityDinner :
	public Dinner
{
	public:
		PriorityDinner( const int& num = 5 );
		virtual ~PriorityDinner();
		virtual void step(); // шаг обеда
		virtual bool addKnight( const std::string& name ); // добавить рыцаря и посадить за стол
		
	protected:
		
	private:
};

}
#endif //_PriorityDinner_H_