#include <stdio.h>
#include <stdlib.h>
#include "../Arvore/bst.h"
#include <time.h>

// void node_visit(bst_node *n)
// {
//     // printf("%d\n", return_key(n));
// }

int main()
{
    int key_total;

    bst *t = bst_create();
    bst *t_ordered = bst_create();
    scanf("\n%i", &key_total);
    srand(time(NULL));
    for (int i = 0; i < key_total; i++)
    {
        int r = rand();
        bst_node *new_node_randon = bst_node_create(r);
        att_root(t, random_insert(new_node_randon, return_root(t)));
    }

    for (int i = 0; i < key_total; i++)
    {
        bst_node *new_node_ordered = bst_node_create(i);
        att_root(t_ordered, random_insert(new_node_ordered, return_root(t_ordered)));
    }

    printf("%d\n", bst_height(return_root(t)));
    printf("%d\n", bst_height(return_root(t_ordered)));

    // printf("%d normal\n", bst_height(return_root(t)));
    // printf("%d rotate\n", bst_height(return_root(t_rotate)));
    // att_root(t_rotate, balance(return_root(t_rotate)));
    // printf("%d balance\n", bst_height(return_root(t_rotate)));

    bst_destroy(return_root(t));
    bst_destroy(return_root(t_ordered));
    free(t);
    free(t_ordered);

    return 0;
}