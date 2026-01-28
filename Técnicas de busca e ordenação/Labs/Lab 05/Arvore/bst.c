#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "../Fila/queue.h"
#include "../Pilha/stack.h"
#include <time.h>

typedef struct bst
{
    bst_node *root;
    int size;
} bst;

typedef struct bst_node
{
    int key;
    struct bst_node *left;
    struct bst_node *right;
    int size;
} bst_node;

bst *bst_create()
{
    bst *t = (bst *)malloc(sizeof(bst));
    t->root = NULL;
    t->size = 0;
    return t;
}

bst_node *bst_node_create(int key)
{
    bst_node *n = (bst_node *)malloc(sizeof(bst_node));
    n->key = key;
    n->left = NULL;
    n->right = NULL;

    return n;
}

int return_key(bst_node *n)
{
    return n->key;
}

int key_compare(bst_node *a, bst_node *b)
{
    if (a->key < b->key)
        return -1;
    else if (a->key > b->key)
        return 1;
    else
        return 0;
}

bst_node *return_root(bst *t)
{
    return t->root;
}

void att_root(bst *t, bst_node *new_root)
{
    t->root = new_root;
}

int node_size(bst_node *n)
{
    return n == NULL ? 0 : n->size;
}

void update_size(bst_node *n)
{
    if (n != NULL)
    {
        n->size = 1 + node_size(n->left) + node_size(n->right);
    }
}

bst_node *node_insert(bst_node *new_node, bst_node *root)
{
    if (root == NULL)
    {
        new_node->size = 1;
        return new_node;
    }

    if (key_compare(new_node, root) < 0)
    {
        root->left = node_insert(new_node, root->left);
    }
    else
    {
        root->right = node_insert(new_node, root->right);
    }

    update_size(root);
    return root;
}

bst_node *rotate_right(bst_node *n)
{
    bst_node *t = n->left;
    n->left = t->right;
    t->right = n;
    update_size(n);
    update_size(t);
    return t;
}

bst_node *rotate_left(bst_node *n)
{
    bst_node *t = n->right;
    n->right = t->left;
    t->left = n;
    update_size(n);
    update_size(t);
    return t;
}

bst_node *insert_whit_rotate(bst_node *new_node, bst_node *root)
{
    if (root == NULL)
    {
        return new_node;
    }

    if (key_compare(new_node, root) < 0)
    {
        root->left = insert_whit_rotate(new_node, root->left);
        root = rotate_right(root);
    }
    else
    {
        root->right = insert_whit_rotate(new_node, root->right);
        root = rotate_left(root);
    }

    return root;
}

bst_node *partition(bst_node *n, int k)
{
    if (n == NULL)
    {
        return NULL;
    }

    int t = node_size(n->left);
    if (t > k)
    {
        n->left = partition(n->left, k);
        n = rotate_right(n);
    }
    else if (t < k)
    {
        n->right = partition(n->right, k - t - 1);
        n = rotate_left(n);
    }

    return n;
}

bst_node *balance(bst_node *n)
{
    if (n == NULL || node_size(n) < 2)
    {
        return n;
    }

    n = partition(n, node_size(n) / 2);
    n->left = balance(n->left);
    n->right = balance(n->right);

    return n;
}

bst_node *random_insert(bst_node *new_node, bst_node *root)
{
    if (root == NULL)
    {
        new_node->size = 1;
        return new_node;
    }
    srand(time(NULL));
    int n = node_size(root);
    if (rand() % (n + 1) == 0)
    {
        return insert_whit_rotate(new_node, root);
    }

    if (key_compare(new_node, root) < 0)
    {
        root->left = random_insert(new_node, root->left);
    }
    else
    {
        root->right = random_insert(new_node, root->right);
    }

    update_size(root);
    return root;
}

void bst_destroy(bst_node *root)
{
    if (root == NULL)
        return;

    if (root->left != NULL)
    {
        bst_destroy(root->left);
    }
    if (root->right != NULL)
    {
        bst_destroy(root->right);
    }
    free(root);
}

int bst_height(bst_node *root)
{
    if (root == NULL)
        return -1;

    int left_height = bst_height(root->left);
    int right_height = bst_height(root->right);
    return 1 + (left_height > right_height ? left_height : right_height);
}
