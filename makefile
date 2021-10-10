export (CC) = clang
#TOPTARGETS := all
SUBDIRS := src
export PROROOT := ${CURDIR}

#$(TOPTARGETS): $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

all: $(SUBRIRS)

install:
	@rm -r /opt/ProjectMustang
	@cp -r build/ /opt/ProjectMustang/

clean: $(SUBDIRS)
	@rm $(wildcard build/bin/*)

.PHONY: install all clean $(TOPTARGETS) $(SUBDIRS)
