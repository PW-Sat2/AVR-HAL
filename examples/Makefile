SUBDIRS := $(subst /,,$(wildcard */))
CLEAN_SUBDIRS := $(addprefix clean_,$(SUBDIRS))
ALL_SUBDIRS := $(addprefix all_,$(SUBDIRS))


all: $(SUBDIRS)

$(SUBDIRS): force
	$(MAKE) -C $@ all

clean: $(CLEAN_SUBDIRS)

$(CLEAN_SUBDIRS): force
	$(MAKE) -C $(patsubst clean_%,%,$@) clean

all_targets: $(ALL_SUBDIRS)

$(ALL_SUBDIRS): force
	$(MAKE) -C $(patsubst all_%,%,$@) all_targets 

.PHONY: all force all_targets clean $(SUBDIRS)
