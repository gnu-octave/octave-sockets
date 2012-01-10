OCT = sockets.oct
SRC := $(OCT:.oct=.cc)

#See which octave version we run by querying mkoctfile for its version
#string. (Is there a better way to do this? This looks horrible.) 
majorversion := $(shell  mkoctfile --version 2>&1  | sed  -e 's/[ .+]/\n/g' |sed  -n '3p')
minorversion := $(shell  mkoctfile --version 2>&1  | sed  -e 's/[ .+]/\n/g' |sed  -n '4p')
microversion := $(shell  mkoctfile --version 2>&1  | sed  -e 's/[ .+]/\n/g' |sed  -n '5p')

VFLAGS=-DMAJORVERSION=$(majorversion) 
VFLAGS+=-DMINORVERSION=$(minorversion)
VFLAGS+=-DMICROVERSION=$(microversion)

all: $(OCT)

%.oct: %.cc
	mkoctfile $(VFLAGS) -s $<

test: $(OCT)
	test_octave_sockets

clean:
	rm -f *.oct *.o

.PHONY: all clean test


