SUBDIRS := $(subst /,,$(wildcard */))
CLEAN_SUBDIRS := $(addprefix clean_,$(SUBDIRS))
ALL_SUBDIRS := $(addprefix all_,$(SUBDIRS))
GIT_SUBDIRS := $(addprefix git_,$(SUBDIRS))

all: $(ALL_SUBDIRS)
all_targets: $(ALL_SUBDIRS)

clean: $(CLEAN_SUBDIRS)

$(CLEAN_SUBDIRS): force
	$(MAKE) -C $(patsubst clean_%,%,$@) clean

$(ALL_SUBDIRS): force
	$(MAKE) -C $(patsubst all_%,%,$@) all_targets

gitignores: $(GIT_SUBDIRS)

$(GIT_SUBDIRS): force
	$(MAKE) -C $(patsubst git_%,%,$@) gitignores

.PHONY: all gitignores force all_targets folder_all_targets clean $(SUBDIRS)
