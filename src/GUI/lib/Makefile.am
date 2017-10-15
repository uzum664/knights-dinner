noinst_LTLIBRARIES 		= libknightsGUI.la
libknightsGUI_la_CXXFLAGS	= \
	${GTKMM_CFLAGS} \
	${GLADEMM_CFLAGS} \
	-I$(top_builddir)/src/GUI/widgets \
	-I$(top_builddir)/src/Algorithms/Dinner \
	-I$(top_builddir)/src/Algorithms \
	-I$(top_builddir)/src/Objects
libknightsGUI_la_LIBADD	= \
	${GTKMM_LIBS} \
	${GLADEMM_LIBS} \
	$(top_builddir)/lib/lib@PACKAGE@.la

libknightsGUI_la_SOURCES	= \
	MainWindow.cc \
	TableInterface.cc \
	JournalInterface.cc \
	StatisticInterface.cc

style:
	astyle $(ASTYLE_OPT) *.cc *.h
