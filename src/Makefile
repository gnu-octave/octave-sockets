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

## for this to work, the PKG_ADD commands need to extracted from the source
check: $(OCT)
	$(OCTAVE) -q ./test_octave_sockets

clean:
	rm -f *.o octave-core core *.oct *~

.PHONY: all clean test

