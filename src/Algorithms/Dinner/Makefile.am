noinst_LTLIBRARIES = libDinner.la

libDinner_la_CXXFLAGS	= \
	-I$(top_builddir)/src/Objects \
	-I$(top_builddir)/src/Objects/Knife
libDinner_la_LIBS		= \
	$(top_builddir)/lib/lib@PACKAGE@.la \
	$(top_builddir)/src/Objects/Table/libTable.la \
	$(top_builddir)/src/Objects/Knight/libKnight.la \
	$(top_builddir)/src/Objects/Knife/libKnife.la
libDinner_la_SOURCES	= Dinner.cc

style:
	astyle $(ASTYLE_OPT) *.cc *.h