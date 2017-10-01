noinst_LTLIBRARIES = libKnight.la

libKnight_la_CXXFLAGS	=
libKnight_la_LIBS	= \
	$(top_builddir)/lib/lib@PACKAGE@.la
libKnight_la_SOURCES	= Knight.cc

noinst_PROGRAMS = knight

knight_CXXFLAGS	=
knight_LDADD	= $(top_builddir)/lib/lib@PACKAGE@.la \
	libKnight.la
knight_SOURCES = knight.cc

all-local:
	./knight

style:
	astyle $(ASTYLE_OPT) *.cc *.h