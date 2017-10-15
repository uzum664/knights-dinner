#widget library
#AUTOMAKE_OPTIONS = subdir-objects

lib_LTLIBRARIES = libknightswidgets.la

libknightswidgets_la_SOURCES = \
	RoundTable.cc

libknightswidgets_la_LIBADD = \
	${RSVG_LIBS} \
	${GTKMM_LIBS} \
	${GLADE_LIBS} \
	$(top_builddir)/lib/lib@PACKAGE@.la

libknightswidgets_la_CXXFLAGS = \
	${RSVG_CFLAGS} \
	${GTKMM_CFLAGS} \
	${GLADE_CFLAGS}

#libglade plugin
libgladeplugin_LTLIBRARIES = libknights.la

libgladeplugindir = $(libdir)/libglade/2.0

libknights_la_SOURCES=function-knights.cc

libknights_la_LIBADD = \
	libknightswidgets.la \
	${GTKMM_LIBS} \
	${GLADE_LIBS}

libknights_la_LDFLAGS = -avoid-version

libknights_la_CPPFLAGS = \
	${GTKMM_CFLAGS} \
	${GLADE_CFLAGS}

##glade plugin
gladeplugin_LTLIBRARIES = libglade-knights.la
gladeplugindir = $(libdir)/glade3/modules

libglade_knights_la_SOURCES = glade-knights.cc

libglade_knights_la_LIBADD = \
	${GTKMM_LIBS} \
	${GLADEUI_LIBS} \
	${GLADE_LIBS} \
	libknightswidgets.la

libglade_knights_la_LDFLAGS = -avoid-version

libglade_knights_la_CPPFLAGS = \
	${GTKMM_CFLAGS} \
	${GLADEUI_CFLAGS} \
	${GLADE_CFLAGS}


catalogsdir = $(datadir)/glade3/catalogs
catalogs_DATA = knights.xml

#EXTRA_DIST = knights.xml

style:
	astyle $(ASTYLE_OPT) *.cc *.h
