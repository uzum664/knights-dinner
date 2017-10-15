SUBDIRS=Knife Table Knight

noinst_LTLIBRARIES 	= libObjects.la
libObjects_la_SOURCES	=
libObjects_la_LIBADD	= \
	Knife/libKnife.la \
	Knight/libKnight.la \
	Table/libTable.la

style: $(SUBDIRS)
	for d in $(SUBDIRS); do cd $$d; make style; cd -; done;
