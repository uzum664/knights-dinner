#ifndef KnightState_H_
#define KnightState_H_
// ------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
// ------------------------------------------------------------------------------------------
namespace knights
{

class Knight;

/*!
	Класс Состояние Рыцаря - есть неколько сотояний:
		KnightWaitingState - Рыцарь находится в ожидании, выполняет следующие действия:
			- может поменять ножи местами если требуется
			- перейти в KnightTransientState, если голоден, сидит за столом и есть разрешение на обед
		KnightTransientState - переходный процесс, пока рыцарь решает что делать дальше, выполняет следующие действия:
			- запросить смену ножей, если видит что у него 2 одинаковых
			- перейти в состояние KnightTalkState
			- перейти в состояние KnightEatState
		KnightEatState - прием пищи
			- в конце трапезы может поменять ножи местами если требуется
			- в конце трапезы переходит в KnightTransientState
		KnightTalkState - рассказ истории
			- в конце рассказа переходит в KnightTransientState
*/

class KnightState
{
	public:
		static KnightState* Instance();
		void Destroy();
		virtual ~KnightState();

		virtual bool activate( Knight* knight );
		virtual bool deactivate( Knight* knight );
		virtual void step( Knight* knight ) {}

		virtual const std::string stateName()
		{
			return "???State";
		}
		virtual std::ostringstream& stateInfo( std::ostringstream& os )
		{
			return os;
		}

	protected:
		KnightState();
		KnightState* getState( Knight* knight );
		void changeState( Knight* knight, KnightState* state );
		bool hasPlace( Knight* knight ) const { return knight->place_ != NULL; } // Рыцарь занял место
		bool hasPermision( Knight* knight ) const { return knight->has_permition_; } // есть разрешение
		bool isHungry( Knight* knight ) const { return knight->hunger_ > 0; } // рыцарь голоден
		bool toldStory( Knight* knight ) const { return knight->story_num_ > 0; } // рыцарь рассказал хотя бы 1 историю
		void tellStory( Knight* knight ) { knight->tellStory(); } // рыцарь рассказывает историю
		void eat( Knight* knight ) { knight->eat(); } // рыцарь кушает
		void setWaitingDifferentKnifes( Knight* knight ) { knight->waiting_knifes_ = true; } // Выставить флаг ожидания ножей
		void resetWaitingDifferentKnifes( Knight* knight ) { knight->waiting_knifes_ = false; } // Сбросить флаг ожидания ножей
		bool isWaitingDifferentKnifes( Knight* knight ) { return knight->waiting_knifes_; } // Рыцарь ждет подходящих ножей
		bool needSwapKnifes( Knight* knight ) { return knight->need_swap_knifes_; } // Рыцарю нужно поменять ножи
		bool swapKnifes( Knight* knight ); // Пробуем поменять ножи
		bool takeKnifes( Knight* knight ); // Пробуем взять ножи
		bool putKnifes( Knight* knight ); // Положить ножи
		bool isKnifesDifferent( Knight* knight ); // Разные ножи?
		bool isKnifesAvailable( Knight* knight ); // Ножи не заняты?
		void setStateEndTime( Knight* knight, const time_t& time ) { knight->state_timeout_ = time; } // выставляем время окончания состояния
		bool isStateEndTime( Knight* knight, const time_t& time ) { return ( time >= knight->state_timeout_ ); } // проверяем время окончания состояния

	private:
		Place* getPlace( Knight* knight ) const { return knight->place_; } // место рыцаря
		static KnightState* inst_;
};
// ---------------------------------------------------------------------------
class KnightWaitingState:
	public KnightState
{
	public:
		static KnightWaitingState* Instance();
		void Destroy();
		virtual ~KnightWaitingState();

		virtual void step( Knight* knight );
		virtual const std::string stateName()
		{
			return "KnightWaitingState";
		}

	protected:
		KnightWaitingState();

	private:
		static KnightWaitingState* inst_;
};
// ---------------------------------------------------------------------------
class KnightTransientState:
	public KnightState
{
	public:
		static KnightTransientState* Instance();
		void Destroy();
		virtual ~KnightTransientState();

		virtual void step( Knight* knight );
		virtual const std::string stateName()
		{
			return "KnightTransientState";
		}

	protected:
		KnightTransientState();

	private:
		static KnightTransientState* inst_;
};
// ---------------------------------------------------------------------------
class KnightTalkState:
	public KnightState
{
	public:
		static KnightTalkState* Instance();
		void Destroy();
		virtual ~KnightTalkState();

		virtual bool activate( Knight* knight );
		virtual bool deactivate( Knight* knight );
		virtual void step( Knight* knight );
		virtual const std::string stateName()
		{
			return "KnightTalkState";
		}

	protected:
		KnightTalkState();

	private:
		static KnightTalkState* inst_;
};
// ---------------------------------------------------------------------------
class KnightEatState:
	public KnightState
{
	public:
		static KnightEatState* Instance();
		void Destroy();
		virtual ~KnightEatState();

		virtual bool activate( Knight* knight );
		virtual bool deactivate( Knight* knight );
		virtual void step( Knight* knight );
		virtual const std::string stateName()
		{
			return "KnightEatState";
		}

	protected:
		KnightEatState();

	private:
		static KnightEatState* inst_;
};

}
// ---------------------------------------------------------------------------
#endif // KnightState_H_
// ---------------------------------------------------------------------------
