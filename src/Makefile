OCT = sockets.oct
SRC := $(OCT:.oct=.cc)

#Allow mkoctfile to be set externally.
MKOCTFILE ?= mkoctfile
OCTAVE ?= octave

#See which octave version we run by querying mkoctfile for its version
#string. This is needed because there was an octave macro that changed
#from 3.0 to 3.2. When 3.0 is considered long gone, this is not
#needed anymore.
#The best thing would be to do this check inside the .cc file, but I
#believe there are no version macros other than VERSION from
#octave/config.h, which is a string and difficult to deal with. The octave
#developers discourage from relying on versions, so this is not likely
#to be supported. 
majorversion := $(word 3,$(shell $(MKOCTFILE) --version 2>&1 | sed 's/\./ /g'))
minorversion := $(word 4,$(shell $(MKOCTFILE) --version 2>&1 | sed 's/\./ /g'))
microversion := $(word 5,$(shell $(MKOCTFILE) --version 2>&1 | sed 's/\./ /g')) 

VFLAGS=-DMAJORVERSION=$(majorversion) 
VFLAGS+=-DMINORVERSION=$(minorversion)
VFLAGS+=-DMICROVERSION=$(microversion)

all: $(OCT)

%.oct: %.cc
	$(MKOCTFILE) $(VFLAGS) -s $<

test: $(OCT)
	$(OCTAVE) -q ./test_octave_sockets

clean:
	rm -f *.oct *.o

.PHONY: all clean test


