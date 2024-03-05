export (CC) = gcc
#TOPTARGETS := all
SUBDIRS := src
export PROROOT := ${CURDIR}

#$(TOPTARGETS): $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

all: build install

build: $(SUBDIRS)

install:
	@rm -r /opt/ProjectMustang
	@cp -r build/ /opt/ProjectMustang/

clean: $(SUBDIRS)
	@rm $(wildcard build/bin/*)

.PHONY: install build all clean $(TOPTARGETS) $(SUBDIRS)
