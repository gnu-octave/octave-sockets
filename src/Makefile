OCT = socket.oct
SRC := $(OCT:.oct=.cc)

MKOCTFILE ?= mkoctfile -Wall
OCTAVE ?= octave

## windows users should link with -lws2_32 (on mingw, at least). If you
## know how to detect windows and find the appropriate linker flag here,
## please drop a mail to the octave maintainers mailing list.

all: $(OCT)

%.oct: %.cc
	$(MKOCTFILE) $<

## We need to generate a PKG_ADD file for this to work. We could also
## get a string with the stuff in PKG_ADD and eval it before the test
## command, but it messes up the quotes.
check: $(OCT)
	grep PKG_ADD socket.cc | sed 's/\/\/ PKG_ADD: //' > PKG_ADD
	$(OCTAVE) -q --no-gui --eval "test socket.cc"
	rm PKG_ADD

clean:
	rm -f *.o octave-core core *.oct *~ PKG_ADD

.PHONY: all clean test

