all: geraos trab1

trab1: trab1.o funcoestrab.o
	gcc trab1.o funcoestrab.o -o trab1

geraos: trab1.c funcoestrab.c
	gcc -c trab1.c funcoestrab.c

clean:
	rm -rf *.o trab1

