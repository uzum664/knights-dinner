#ifndef KnightState_H_
#define KnightState_H_
// ------------------------------------------------------------------------------------------
#include <string>
#include <iostream>
// ------------------------------------------------------------------------------------------
namespace knights
{

class Knight;

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
		void changeState( Knight* knight, KnightState* state );
		KnightState* getState( Knight* knight );
		Place* getPlace( Knight* knight ) const { return knight->place_; } // Место рыцаря
		bool hasPlace( Knight* knight ) const { return knight->place_ != NULL; } // Рыцарь занял место
		bool hasPermision( Knight* knight ) const { return knight->has_permition_; } // есть разрешение
		bool isHungry( Knight* knight ) const { return knight->hunger > 0; } // рыцарь голоден
		void tellStory( Knight* knight ) { knight->story_num_++; }// рыцарь рассказывает историю
		void eat( Knight* knight ) { knight->meal_num_++; knight->hunger--; }// рыцарь кушает

	private:
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
