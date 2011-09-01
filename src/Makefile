OCT = sockets.oct
SRC := $(OCT:.oct=.cc)

#See which octave version we run by querying mkoctfile for its version
#string. (Is there a better way to do this? This looks horrible.) 
majorversion :=$(shell mkoctfile --version 2>&1 |sed -e 's/^.* \([0-9]*\)\.\([0-9]*\).\([0-9]*\)+\?$$/\1/g')
minorversion:=$(shell mkoctfile --version 2>&1 |sed -e 's/^.* \([0-9]*\)\.\([0-9]*\).\([0-9]*\)+\?$$/\2/g')
microversion:=$(shell mkoctfile --version 2>&1 |sed -e 's/^.* \([0-9]*\)\.\([0-9]*\).\([0-9]*\)+\?$$/\3/g')

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


