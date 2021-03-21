IDIR = ./include
CC=g++
CFLAGS=-I$(IDIR) -Werror -Wall

LINK_TARGET=signal

_OBJ = main.o CircularBuffer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_DEPS = CircularBuffer.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR=obj
SRCDIR=src

all: $(LINK_TARGET)

$(LINK_TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/main.o: main.cpp $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/%.o : $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm $(LINK_TARGET) $(ODIR)/*.o

