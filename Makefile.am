SUBDIRS=lib src

style: $(SUBDIRS)
	for d in $(SUBDIRS); do cd $$d; make style; cd -; done;