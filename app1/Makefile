CC=clang -g
CFLAGS=-g -Wall -Wextra -Werror

EXEC=client-introduction client-tutoriel client-interactif client-TUTORIEL client-projetX client-crypteMove client-bayOfPigs client-crypteSeq client-northwoods client-lostCause client-planB client-oneMillion

all: $(EXEC)

client-interactif: client-interactif.o client.o

client-tutoriel: client-tutoriel.o client.o

client-introduction: client-introduction.o client.o

client-TUTORIEL: client-TUTORIEL.o client.o ressources.o asserts.o

client-projetX: client-projetX.o client.o ressources.o asserts.o

client-crypteMove: client-crypteMove.o client.o ressources.o asserts.o

client-bayOfPigs: client-bayOfPigs.o client.o ressources.o asserts.o

client-crypteSeq: client-crypteSeq.o client.o ressources.o asserts.o

client-northwoods: client-northwoods.o client.o ressources.o asserts.o

client-lostCause: client-lostCause.o client.o ressources.o asserts.o

client-planB: client-planB.o client.o ressources.o asserts.o

client-oneMillion: client-oneMillion.o client.o ressources.o asserts.o

client.o: client.c client.h

ressources.o: ressources.c ressources.h

asserts.o: asserts.c asserts.h ressources.o

clean:
	rm -f *.o

clear:
	rm -f $(EXEC)
