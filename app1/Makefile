CC=clang
CFLAGS=-g -Wall -Wextra -Werror

EXEC=client-introduction client-tutoriel client-interactif client-TUTORIEL client-projetX client-crypteMove client-bayOfPigs client-crypteSeq

all: $(EXEC)

client-interactif: client-interactif.o client.o

client-tutoriel: client-tutoriel.o client.o

client-introduction: client-introduction.o client.o

client-TUTORIEL: client-TUTORIEL.o client.o ressources.o

client-projetX: client-projetX.o client.o ressources.o

client-crypteMove: client-crypteMove.o client.o ressources.o

client-bayOfPigs: client-bayOfPigs.o client.o ressources.o

client-crypteSeq: client-crypteSeq.o client.o ressources.o

client.o: client.c client.h

ressources.o: ressources.c ressources.h

clean:
	rm -f *.o

clear:
	rm -f $(EXEC)
