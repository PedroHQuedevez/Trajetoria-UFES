CFLAGS = -Wall -Wextra -lpthread

all:
	gcc $(CFLAGS) -o banheiro src/client/funcionario.c src/libs/src/*.c
clean:
	rm -f banheiro
run:
	./banheiro
valgrind:
	valgrind --track-origins=yes --leak-check=full -s ./banheiro