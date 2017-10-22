#include <gtkmm.h>
#include <gladeui/glade.h>
#include <glibmm.h>
#include <plugins.h>
#include "RoundTable.h"
#include "Statistic.h"
#include "Journal.h"

using namespace knights;

extern "C" void knights_init()
{
	Gtk::Main::init_gtkmm_internals();
}
//----------------------------------------------------------------------------------
extern "C" void roundtable_init()
{
	Obj_Get_Type<RoundTable>();
}

extern "C" GType gtkmm___custom_object_roundtable_get_type()
{
	return Obj_Get_Type<RoundTable>();
}

extern "C" void roundtable_postcreate(GladeWidgetAdaptor* adaptor, GObject* object, GladeCreateReason reason)
{
	uwrap<RoundTable>(object);
}
//----------------------------------------------------------------------------------
extern "C" void statistic_init()
{
	Obj_Get_Type<Statistic>();
}

extern "C" GType gtkmm___custom_object_statistic_get_type()
{
	return Obj_Get_Type<Statistic>();
}

extern "C" void statistic_postcreate(GladeWidgetAdaptor* adaptor, GObject* object, GladeCreateReason reason)
{
	uwrap<Statistic>(object);
}
//----------------------------------------------------------------------------------
extern "C" void journal_init()
{
	Obj_Get_Type<Journal>();
}

extern "C" GType gtkmm___custom_object_journal_get_type()
{
	return Obj_Get_Type<Journal>();
}

extern "C" void journal_postcreate(GladeWidgetAdaptor* adaptor, GObject* object, GladeCreateReason reason)
{
	uwrap<Journal>(object);
}
//----------------------------------------------------------------------------------