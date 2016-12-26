SUBDIRS := $(subst /,,$(wildcard */))
CLEAN_SUBDIRS := $(addprefix clean_,$(SUBDIRS))
GIT_SUBDIRS := $(addprefix git_,$(SUBDIRS))


all: $(SUBDIRS)

$(SUBDIRS): force
	$(MAKE) -C $@ all

clean: $(CLEAN_SUBDIRS)

$(CLEAN_SUBDIRS): force
	$(MAKE) -C $(patsubst clean_%,%,$@) clean

all_targets: force
	$(MAKE) -C !all_targets all_targets

gitignores: $(GIT_SUBDIRS)

$(GIT_SUBDIRS): force
	$(MAKE) -C $(patsubst git_%,%,$@) gitignores

.PHONY: all gitignores force all_targets clean $(SUBDIRS)
