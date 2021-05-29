IDIR = ./include
CC=g++
CFLAGS=-I$(IDIR) -Werror -Wall

LINK_TARGET=signal
TEST_TARGET=test

_OBJ = CircularBuffer.o SoundUnit.o SoundPath.o Delay.o Filter.o Oscillator.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_DEPS = CircularBuffer.hpp SoundUnit.hpp SoundPath.hpp Delay.hpp Filter.hpp Oscillator.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR=obj
SRCDIR=src

all: $(LINK_TARGET) $(TEST_TARGET)

$(LINK_TARGET): $(OBJ) $(ODIR)/main.o
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/main.o: main.cpp $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

$(TEST_TARGET): $(OBJ) $(ODIR)/test.o
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/test.o: test.cpp $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/%.o : $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm $(LINK_TARGET) $(TEST_TARGET) $(ODIR)/*.o

