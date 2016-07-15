SUBDIRS := $(wildcard */)

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ all

all_targets: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ all_targets


.PHONY: all all_targets $(SUBDIRS)