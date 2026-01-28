#ifndef BST_H
#define BST_H

typedef struct bst_node bst_node;
typedef struct bst bst;

bst *bst_create();
bst_node *bst_node_create(int key);
bst_node *return_root(bst *t);
int return_key(bst_node *n);
void att_root(bst *t, bst_node *new_root);
bst_node *node_insert(bst_node *new_node, bst_node *root);
void bst_destroy(bst_node *root);
int bst_height(bst_node *root);
void rec_preorder(bst_node *n, void (*visit)(bst_node *));
void rec_inorder(bst_node *n, void (*visit)(bst_node *));
void rec_postorder(bst_node *n, void (*visit)(bst_node *));
void non_recursive_preorder(bst_node *n, void (*visit)(bst_node *));
void non_recursive_inorder(bst_node *n, void (*visit)(bst_node *));
void non_recursive_postorder(bst_node *n, void (*visit)(bst_node *));

#endif