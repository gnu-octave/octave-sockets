OCT = sockets.oct
SRC := $(OCT:.oct=.cc)

all make: $(OCT)

%.oct: %.cc
	mkoctfile -s $<

test: $(OCT)
	test_octave_sockets

clean:
	rm -f *.oct *.o

.PHONY: make clean test


