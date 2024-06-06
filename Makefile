CC = gcc

CFLAGS = `pkg-config --cflags gtk+-3.0 appindicator3-0.1` -Wall -lpthread -lX11

LIBS = `pkg-config --libs gtk+-3.0 appindicator3-0.1` -Wall -lpthread -lX11

# File names

SRC = gxcapindicator.c

OBJ = $(SRC:.c=.o)

EXE = gxcapindicator

# Build executable files

all: $(EXE)

gxcapindicator: gxcapindicator.o

	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

# Debug step

debug:

	$(CC) $(CFLAGS) -g $(SRC) -o debug $(LIBS)

# Test step

test:

	./gxcapindicator

# Clean object files and executables

clean:

	rm -f $(OBJ) $(EXE) debug
