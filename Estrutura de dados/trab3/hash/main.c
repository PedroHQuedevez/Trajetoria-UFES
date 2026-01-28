
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forward_list.h"
#include "vector.h"
#include "hash.h"

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

int Hash_Cmp(node *n, void *b)
{
    HashTableItem *a = (HashTableItem *)retorna_node_data(n);
    return strcmp((char *)a->key, (char *)b);
}

int hashU(HashTable *ht, void *val)
{
    char *v = (char *)val;
    int h, a = 31415, b = 27183;
    for (h = 0; *v != '\0'; v++)
    {
        h = (a * h + *v) % hash_table_size(ht);
    }
    return h;
}

// int Hash_Cmp(void *key1, void *key2)
// {
//     char *c1 = (char *)key1;
//     char *c2 = (char *)key2;

//     return strcmp(c1, c2);
// }

int main(int argc, char **argv)
{
    // char texto[100];

    // printf("Digite um texto: \n");
    // scanf("%[^\n]", texto);

    // Vector *words = string_split(texto);
    // Vector *unique = vector_unique(words, compara_strings);

    // ler todos os nomes de arquivo;
    char archive_name[100];
    Vector *archive_names = vector_construct();

    while ((scanf("\n%s", archive_name)) != -1)
    {
        char *a = (char *)malloc(sizeof(char) * 100);
        strcpy(a, archive_name);
        vector_push_back(archive_names, a);
        // printf("%s\n", a);
    }

    // for (int i = 0; i < vector_size(archive_names); i++)
    //     {
    // printf("%s\n", (char *)vector_get(archive_names, i));
    //     }

    // hash com palavras/hash;
    HashTable *hash_table_palavras_hash = hash_table_construct(10009, hashU, Hash_Cmp);

    for (int i = 0; i < vector_size(archive_names); i++)
    {
        // abre arquivo atual;
        char archive_path[100];
        sprintf(archive_path, "case/%s", (char *)vector_get(archive_names, i));
        FILE *archive = fopen(archive_path, "r");
        if (archive == NULL)
        {
            printf("%s\n", archive_path);
            printf("ERRO AO LER O ARQUIVO\n");
            exit(1);
        }
        // le palavras arquivo
        char archive_text[1000];
        fgets(archive_text, 999, archive);
        // printf("%s\n", archive_path);
        // printf("%s\n", archive_text);
        Vector *words_archive = string_split(archive_text);
        Vector *unique_archive = vector_unique(words_archive, compara_strings);

        for (int j = 0; j < vector_size(unique_archive); j++)
        {
            HashTableItem *item_palavra_hash = (HashTableItem *)hash_table_get(hash_table_palavras_hash, vector_get(unique_archive, j)); // verificar se a chave existe;
            if (item_palavra_hash == NULL)                                                                                               // verifica somente se a hash com a palavra existe;
            {
                HashTable *hash_arquivo_freq = hash_table_construct(1009, hashU, Hash_Cmp);
                HashTableItem *palavra_com_hash = Hash_table_item_construct(vector_get(unique_archive, j), hash_arquivo_freq); // palavra com a hash anexada;
                hash_table_set(hash_table_palavras_hash, vector_get(unique_archive, j), palavra_com_hash);                     // adiciona a palavra com a hash na lista;
                // se a palavra não existia dentro da hash então não tem nenhum arquivo/frequencia armazenado;
                int *freq = (int *)malloc(sizeof(int));
                *freq = 1;
                HashTableItem *arquivo_com_freq = Hash_table_item_construct(vector_get(archive_names, i), freq);
                hash_table_set(hash_arquivo_freq, vector_get(archive_names, i), arquivo_com_freq);
            }
            else
            { // erro aqui
                HashTable *hash_arquivo_freq = (HashTable *)retorna_hashtableitem_val(item_palavra_hash);
                HashTableItem *arquivo_com_freq = (HashTableItem *)hash_table_get(hash_arquivo_freq, vector_get(archive_names, i)); // erro aqui!!!!
                if (arquivo_com_freq != NULL)
                {
                    add_1_to_val(arquivo_com_freq);
                }
                else
                {
                    int *freq = (int *)malloc(sizeof(int));
                    *freq = 1;
                    HashTableItem *arquivo_com_freq = Hash_table_item_construct(vector_get(archive_names, i), freq);
                    hash_table_set(hash_arquivo_freq, vector_get(archive_names, i), arquivo_com_freq);
                }
                // se a palavra já está com a palavra/hash armazenada, procurar o par arquivo/frequencia dentro da hash palavra/hash;
                // para procurar, usar hashtableget dentro da hash da palavra/hash usando o nome do arquivo como key;
            }

            // verificar se dentro do par chave/valor, da primeira hash , se o par arquivo/frequência existe;
        }
    }

    // char index_path[100];
    // sprintf(index_path, "case/index.txt");
    // FILE *index = fopen(index_path, "w");

    // hash_table_destroy(hash_table_palavras_hash);
    // vector_destroy(archive_names);

    // libera_dados(words);
    //  o vector unique faz copia de ponteiros (shallow copy) e, por isso, nao
    //  precisa liberar os dados do vetor antes de remove-lo. Eles ja serao
    //  liberados acima.
    // vector_destroy(unique);

    return 0;
}
