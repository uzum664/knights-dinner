noinst_LTLIBRARIES = libKnight.la

libKnight_la_CXXFLAGS	= \
	-I../Table
libKnight_la_LIBS	= \
	$(top_builddir)/lib/lib@PACKAGE@.la \
	../Table/libTable.la
libKnight_la_SOURCES	= KnightState.cc KnightWaitingState.cc KnightTransientState.cc KnightTalkState.cc KnightEatState.cc Knight.cc

noinst_PROGRAMS = knight

knight_CXXFLAGS	= \
	-I../Table
knight_LDADD	= \
	libKnight.la \
	$(top_builddir)/lib/lib@PACKAGE@.la \
	../Table/libTable.la \
	../Knife/libKnife.la
knight_SOURCES = knight.cc

all-local:
	./knight

style:
	astyle $(ASTYLE_OPT) *.cc *.h