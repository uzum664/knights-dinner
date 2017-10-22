#ifndef _Journal_H
#define _Journal_H
// -------------------------------------------------------------------------
#include "TreeView.h"

namespace knights
{
	#define COLUMN(name) dynamic_cast<JournalColumnRecord*>(columns_)->name
	/*! структура, описывающая строку в журнале(точнее колонки) */
	class JournalColumnRecord : public ColumnRecord
	{
	public:

		JournalColumnRecord()
		{
			add(time_string);
			add(text_message);
		}

		Gtk::TreeModelColumn<std::string> time_string;
		Gtk::TreeModelColumn<std::string> text_message;
	};

	class Journal : public TreeView
	{
		public:
			Journal();
			explicit Journal(TreeView::BaseObjectType* gobject);
			virtual ~Journal();
			
			void addRow( const std::string& text ); // добавить запись
			
		protected:
			virtual void init_treeview();

			JournalColumnRecord journal_columns_;		// описание строки в журнале

		private:
			void constructor();

			DISALLOW_COPY_AND_ASSIGN(Journal);
	};

}
#endif
