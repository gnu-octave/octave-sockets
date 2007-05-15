OCT = sockets.oct
SRC := $(OCT:.oct=.cpp)

make: $(OCT)

%.oct: %.cpp
	mkoctfile -s $<

test: $(OCT)
	test_octave_sockets

clean:
	rm -f *.oct *.o

.PHONY: make clean test


