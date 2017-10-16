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
			static StatisticInterface* Instance( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml = Glib::RefPtr<Gnome::Glade::Xml>(), Dinner* const dinner = NULL );
			virtual ~StatisticInterface();
			
			int getPollTimeout() { return 200; } // период цикла обработки данных, мс
			
		protected:
			StatisticInterface( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml, Dinner* const dinner );
			StatisticInterface() {};
			void init();
			bool poll();
			
		private:
			static StatisticInterface* stats_interface_;
			Statistic* stats_;
			typedef std::map<Knight*, unsigned int> Knights;
			Knights knights_;

	};
}

#endif /* _StatisticInterface_H */
