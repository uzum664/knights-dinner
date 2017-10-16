#include <iostream>
#include "Statistic.h"
#include "Configuration.h"
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// -------------------------------------------------------------------------
#define INIT_ROUNDTABLE_PROPERTIES() \
	food_knife_image_path(*this, "food-knife-image-path", Glib::RefPtr<Gdk::Pixbuf>()) \
	,cutter_knife_image_path(*this, "cutter-knife-image-path", Glib::RefPtr<Gdk::Pixbuf>())
// -------------------------------------------------------------------------
void Statistic::constructor()
{
	cout << "Statistic::constructor()" << endl;
	columns_ = &stats_columns_;
}
// -------------------------------------------------------------------------
Statistic::Statistic() :
	Glib::ObjectBase("statistic")
	,INIT_ROUNDTABLE_PROPERTIES()
{
	constructor();
}
// -------------------------------------------------------------------------
Statistic::Statistic( TreeView::BaseObjectType* gobject ) :
	TreeView(gobject)
	,INIT_ROUNDTABLE_PROPERTIES()
{
	constructor();
}
// -------------------------------------------------------------------------
Statistic::~Statistic()
{
}
// -------------------------------------------------------------------------
void Statistic::init_treeview()
{
	if(tree_model_ref_)
		return;
	TreeView::init_treeview();

	{
		Gtk::CellRendererText* pRenderer = Gtk::manage( new Gtk::CellRendererText() );
		Gtk::TreeViewColumn* pColumn = add_column("Имя", pRenderer);
		pColumn->add_attribute(pRenderer->property_text(), COLUMN(name));
		pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_AUTOSIZE);
		pColumn->set_expand(true);
		pRenderer->property_xalign() = 0.5;
	}
	
	{
		Gtk::CellRendererText* pRenderer = Gtk::manage( new Gtk::CellRendererText() );
		Gtk::TreeViewColumn* pColumn = add_column("Состояние", pRenderer);
		pColumn->add_attribute(pRenderer->property_text(), COLUMN(state));
		pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
		pColumn->set_fixed_width(84);
		pRenderer->property_xalign() = 0.5;
	}
	
	{
		Gtk::CellRendererPixbuf* pRenderer = Gtk::manage( new Gtk::CellRendererPixbuf() );
		Gtk::TreeViewColumn* pColumn = add_column("Левый нож", pRenderer);
		pColumn->add_attribute(pRenderer->property_pixbuf(), COLUMN(left_knife));
		pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
		pColumn->set_fixed_width(32);
		pRenderer->property_xalign() = 0.5;
	}

	{
		Gtk::CellRendererPixbuf* pRenderer = Gtk::manage( new Gtk::CellRendererPixbuf() );
		Gtk::TreeViewColumn* pColumn = add_column("Правый нож", pRenderer);
		pColumn->add_attribute(pRenderer->property_pixbuf(), COLUMN(right_knife));
		pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
		pColumn->set_fixed_width(32);
		pRenderer->property_xalign() = 0.5;
	}

	{
		Gtk::CellRendererText* pRenderer = Gtk::manage( new Gtk::CellRendererText() );
		Gtk::TreeViewColumn* pColumn = add_column("Приемы пищи", pRenderer);
		pColumn->add_attribute(pRenderer->property_text(), COLUMN(meals));
		pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
		pColumn->set_fixed_width(84);
		pRenderer->property_xalign() = 0.5;
	}

	{
		Gtk::CellRendererText* pRenderer = Gtk::manage( new Gtk::CellRendererText() );
		Gtk::TreeViewColumn* pColumn = add_column("Истории", pRenderer);
		pColumn->add_attribute(pRenderer->property_text(), COLUMN(stories));
		pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
		pColumn->set_fixed_width(84);
		pRenderer->property_xalign() = 0.5;
	}
}
// -------------------------------------------------------------------------
void Statistic::updateRow( const unsigned int& number, const ColumnsPack& data )
{
	for( Gtk::TreeIter iter = tree_model_ref_->children().begin(); iter != tree_model_ref_->children().end(); ++iter )
	{
		Gtk::TreeRow row = *iter;
		if( number != row[COLUMN(number)] )
			continue;
		row[COLUMN(name)] = data.name;
		row[COLUMN(state)] = data.state;
		if( data.left_knife == FOOD_KNIFE )
			row[COLUMN(left_knife)] = get_food_knife_image_path();
		else if( data.left_knife == CUTTER_KNIFE )
			row[COLUMN(left_knife)] = get_cutter_knife_image_path();
		if( data.right_knife == FOOD_KNIFE )
			row[COLUMN(right_knife)] = get_food_knife_image_path();
		else if( data.right_knife == CUTTER_KNIFE )
			row[COLUMN(right_knife)] = get_cutter_knife_image_path();
		row[COLUMN(meals)] = data.meals;
		row[COLUMN(stories)] = data.stories;
	}
}
// -------------------------------------------------------------------------
