#ifndef _TreeView_H
#define _TreeView_H
// -------------------------------------------------------------------------
#include <gtkmm.h>
#include <map>
#include "gtk_macros.h"

namespace knights
{

	#define COLUMN(name) dynamic_cast<ColumnRecord*>(columns_)->name
	// структура, описывающая строку в журнале(точнее колонки)
	class ColumnRecord : public Gtk::TreeModel::ColumnRecord
	{
	public:

		ColumnRecord()
		{
			add(number);
			add(time);
		}

		Gtk::TreeModelColumn<unsigned int> number;
		Gtk::TreeModelColumn<time_t> time;
	};

	class TreeView : public Gtk::ScrolledWindow
	{
		public:
			TreeView();
			explicit TreeView(Gtk::ScrolledWindow::BaseObjectType* gobject);
			virtual ~TreeView();
			
			template<class ColumnsPack> void updateRow( const unsigned int& number, const ColumnsPack& data ) {} // обновить запись
			unsigned int addRow(); // добавить запись
			
		protected:
			virtual void on_realize();
			virtual void init_treeview(); // инициализация treeview, вызывается в on_realize()
			Gtk::TreeViewColumn* add_column(const std::string& name, Gtk::CellRenderer* renderer); // Добавить колонку
			
			struct ColumnPos
			{
				int pos;
				Gtk::TreeViewColumn* column;
			};
			typedef std::map<std::string, ColumnPos> ColumnPosMap;
			ColumnPosMap columns_map;
			Glib::RefPtr<Gtk::ListStore> tree_model_ref_;	// модель списка для использования с виджетом Gtk::TreeView
			Gtk::TreeView tree_view_;			// виджет отображающий модель (Gtk::TreeModel) данных и позволяющий пользователю взаимодействовать с ними
			Gtk::TreeModel::ColumnRecord* columns_;		// указатель на описание строки в журнале
			ColumnRecord tree_model_columns_;		// описание строки в журнале

		private:
			void constructor();
			
			unsigned int row_number_;
			
			DISALLOW_COPY_AND_ASSIGN(TreeView);
	};

}
#endif
