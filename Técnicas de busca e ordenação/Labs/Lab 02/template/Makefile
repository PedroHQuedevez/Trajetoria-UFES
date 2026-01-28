bub:
	gcc -Wall client.c sorts.c -o main

clean:
	rm -f *.o a.out

execute:
	./main ../in/nearly_sorted/1Knearly_sorted.txt 1000
	./main ../in/reverse_sorted/1Kreverse_sorted.txt 1000
	./main ../in/sorted/1Ksorted.txt 1000
	./main ../in/unif_rand/1Kunif_rand.txt 1000

	./main ../in/nearly_sorted/10Knearly_sorted.txt 10000
	./main ../in/reverse_sorted/10Kreverse_sorted.txt 10000
	./main ../in/sorted/10Ksorted.txt 10000
	./main ../in/unif_rand/10Kunif_rand.txt 10000
	
	./main ../in/unif_rand/100Kunif_rand.txt 100000
	./main ../in/nearly_sorted/100Knearly_sorted.txt 100000
	./main ../in/reverse_sorted/100Kreverse_sorted.txt 100000
	./main ../in/sorted/100Ksorted.txt 100000
