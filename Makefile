CC=gcc
CFLAGS=-I. -Wall  -lm
DEPS = baralho.h jogador.h jogo.h rodada.h
OBJ = main.o baralho.o jogador.o jogo.o rodada.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


trabalhoED1: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o
