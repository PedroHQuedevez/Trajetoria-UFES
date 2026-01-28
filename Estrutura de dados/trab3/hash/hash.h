#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_

typedef struct HashTable HashTable;

typedef int (*HashFunction)(HashTable *, void *);
typedef int (*CmpFunction)(node *k1, void *k2);

typedef struct
{
    void *key;
    void *val;
} HashTableItem;

/**
 * @brief Cria a tabela hash
 * @param table_size
 * Número de buckets na tabela hash
 * @param hash_fn
 * Ponteiro de função que recebe como entrada uma chave do tipo void* e retorna um inteiro.
 * @param cmp_fn
 * Ponteiro de função que recebe como entrada dois void* representando duas chaves e tem a mesma semântica da função strcmp
 * @return HashTable*
 * Retorna o ponteiro da tabela hash recém alocada.
 */
HashTable *hash_table_construct(int table_size, HashFunction hash_fn, CmpFunction cmp_fn);

// funcao para insercao/atualizacao de pares chave-valor em O(1). Esta função deve usar hash modular para garantir que o valor da chave será mapeado em um bucket válido da tabela hash.
void hash_table_set(HashTable *h, void *key, void *val);

// retorna o valor associado com a chave key ou NULL se ela nao existir em O(1). Esta função deve usar hash modular para garantir que o valor da chave será mapeado em um bucket válido da tabela hash.
void *hash_table_get(HashTable *h, void *key);

// remove o par chave-valor e retorna o valor ou NULL se nao existir tal chave em O(1).
void *hash_table_pop(HashTable *h, void *key);

// numero de elementos
int hash_table_size(HashTable *h);

// libera o espaco alocado para a tabela hash
void hash_table_destroy(HashTable *h);

int hash_key_exist(HashTable *h, void *key);

void add_1_to_val(HashTableItem *h);

void print_pair_char_int(HashTableItem *item);

HashTableItem *Hash_table_item_construct(void *key, void *val);

void *retorna_hashtableitem_val(HashTableItem *item);
#endif