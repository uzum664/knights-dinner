SUBDIRS=Dinner SimpleDinner PriorityDinner HungrySimpleDinner

noinst_LTLIBRARIES 		= libAlgorithms.la
libAlgorithms_la_SOURCES	=
libAlgorithms_la_LIBADD	= \
	Dinner/libDinner.la \
	SimpleDinner/libSimpleDinner.la \
	PriorityDinner/libPriorityDinner.la \
	HungrySimpleDinner/libHungrySimpleDinner.la

style: $(SUBDIRS)
	for d in $(SUBDIRS); do cd $$d; make style; cd -; done;
