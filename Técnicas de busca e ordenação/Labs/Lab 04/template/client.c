#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "item.h"
#include "sorts.h"

// Para mudar o algoritmo de ordenação, vá em sorts.c na função sort.

extern void sort(Item *, int, int);

int main(int argc, char *argv[])
{ // Input
    int N = atoi(argv[2]);
    Item *itens = malloc(N * sizeof(Item));

    FILE *file = fopen((argv[1]), "r");
    for (int i = 0; i < N; i++)
    {
        fscanf(file, "\n%d", &itens[i]);
    }
    fclose(file);

    FILE *resultados = fopen("../Resultados.txt", "a");

    // Sort

    int time;
    clock_t start = clock();
    sort(itens, 0, N - 1);

    clock_t end = clock();

    time = (end - start) * 1000 / CLOCKS_PER_SEC;

    printf("Arquivo: %s Tempo: %i milissegundos\n", argv[1], time);
    // fprintf(resultados, "Arquivo: %s Tempo: %i milissegundos\n", argv[1], time);

    fclose(resultados);

    // Output

    // for (int i = 0; i < N; i++)
    // {
    //     printf("%d\n", itens[i]);
    // }

    free(itens);
}
