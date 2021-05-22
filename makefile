IDIR = ./include
CC=g++
CFLAGS=-I$(IDIR) -Werror -Wall

LINK_TARGET=signal
TEST_TARGET=test

_OBJ = main.o CircularBuffer.o SoundUnit.o Delay.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_TEST_OBJ = test.o CircularBuffer.o SoundUnit.o Delay.o
TEST_OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_DEPS = CircularBuffer.hpp SoundUnit.hpp Delay.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR=obj
SRCDIR=src

all: $(LINK_TARGET)

$(LINK_TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/main.o: main.cpp $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

$(TEST_TARGET): $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/test.o: test.cpp $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/%.o : $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm $(LINK_TARGET) $(TEST_TARGET) $(ODIR)/*.o

