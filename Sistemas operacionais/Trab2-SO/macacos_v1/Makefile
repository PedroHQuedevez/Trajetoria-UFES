CFLAGS = -Wall -Wextra -lpthread

all:
	gcc $(CFLAGS) -o macacosV1 src/client/main.c src/libs/src/*.c
clean:
	rm -f macacosV1
run:
	./macacosV1
valgrind:
	valgrind --track-origins=yes --leak-check=full -s ./macacosV1