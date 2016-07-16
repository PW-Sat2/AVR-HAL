SUBDIRS := $(wildcard */)

all: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ all

all_targets: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ all_targets

clean: $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ clean

.PHONY: all all_targets clean $(SUBDIRS)