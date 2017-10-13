#ifndef _RoundTable_H
#define _RoundTable_H
// -------------------------------------------------------------------------
#include <gtkmm.h>
#include "gtk_macros.h"

namespace knights
{

	class RoundTable : public Gtk::Fixed
	{
		public:
			RoundTable();
			explicit RoundTable(Gtk::Fixed::BaseObjectType* gobject);
			virtual ~RoundTable();
			
		protected:
			virtual void on_add(Gtk::Widget* w);

		private:
			void constructor();

			DISALLOW_COPY_AND_ASSIGN(RoundTable);
	};

}
#endif
