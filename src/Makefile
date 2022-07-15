# Makefile for the octave sockets package.
# The intent is to keep this makefile working for
# * Octave>=3.2
# * Windows
# straight out of the box.

OCT := socket.oct
SRC := $(OCT:.oct=.cc)

MKOCTFILE ?= mkoctfile -Wall
OCTAVE_CONFIG ?= octave-config
OCTAVE ?= octave
GREP ?= grep

CANONICAL_HOST_TYPE := $(shell $(OCTAVE_CONFIG) -p CANONICAL_HOST_TYPE))

ARCHDIR   := "$(shell $(OCTAVE_CONFIG) -p CANONICAL_HOST_TYPE)-$(shell $(OCTAVE_CONFIG) -p API_VERSION)"
CC_SOURCES  := $(wildcard *.cc)
CC_TST_SOURCES := $(shell $(GREP) --files-with-matches '^%!' $(CC_SOURCES))
TST_SOURCES := $(patsubst %.cc,../inst/$(ARCHDIR)/%.cc-tst,$(CC_TST_SOURCES))

#The following is necessary to get the sockets package working in Windows.
#It has been tried on Win7 and XP, in Octave 3.8.0 using mxe-octave (mingw)
EXTRALIBS := 
ifneq (,$(findstring mingw,$(CANONICAL_HOST_TYPE)))
  EXTRALIBS := -lws2_32
endif

all: $(OCT) archtests

%.oct: %.cc
	$(MKOCTFILE) $< $(EXTRALIBS)

$(TST_SOURCES): ../inst/$(ARCHDIR)/%.cc-tst: %.cc | ../inst/$(ARCHDIR)
	@echo "Extracting tests from $< ..."
	@$(RM) -f "$@" "$@-t"
	@(      echo "## Generated from $<"; \
		$(GREP) '^%!' "$<") > "$@"

PHONY: archtests
archtests: $(TST_SOURCES)

PHONY: cleanarchtests
cleanarchtests:
	rm -f $(TST_SOURCES)

../inst/$(ARCHDIR):
	@mkdir -p "$@"

# We need to generate a PKG_ADD file for this to work. We could also
# get a string with the stuff in PKG_ADD and eval it before the test
# command, but it messes up the quotes.
check: $(OCT)
	$(GREP) PKG_ADD $(SRC) | sed 's/\/\/ PKG_ADD: //' > PKG_ADD
	$(OCTAVE) -q --no-window-system --eval "test $(SRC)"
	rm PKG_ADD

clean: cleanarchtests
	-rm -f *.o octave-core octave-workspace core *.oct *~ PKG_ADD

#This creates a package for distribution. It requires the checked out hg
#repo to be named sockets, or that a symlink of name sockets point to the
#checked out repo.
pkgversion:=$(word 2,$(shell grep ^Version ../DESCRIPTION|head -n1))
pkg:
	cd ../.. && tar cvfzh sockets-${pkgversion}.tar.gz --exclude=.hg sockets/

.PHONY: all clean check pkg
