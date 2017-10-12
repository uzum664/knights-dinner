noinst_LTLIBRARIES = libHungrySimpleDinner.la

libHungrySimpleDinner_la_CXXFLAGS	= \
	-I$(top_builddir)/src/Algorithms/Dinner \
	-I$(top_builddir)/src/Objects \
	-I$(top_builddir)/src/Objects/Knife
libHungrySimpleDinner_la_LIBS		= \
	$(top_builddir)/lib/lib@PACKAGE@.la \
	$(top_builddir)/src/Algorithms/Dinner/libDinner.la \
	$(top_builddir)/src/Objects/Table/libTable.la \
	$(top_builddir)/src/Objects/Knight/libKnight.la \
	$(top_builddir)/src/Objects/Knife/libKnife.la
libHungrySimpleDinner_la_SOURCES	= HungrySimpleDinner.cc

noinst_PROGRAMS = dinner

dinner_CXXFLAGS	= \
	-I$(top_builddir)/src/Algorithms/Dinner \
	-I$(top_builddir)/src/Objects \
	-I$(top_builddir)/src/Objects/Knife
dinner_LDADD	= \
	libHungrySimpleDinner.la \
	$(top_builddir)/src/Algorithms/Dinner/libDinner.la \
	$(top_builddir)/src/Objects/Table/libTable.la \
	$(top_builddir)/src/Objects/Knight/libKnight.la \
	$(top_builddir)/src/Objects/Knife/libKnife.la \
	$(top_builddir)/lib/lib@PACKAGE@.la
dinner_SOURCES = hungry_dinner.cc

style:
	astyle $(ASTYLE_OPT) *.cc *.h