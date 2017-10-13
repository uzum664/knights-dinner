SUBDIRS = widgets lib
bin_PROGRAMS = knights-gui

knights_gui_SOURCES = gui.cc

knights_gui_CXXFLAGS = \
	${GTKMM_CFLAGS} \
	${GLADEMM_CFLAGS} \
	-I$(top_builddir)/src/GUI/lib/ \
	-I$(top_builddir)/src/GUI/widgets/

knights_gui_LDADD = \
	${GTKMM_LIBS} \
	${GLADEMM_LIBS} \
	$(top_builddir)/lib/lib@PACKAGE@.la \
	$(top_builddir)/src/GUI/lib/libknightsGUI.la \
	$(top_builddir)/src/GUI/widgets/libknightswidgets.la

style:
	astyle $(ASTYLE_OPT) *.cc *.h
