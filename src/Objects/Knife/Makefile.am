noinst_LTLIBRARIES = libKnife.la

libKnife_la_CXXFLAGS	=
libKnife_la_LIBS	= \
	$(top_builddir)/lib/lib@PACKAGE@.la
libKnife_la_SOURCES	= Knife.cc

noinst_PROGRAMS = knife

knife_CXXFLAGS	=
knife_LDADD	= $(top_builddir)/lib/lib@PACKAGE@.la \
	libKnife.la
knife_SOURCES = knife.cc

all-local:
	./knife

style:
	astyle $(ASTYLE_OPT) *.cc *.h