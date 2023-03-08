#
# makefile for host:Linux -> taget:Linux
#

include makefile.prg.mk

CC = gcc
CFLAGS = -D__PRG_FILE__=\"$(PRG)\" -D__PRG_VERSION__=\"$(VER)\" -O3
LFLAGS =

OBJ = utf8toAmigaPL.o

%.o: %.c *.h
	$(CC) -c -o $@ $< $(CFLAGS)

all: $(PRG)

$(PRG): $(OBJ)
	$(CC) -o $@ $^ $(LFLAGS)
	chmod +x $(PRG)

clean:
	rm -f *.o
	rm -f $(PRG)
