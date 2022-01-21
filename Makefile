PRG = utf8toAmigaPL

CC = gcc
CFLAGS = -D__PRG_FILE__=\"$(PRG)\"
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