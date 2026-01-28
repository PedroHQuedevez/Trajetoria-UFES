
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

Vector *string_split(char *str)
{
    Vector *words = vector_construct();

    // Split the string at every space character
    char *word = strtok(str, " ");

    while (word != NULL)
    {
        // o strdup faz um malloc internamente! Lembre-se de remove-lo!
        vector_push_back(words, strdup(word));
        word = strtok(NULL, " ");
    }

    return words;
}

void libera_dados(Vector *words)
{
    for (int i = 0; i < vector_size(words); i++)
        // libera os espacos alocados pelo strdup
        free(vector_get(words, i));

    // libera o vetor
    vector_destroy(words);
}

// precisamos fazer essa funcao porque as funcoes do vector esperam como argumento
// uma funcao que recebe dois void* e nao dois char*.
int compara_strings(void *a, void *b)
{
    return strcmp((char *)a, (char *)b);
}

int main(int argc, char **argv)
{
    char texto[100];

    printf("Digite um texto: ");
    scanf("%[^\n]", texto);

    Vector *words = string_split(texto);
    Vector *unique = vector_unique(words, compara_strings);

    printf("Lista de palavras diferentes: \n");
    for (int i = 0; i < vector_size(words); i++)
    {
        printf("%s\n", (char *)vector_get(words, i));
    }

    libera_dados(words);
    // o vector unique faz copia de ponteiros (shallow copy) e, por isso, nao
    // precisa liberar os dados do vetor antes de remove-lo. Eles ja serao
    // liberados acima.
    vector_destroy(unique);

    return 0;
}
