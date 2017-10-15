#ifndef _StatisticInterface_H
#define _StatisticInterface_H

#include <libglademm.h>
//#include "Statistic.h"

namespace knights
{
	class StatisticInterface
	{
		public:;
			static StatisticInterface* Instance( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml = Glib::RefPtr<Gnome::Glade::Xml>() );
			virtual ~StatisticInterface();
			
			int getPollTimeout() { return 200; } // период цикла обработки данных, мс
			
		protected:
			StatisticInterface( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml );
			StatisticInterface() {};
			bool poll();
			
		private:
			static StatisticInterface* stats_interface_;
			//Statistic* stats_;

	};
}

#endif /* _StatisticInterface_H */
