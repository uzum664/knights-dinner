noinst_LTLIBRARIES 		= libknightsGUI.la
libknightsGUI_la_CXXFLAGS	= \
	${GTKMM_CFLAGS} \
	${GLADEMM_CFLAGS}
libknightsGUI_la_LIBADD	= \
	${GTKMM_LIBS} \
	${GLADEMM_LIBS} \
	$(top_builddir)/lib/lib@PACKAGE@.la

libknightsGUI_la_SOURCES	= \
	MainWindow.cc

style:
	astyle $(ASTYLE_OPT) *.cc *.h
