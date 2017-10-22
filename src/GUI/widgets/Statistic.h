#ifndef _Statistic_H
#define _Statistic_H
// -------------------------------------------------------------------------
#include "TreeView.h"

namespace knights
{
	#define COLUMN(name) dynamic_cast<StatsColumnRecord*>(columns_)->name
	// структура, описывающая строку в журнале(точнее колонки)
	class StatsColumnRecord : public ColumnRecord
	{
	public:

		StatsColumnRecord()
		{
			add(name);
			add(state);
			add(left_knife);
			add(right_knife);
			add(meals);
			add(stories);
		}

		Gtk::TreeModelColumn<std::string> name;
		Gtk::TreeModelColumn<std::string> state;
		Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > left_knife;
		Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > right_knife;
		Gtk::TreeModelColumn<unsigned int> meals;
		Gtk::TreeModelColumn<unsigned int> stories;
	};

	class Statistic : public TreeView
	{
		public:
			Statistic();
			explicit Statistic(TreeView::BaseObjectType* gobject);
			virtual ~Statistic();
			
			enum ImageType
			{
				FOOD_KNIFE,
				CUTTER_KNIFE
			};
	
			struct ColumnsPack
			{
				std::string name;
				std::string state;
				ImageType left_knife;
				ImageType right_knife;
				unsigned int meals;
				unsigned int stories;
			};
			
			void updateRow( const unsigned int& number, const ColumnsPack& data ); // обновить запись
			
		protected:
			virtual void init_treeview();
			
			StatsColumnRecord stats_columns_;		// описание строки в журнале

		private:
			void constructor();
			
			ADD_PROPERTY( food_knife_image_path, Glib::RefPtr<Gdk::Pixbuf> )
			ADD_PROPERTY( cutter_knife_image_path, Glib::RefPtr<Gdk::Pixbuf> )

			DISALLOW_COPY_AND_ASSIGN(Statistic);
	};

}
#endif
