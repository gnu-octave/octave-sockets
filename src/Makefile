OCT := socket.oct
SRC := $(OCT:.oct=.cc)

MKOCTFILE ?= mkoctfile -Wall
OCTAVE ?= octave

$(info octave is $(OCTAVE))

EXTRALIBS := 
ifeq ($(OS),Windows_NT)
  EXTRALIBS := -lws2_32
endif

all: $(OCT)

%.oct: %.cc
	$(MKOCTFILE) $< $(EXTRALIBS)

## We need to generate a PKG_ADD file for this to work. We could also
## get a string with the stuff in PKG_ADD and eval it before the test
## command, but it messes up the quotes.
check: $(OCT)
	grep PKG_ADD $(SRC) | sed 's/\/\/ PKG_ADD: //' > PKG_ADD
	$(OCTAVE) -q --no-window-system --eval "test $(SRC)"
	rm PKG_ADD

clean:
	rm -f *.o octave-core core *.oct *~ PKG_ADD

.PHONY: all clean check

