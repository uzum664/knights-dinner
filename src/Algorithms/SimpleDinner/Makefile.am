noinst_LTLIBRARIES = libSimpleDinner.la

libSimpleDinner_la_CXXFLAGS	= \
	-I$(top_builddir)/src/Algorithms/Dinner \
	-I$(top_builddir)/src/Objects \
	-I$(top_builddir)/src/Objects/Knife
libSimpleDinner_la_LIBS		= \
	$(top_builddir)/lib/lib@PACKAGE@.la \
	$(top_builddir)/src/Algorithms/Dinner/libDinner.la \
	$(top_builddir)/src/Objects/Table/libTable.la \
	$(top_builddir)/src/Objects/Knight/libKnight.la \
	$(top_builddir)/src/Objects/Knife/libKnife.la
libSimpleDinner_la_SOURCES	= SimpleDinner.cc

noinst_PROGRAMS = dinner

dinner_CXXFLAGS	= \
	-I$(top_builddir)/src/Algorithms/Dinner \
	-I$(top_builddir)/src/Objects \
	-I$(top_builddir)/src/Objects/Knife
dinner_LDADD	= \
	libSimpleDinner.la \
	$(top_builddir)/src/Algorithms/Dinner/libDinner.la \
	$(top_builddir)/src/Objects/Table/libTable.la \
	$(top_builddir)/src/Objects/Knight/libKnight.la \
	$(top_builddir)/src/Objects/Knife/libKnife.la \
	$(top_builddir)/lib/lib@PACKAGE@.la
dinner_SOURCES = simple_dinner.cc

style:
	astyle $(ASTYLE_OPT) *.cc *.h