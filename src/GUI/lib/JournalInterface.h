#ifndef _JournalInterface_H
#define _JournalInterface_H

#include <libglademm.h>
//#include "Journal.h"

namespace knights
{
	class JournalInterface
	{
		public:;
			static JournalInterface* Instance( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml = Glib::RefPtr<Gnome::Glade::Xml>() );
			virtual ~JournalInterface();
			
			int getPollTimeout() { return 200; } // период цикла обработки данных, мс
			
		protected:
			JournalInterface( const Glib::RefPtr<Gnome::Glade::Xml>& gladexml );
			JournalInterface() {};
			bool poll();
			
		private:
			static JournalInterface* journal_interface_;
			//Journal* journal_;

	};
}

#endif /* _JournalInterface_H */
