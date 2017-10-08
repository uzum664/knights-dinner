#ifndef _Knight_H_
#define _Knight_H_

#include <string>
#include <iostream>
#include <pthread.h>

namespace knights
{

class Place;
class KnightState;
void* knight_thread( void* param );

/*!
	Класс Рыцарь - самостоятельный поток, который выполняет разные задачи в зависимости от сотояния.
	Класс Рыцарь выполняет следующие задачи:
		- пока он голоден и есть разрешение, то будет пытаться взять ножи, что бы поесть
		- если не может взять 2 разных ножа, то будет рассказывать истории
*/

class Knight
{
	public:
		Knight( const std::string& name );
		virtual ~Knight();
		
		int getEatTimeout() { return 10000; } // время на поесть, мс
		int getTalkTimeout() { return 10000; } // время на рассказ, мс
		int getPollTimeout() { return 100; } // время цикла рыцаря, мс
		
		bool askSwapKnifes(); // Попросить рыцаря поменять ножи местами ( с проверкой что ножи у него действительно разные)
		void setSwapKnifes( bool swap ) { need_swap_knifes_ = swap; } // Выставить флаг для смены ножей местами
		bool needSwapKnifes() { return need_swap_knifes_; } // Рыцарю нужно поменять ножи
		void setWaitingDifferentKnifes( bool waiting ) { waiting_knifes_ = waiting; } // Выставить флаг ожидания ножей
		bool isWaitingDifferentKnifes() { return waiting_knifes_; } // Рыцарь ждет подходящих ножей
		bool isHungry() const { return hunger > 0; } // рыцарь голоден
		bool toldStory() const { return story_num_ > 0; } // рыцарь рассказал хотя бы 1 историю
		bool hasPlace() const { return place_ != NULL; } // Рыцарь занял место
		bool hasPermision() const { return has_permition_; } // есть разрешение
		void permit( bool permition ); // разрешить кушать
		bool putOn( Place* place ); // посадить рыцаря на место
		void run(); // Запускает поток рыцаря
		static void lookFor(Knight* knight); // Ожидание завершения потока
		
	protected:
		Knight(){}; // Безымянных рыцарей нету
		void changeState( KnightState* state ); // Смена состояния рыцаря
		void thread(); // Поток рыцаря в котором он может брать/ложить ножи, кушать, рассказывать
		friend void* knight_thread( void* param );
		friend std::ostream& operator<<(std::ostream& os, Knight& knight );
		friend std::ostream& operator<<(std::ostream& os, Knight* knight );
		friend class KnightState;
		
	private:
		bool running_; // флаг что уже запущен поток
		std::string name_; // Имя рыцаря
		KnightState* state_; // Состояние рыцаря
		bool has_right_knife_; // Нож cправа взят в руке
		bool has_lelt_knife_; // Нож слева взят в руке
		unsigned int meal_num_; // Количество приемов пищи
		unsigned int story_num_; // Количество рассказанных историй
		bool has_permition_; // есть разрешение начать обед
		int hunger; // голод рыцаря
		Place* place_; // Место за столом
		bool waiting_knifes_; // флаг ожидания ножей
		bool need_swap_knifes_; // флаг для смены ножей
		pthread_t thread_;
		pthread_attr_t thread_attr_;
};

}
#endif //_Knight_H_