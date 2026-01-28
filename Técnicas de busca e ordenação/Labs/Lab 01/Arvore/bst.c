#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "../Fila/queue.h"
#include "../Pilha/stack.h"

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

bst_node *node_insert(bst_node *new_node, bst_node *root)
{
    if (root == NULL)
    {
        return new_node;
    }
    else
    {
        if (key_compare(new_node, root) < 0)
        {
            root->left = node_insert(new_node, root->left);
        }

        else
        {
            root->right = node_insert(new_node, root->right);
        }
    }
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

void rec_preorder(bst_node *n, void (*visit)(bst_node *))
{
    if (n == NULL)
        return;
    visit(n);
    rec_preorder(n->left, visit);
    rec_preorder(n->right, visit);
}

void rec_inorder(bst_node *n, void (*visit)(bst_node *))
{
    if (n == NULL)
        return;
    rec_inorder(n->left, visit);
    visit(n);
    rec_inorder(n->right, visit);
}

void rec_postorder(bst_node *n, void (*visit)(bst_node *))
{
    if (n == NULL)
        return;
    rec_postorder(n->left, visit);
    rec_postorder(n->right, visit);
    visit(n);
}

void non_recursive_preorder(bst_node *n, void (*visit)(bst_node *))
{
    stack *s = stack_create();
    bst_node *current = n;
    while (current != NULL || return_size(s) != 0)
    {
        if (current != NULL)
        {
            stack_push(s, current);
            visit(current);
            current = current->left;
        }
        else
        {
            current = stack_pop(s);
            current = current->right;
        }
    }
    stack_destroy(s);
}

void non_recursive_inorder(bst_node *n, void (*visit)(bst_node *))
{
    stack *s = stack_create();
    bst_node *current = n;
    while (current != NULL || return_size(s) != 0)
    {
        while (current != NULL)
        {
            stack_push(s, current);
            current = current->left;
        }
        current = stack_pop(s);
        visit(current);
        current = current->right;
    }
    stack_destroy(s);
}

void non_recursive_postorder(bst_node *n, void (*visit)(bst_node *))
{
    stack *s = stack_create();
    bst_node *current = n;
    bst_node *last_visited = NULL;
    while (current != NULL || return_size(s) != 0)
    {
        while (current != NULL)
        {
            stack_push(s, current);
            current = current->left;
        }
        current = stack_pop(s);
        if (current->right == NULL || current->right == last_visited)
        {
            visit(current);
            last_visited = current;
            current = NULL;
        }
        else
        {
            stack_push(s, current);
            current = current->right;
        }
    }
    stack_destroy(s);
}

void non_recursive_level_order(bst_node *n, void (*visit)(bst_node *))
{
    queue *q = queue_create();
    bst_node *current = n;
    queue_push(q, current);
    while (queue_size(q) > 0)
    {
        current = queue_pop(q);
        visit(current);
        if (current->left != NULL)
        {
            queue_push(q, current->left);
        }
        if (current->right != NULL)
        {
            queue_push(q, current->right);
        }
    }
    queue_destroy(q);
}