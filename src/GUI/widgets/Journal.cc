#include <iostream>
#include "Journal.h"
#include "Configuration.h"
// -------------------------------------------------------------------------
using namespace std;
using namespace knights;
// -------------------------------------------------------------------------
#define INIT_ROUNDTABLE_PROPERTIES() \

// -------------------------------------------------------------------------
void Journal::constructor()
{
	cout << "Journal::constructor()" << endl;
	columns_ = &journal_columns_;
}
// -------------------------------------------------------------------------
Journal::Journal() :
	Glib::ObjectBase("journal")
	//,INIT_ROUNDTABLE_PROPERTIES()
{
	constructor();
}
// -------------------------------------------------------------------------
Journal::Journal( TreeView::BaseObjectType* gobject ) :
	TreeView(gobject)
	//,INIT_ROUNDTABLE_PROPERTIES()
{
	constructor();
}
// -------------------------------------------------------------------------
Journal::~Journal()
{
}
//-----------------------------------------------------------------------------------------------------
void Journal::init_treeview()
{
	if(tree_model_ref_)
		return;
	TreeView::init_treeview();
	
	{
		Gtk::CellRendererText* pRenderer = Gtk::manage( new Gtk::CellRendererText() );
		Gtk::TreeViewColumn* pColumn = add_column("Время", pRenderer);
		pColumn->add_attribute(pRenderer->property_text(), COLUMN(time_string));
		pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_FIXED);
		pColumn->set_fixed_width(140);
		pRenderer->property_xalign() = 0.5;
	}

	{
		Gtk::CellRendererText* pRenderer = Gtk::manage( new Gtk::CellRendererText() );
		Gtk::TreeViewColumn* pColumn = add_column("Сообщение", pRenderer);
		pColumn->add_attribute(pRenderer->property_text(), COLUMN(text_message));
		pColumn->set_sizing(Gtk::TREE_VIEW_COLUMN_AUTOSIZE);
		pColumn->set_expand(true);
		pRenderer->property_xalign() = 0.5;
	}
}
// -------------------------------------------------------------------------
void Journal::addRow( const std::string& text, const time_t& time )
{
	unsigned int number = TreeView::addRow();
	Gtk::TreeNodeChildren::reverse_iterator iter = tree_model_ref_->children().rbegin();
	Gtk::TreeRow row = *iter;
	// переводим время в строку
	gchar timestr[20];
	{
		struct tm tm;
		time_t sec = (time > 0) ? time : row[COLUMN(time)];
		localtime_r(&sec, &tm);
		strftime(timestr, 20, "%d.%m.%Y %H:%M:%S", &tm);
	}
	row[COLUMN(time_string)] = timestr;
	row[COLUMN(text_message)] = text;
}
// -------------------------------------------------------------------------
void Journal::addRow( Message& message )
{
	addRow( message.getMessage(), message.getTime() );
}
// -------------------------------------------------------------------------
