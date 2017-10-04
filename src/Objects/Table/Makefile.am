noinst_LTLIBRARIES = libTable.la

libTable_la_CXXFLAGS	= \
	-I../Knife
libTable_la_LIBS	= \
	$(top_builddir)/lib/lib@PACKAGE@.la \
	../Knife/libKnife.la
libTable_la_SOURCES	= Place.cc Table.cc

noinst_PROGRAMS = table

table_CXXFLAGS	= \
	-I../Knife
table_LDADD	= \
	libTable.la \
	../Knife/libKnife.la \
	$(top_builddir)/lib/lib@PACKAGE@.la
table_SOURCES = table.cc

check:
	./table

style:
	astyle $(ASTYLE_OPT) *.cc *.h