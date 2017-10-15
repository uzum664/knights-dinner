#ifndef _TableInterface_H
#define _TableInterface_H

#include <libglademm.h>
#include "RoundTable.h"

namespace knights
{
	class TableInterface
	{
		public:;
			static TableInterface* Instance( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml = Glib::RefPtr<Gnome::Glade::Xml>() );
			virtual ~TableInterface();
			
			int getPollTimeout() { return 200; } // период цикла обработки данных, мс
			
		protected:
			TableInterface( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml );
			TableInterface() {};
			bool poll();
			
		private:
			static TableInterface* table_interface_;
			RoundTable* gui_table_;

	};
}

#endif /* _TableInterface_H */
