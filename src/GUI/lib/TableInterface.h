#ifndef _TableInterface_H
#define _TableInterface_H

#include <libglademm.h>
#include "RoundTable.h"
#include "Knife/Knife.h"
#include "Knight/Knight.h"

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
			void init();
			bool poll();
			
		private:
			static TableInterface* table_interface_;
			RoundTable* gui_table_;
			std::map<Knife*, RoundTable::ImageKey> knife_keys_; // массив для определения какой виджет соответствует ножу
			// так как рыцари места не меняют им массив соответствий не нужен
			//std::map<Knight*, RoundTable::ImageKey> knights_keys_; // массив для определения какой виджет соответствует рыцарю
	};
}

#endif /* _TableInterface_H */
