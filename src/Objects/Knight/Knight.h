#ifndef _Knight_H_
#define _Knight_H_

#include <string>
#include <iostream>
#include <pthread.h>

// макрос для логов и сообщений рыцаря
#define MESSAGE(who, text) \
{ \
	ostringstream os; \
	os << who->name_ << text << endl; \
	cout << os.str(); \
	MessageQueue::push(os.str()); \
}

namespace knights
{

class Place;
class KnightState;
class StatisticInterface;
void* knight_thread( void* param );

/*!
	Класс Рыцарь - самостоятельный поток, который выполняет разные задачи в зависимости от сотояния.
	Класс Рыцарь выполняет следующие задачи:
		- пока он голоден и есть разрешение, то будет пытаться взть ножи, что бы поесть
		- если нет свободных ножей, то будет рассказывать историю
		- если взял оба ножа то может их поменять местами
	Так как к рыцарю может быть осуществлен доступ из основного потока после вызова run() то в mutex_ обернуты:
		- основной цикл рыцаря thread
		- public методы
	В классах KnightState нельзя использовать public методы Knight, так как Knight должен гарантировать что при вызовах в KnightState mutex_ уже залочен.
	В классах KnightState можно использовать методы базового KnightState
*/

class Knight
{
	public:
		Knight( const std::string& name );
		virtual ~Knight();
		
		int getPollTimeout() { return 100; } // время цикла рыцаря, мс
		
		enum State
		{
			WAITING,
			EAT,
			TALK,
			TRANSIENT
		};
		State getState(); // Состояние рыцаря
		std::string textStatistic(); // Статистика рыцаря
		bool askSwapKnifes(); // Попросить рыцаря поменять ножи местами ( с проверкой что ножи у него действительно разные)
		bool isWaitingDifferentKnifes(); // Рыцарь ждет подходящих ножей
		bool hasDifferentKnifes(); // У рыцаря есть подходящие ножи
		bool hasPermision(); // есть разрешение
		bool hasLeftKnife(); // Рыцарь взял левый нож
		bool hasRightKnife(); // Рыцарь взял правый нож
		int getHunger(); // Уровень голода рыцаря
		bool isHungry(); // рыцарь голоден
		bool toldStory(); // рыцарь рассказал хотя бы 1 историю
		void permit( bool permition ); // разрешить кушать
		bool putOn( Place* place ); // посадить рыцаря на место
		void run(); // Запускает поток рыцаря
		static void lookFor(Knight* knight); // Ожидание завершения потока
		
	protected:
		Knight(){}; // Безымянных рыцарей нету
		
		virtual void tellStory() { story_num_++; } // рыцарь рассказать историю
		virtual void eat() { meal_num_++; hunger_--; } // поесть
		void changeState( KnightState* state ); // Смена состояния рыцаря
		void thread(); // Поток рыцаря в котором он может брать/ложить ножи, кушать, рассказывать
		friend void* knight_thread( void* param );
		
		friend std::ostream& operator<<(std::ostream& os, Knight& knight );
		friend std::ostream& operator<<(std::ostream& os, Knight* knight );
		friend class KnightState;
		friend class KnightEatState;
		friend class KnightTalkState;
		friend class KnightWaitingState;
		friend class KnightTransientState;
		friend class StatisticInterface;
		
		int hunger_; // голод рыцаря
		
	private:
		bool running_; // флаг что уже запущен поток
		std::string name_; // Имя рыцаря
		KnightState* state_; // Состояние рыцаря
		bool has_right_knife_; // Нож cправа взят в руке
		bool has_left_knife_; // Нож слева взят в руке
		unsigned int meal_num_; // Количество приемов пищи
		unsigned int story_num_; // Количество рассказанных историй
		bool has_permition_; // есть разрешение начать обед
		Place* place_; // Место за столом
		bool waiting_knifes_; // флаг ожидания ножей
		bool need_swap_knifes_; // флаг для смены ножей
		bool swapped_knifes_; // флаг что уже менял ножи
		time_t state_timeout_; // время окончания состояния (для Eat и Talk)
		pthread_mutex_t mutex_; // mutex доступа к рыцарю
		pthread_t thread_;
		pthread_attr_t thread_attr_;
};

}
#endif //_Knight_H_