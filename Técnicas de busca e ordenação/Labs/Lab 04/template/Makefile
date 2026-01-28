bub:
	gcc -Wall client.c sorts.c stack.c -o main

clean:
	rm -f *.o a.out

execute:
	
	./main ../input/nearly_sorted/100000.txt 100000
	./main ../input/nearly_sorted/1000000.txt 1000000
	./main ../input/nearly_sorted/10000000.txt 10000000

	./main ../input/reverse_sorted/100000.txt 100000
	./main ../input/reverse_sorted/1000000.txt 1000000
	./main ../input/reverse_sorted/10000000.txt 10000000

	./main ../input/sorted/100000.txt 100000
	./main ../input/sorted/1000000.txt 1000000
	./main ../input/sorted/10000000.txt 1000000

	./main ../input/unif_rand/100000.txt 100000
	./main ../input/unif_rand/1000000.txt 1000000
	./main ../input/unif_rand/10000000.txt 10000000

	./main ../input/few_uniq/10M_const_keys_sorted.txt 10000000
	./main ../input/few_uniq/10M_const_keys_unif_rand.txt 10000000
	