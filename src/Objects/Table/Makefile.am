noinst_LTLIBRARIES = libTable.la

libTable_la_CXXFLAGS	=
libTable_la_LIBS	= \
	$(top_builddir)/lib/lib@PACKAGE@.la
libTable_la_SOURCES	= Table.cc

noinst_PROGRAMS = table

table_CXXFLAGS	=
table_LDADD	= $(top_builddir)/lib/lib@PACKAGE@.la \
	libTable.la
table_SOURCES = table.cc

all-local:
	./table

style:
	astyle $(ASTYLE_OPT) *.cc *.h