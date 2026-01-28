#include <stdio.h>
#include <stdlib.h>
#include "forward_list.h"
#include "hash.h"

struct HashTable
{
    int table_size;
    HashFunction hash_fn;
    CmpFunction cmp_fn;
    forward_list **buckets;
};

HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn)
{
    HashTable *hash_tbl = calloc(1, sizeof(HashTable));

    hash_tbl->table_size = table_size;
    hash_tbl->hash_fn = hash_fn;
    hash_tbl->cmp_fn = cmp_fn;
    hash_tbl->buckets = (forward_list **)calloc(table_size, sizeof(forward_list *));

    return hash_tbl;
}

HashTableItem *Hash_table_item_construct(void *key, void *val)
{
    HashTableItem *item = (HashTableItem *)calloc(1, sizeof(HashTableItem));
    item->key = key;
    item->val = val;
    return item;
}

void hash_table_set(HashTable *h, void *key, void *val)
{
    int hash_val = h->hash_fn(h, key);
    if (h->buckets[hash_val] == NULL)
    {
        h->buckets[hash_val] = list_construct();
    }
    HashTableItem *item = Hash_table_item_construct(key, val);
    node *n = node_constructt(item, NULL);
    list_push_front(h->buckets[hash_val], n);
}

int hash_key_exist(HashTable *h, void *key)
{
    int hash_val = h->hash_fn(h, key);
    if (list_get(h->buckets[hash_val], h->cmp_fn, key) != NULL)
    {
        return 1;
    }
    return 0;
}

void *hash_table_get(HashTable *h, void *key)
{
    int hash_val = h->hash_fn(h, key);
    if (h->buckets[hash_val] != NULL)
    {
        node *n = list_get(h->buckets[hash_val], h->cmp_fn, key);
        if (n != NULL)
        {
            return retorna_node_data(n);
        }
        else
        {
            return NULL;
        }
    }
    return NULL;
}

void *hash_table_pop(HashTable *h, void *key)
{
    // pra depois pq não sei se será necessário;
}

int hash_table_size(HashTable *h)
{
    return h->table_size;
}

void hash_table_item_destroy(HashTableItem *item)
{
    free(item);
}

void hash_table_destroy(HashTable *h)
{
    if (h != NULL)
    {
        for (int i = 0; i < h->table_size; i++)
        {
            if (h->buckets[i] != NULL)
            {
                // se necessário, colocar uma função dentro da hash para desalocar o HashTableItem;
                // list_destroy()
            }
        }
        free(h->buckets);
        free(h);
    }
}

void add_1_to_val(HashTableItem *h)
{
    int *val = (int *)h->val;
    (*val)++;
}

void print_pair_char_int(HashTableItem *item)
{
    char *char_item = (char *)item->key;
    int *int_item = item->val;

    printf("%s %i\n", char_item, *(int *)item->val);
}

void print_pair_arq(FILE *arq, HashTableItem *item)
{
    char *char_item = (char *)item->key;
    int *int_item = item->val;

    fprintf(arq, "%s %i\n", char_item, *(int *)item->val);
}

void *retorna_hashtableitem_val(HashTableItem *item)
{
    return item->val;
}