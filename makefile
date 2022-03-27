IDIR = ./include
CC=gcc
CFLAGS=-I$(IDIR) -Werror -Wall

LINK_TARGET=signal
TEST_TARGET=test

_OBJ = CircularBuffer.o SoundPath.o Delay.o Filter.o Oscillator.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

_DEPS = CircularBuffer.h SoundPath.h Delay.h Filter.h Oscillator.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR=obj
SRCDIR=src

all: $(LINK_TARGET) $(TEST_TARGET)

$(LINK_TARGET): $(OBJ) $(ODIR)/main.o
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/main.o: main.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

$(TEST_TARGET): $(OBJ) $(ODIR)/test.o
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/test.o: test.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

$(ODIR)/%.o : $(SRCDIR)/%.c $(DEPS)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm $(LINK_TARGET) $(TEST_TARGET) $(ODIR)/*.o

