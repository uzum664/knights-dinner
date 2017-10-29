#ifndef _StatisticInterface_H
#define _StatisticInterface_H

#include <libglademm.h>
#include "Statistic.h"
#include "Dinner.h"
#include <map>

namespace knights
{
	class StatisticInterface
	{
		public:;
			static StatisticInterface* Instance( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml = Glib::RefPtr<Gnome::Glade::Xml>() );
			virtual ~StatisticInterface();
			void reinit( Dinner* const dinner );
			
			int getPollTimeout() { return 200; } // период цикла обработки данных, мс
			
		protected:
			StatisticInterface( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml );
			StatisticInterface() {};
			bool poll();
			
		private:
			static StatisticInterface* stats_interface_;
			Statistic* stats_; // виджет таблица
			struct KnightInfo
			{
				KnightInfo(Knight* k) :
				knight(k)
				,row(0)
				{
				}
				Knight* knight; // рыцарь отображаемый в строке
				unsigned int row; // строка в таблице
			};
			typedef std::list<KnightInfo> Knights;
			Knights knights_;

	};
}

#endif /* _StatisticInterface_H */
