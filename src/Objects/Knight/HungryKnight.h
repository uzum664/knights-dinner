#ifndef _HungryKnight_H_
#define _HungryKnight_H_

#include "Knight.h"

namespace knights
{
/*!
	Класс Голодный Рыцарь - можно задать уровень голода
		- будет голодать когда рассказывает историю
*/

class HungryKnight :
	public Knight
{
	public:
		HungryKnight( const std::string& name, const int& hunger = 1, const double& power = 0.5 );
		virtual ~HungryKnight();
		
	protected:
		HungryKnight(){};
		
		virtual void tellStory(); // рыцарь рассказать историю
		virtual void eat(); // поесть
		
	private:
		double hunger_power_; // Отношение голодания рыцаря к насыщению за 1 итерацию KnightTalkState или KnightEatState 
		
};

}
#endif //_HungryKnight_H_