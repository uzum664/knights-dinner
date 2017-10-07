#ifndef _Knife_H_
#define _Knife_H_

#include <pthread.h>
#include <iostream>

namespace knights
{

/*!
	Класс Нож - собственно ресурс, который можно только взять и положить.
	Что бы не проверять каждый раз взят ли нож кем то, добавлено условие taken_cond_
		за которым рыцарь может следить пока разговаривает (KnightTalkState).)
*/

class Knife
{
	public:
		virtual ~Knife();
		bool take(); // Взять нож
		bool put(); // Положить нож
		bool isTaken(); // Проверить не занят ли нож
		bool lookFor( const int& ms ); // ожидаем что нож освободится в течение мс
		
	protected:
		Knife(); // Нож без типа не бывает
		friend std::ostream& operator<<(std::ostream& os, Knife& knife );
		friend std::ostream& operator<<(std::ostream& os, Knife* knife );
		std::string type_; // Описание типа ножа
		
	private:
		pthread_mutex_t taken_mutex_;
		pthread_cond_t taken_cond_;
		bool taken_; // Признак что нож занят
};

// нож для придержания еды
class FoodKnife :
	public Knife
{
	public:
		FoodKnife() { type_="food"; };
		virtual ~FoodKnife() {};
	protected:
		
	private:
};

// Нож для нарезки
class CutterKnife : 
	public Knife
{
	public:
		CutterKnife() { type_="cutter"; };
		virtual ~CutterKnife() {};
	protected:
		
	private:
};

}
#endif //_Knife_H_