CFLAGS = -Wall -Wextra -lpthread

all:
	gcc $(CFLAGS) -o macacosV2 src/client/main.c src/libs/src/*.c
clean:
	rm -f macacosV2
run:
	./macacosV2
valgrind:
	valgrind --track-origins=yes --leak-check=full -s ./macacosV2