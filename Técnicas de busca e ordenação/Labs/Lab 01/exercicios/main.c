#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../Arvore/bst.h"

void node_visit(bst_node *n)
{
    // printf("%d\n", return_key(n));
}

int main()
{
    int key_total;
    double seconds;
    clock_t start;
    clock_t end;

    bst *t = bst_create();

    scanf("\n%i", &key_total);

    srand(time(NULL));
    for (int i = 0; i < key_total; i++)
    {
        int r = rand();
        bst_node *new_node = bst_node_create(r);
        att_root(t, node_insert(new_node, return_root(t)));
    }

    // printf("%d\n", bst_height(return_root(t)));

    // --------------------------------------------------------

    printf("\npreorder;\n");
    start = clock();
    rec_preorder(return_root(t), node_visit);
    end = clock();
    seconds = ((double)end - start) / CLOCKS_PER_SEC;
    printf(" % lf \n", seconds);

    start = clock();
    non_recursive_preorder(return_root(t), node_visit);
    end = clock();
    seconds = ((double)end - start) / CLOCKS_PER_SEC;
    printf(" % lf \n", seconds);

    printf("\n");

    // --------------------------------------------------------

    printf("\ninorder;\n");
    start = clock();
    rec_inorder(return_root(t), node_visit);
    end = clock();
    seconds = ((double)end - start) / CLOCKS_PER_SEC;
    printf(" % lf \n", seconds);

    start = clock();
    non_recursive_inorder(return_root(t), node_visit);
    end = clock();
    seconds = ((double)end - start) / CLOCKS_PER_SEC;
    printf(" % lf \n", seconds);

    printf("\n");

    // --------------------------------------------------------

    printf("\npostorder;\n");
    start = clock();
    rec_postorder(return_root(t), node_visit);
    end = clock();
    seconds = ((double)end - start) / CLOCKS_PER_SEC;
    printf(" % lf \n", seconds);

    start = clock();
    non_recursive_postorder(return_root(t), node_visit);
    end = clock();
    seconds = ((double)end - start) / CLOCKS_PER_SEC;
    printf(" % lf \n", seconds);

    printf("\n");

    // --------------------------------------------------------

    bst_destroy(return_root(t));
    free(t);

    return 0;
}