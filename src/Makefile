CC=g++

IDIR=../include

_DEPS = linearInterpolate.hpp, util.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

OBJ = linearInterpolate.o test.o

%.o: %.cpp $(DEPS)
        $(CC) -c -o $@ $< $(CFLAGS)

linearInterpolate: $(OBJ)
        $(CC) -o $@ $^ $(CFLAGS)
