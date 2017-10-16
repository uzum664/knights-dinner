#include <gtk/gtk.h>
#include <glade/glade-init.h>
#include <glade/glade-build.h>
#include <glibmm.h>
#include <plugins.h>
#include "RoundTable.h"
#include "Statistic.h"
#include "Journal.h"

using namespace knights;

template <class UType> static GtkWidget* glade_new(GladeXML* xml, GType widget_type, GladeWidgetInfo* info)
{
	UType* uw = manage(new UType);
	GtkWidget* w = GTK_WIDGET(uw->gobj());
	GObjectClass* oclass = G_OBJECT_GET_CLASS(w);

	for (unsigned int i = 0; i < info->n_properties; i++)
	{
		const gchar* name = info->properties[i].name;
		const gchar* value = info->properties[i].value;
		GParamSpec* pspec;

		pspec = g_object_class_find_property (oclass, name);

		if (pspec)
		{
			GValue gvalue = { 0 };

			if (glade_xml_set_value_from_string(xml, pspec, value, &gvalue))
			{
				g_object_set_property(G_OBJECT(w), name, &gvalue);
				g_value_unset(&gvalue);
			}
		}
	}

	return w;
}

extern "C" void glade_module_register_widgets()
{
	glade_register_widget(Obj_Get_Type<RoundTable>(), glade_new<RoundTable>, NULL, NULL);
	glade_register_widget(Obj_Get_Type<Statistic>(), glade_new<Statistic>, NULL, NULL);
	glade_register_widget(Obj_Get_Type<Journal>(), glade_new<Journal>, NULL, NULL);
}
