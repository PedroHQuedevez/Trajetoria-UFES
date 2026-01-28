#ifndef _FORWARD_LIST_H
#define _FORWARD_LIST_H

typedef struct forward_list forward_list;
typedef struct node node;

typedef void (*node_print)(node *n);
typedef int (*node_comp)(node *n, void *item);
typedef void (*node_destroy)(node *n);

forward_list *list_construct();
void list_push_front(forward_list *fl, node *node);
node *node_construct();
void node_free_NULL(node *n);
void list_printf(forward_list *fl, node_print node_print_type);
node *list_get(forward_list *fl, node_comp node_fctcomp, void *item);
void list_destroy(forward_list *fl, node_destroy node_destroy);
void forward_list_unique(forward_list *fl, node_comp node_comp, node *node_atual);
forward_list *list_copy(forward_list *fl);
void ordena_lista(forward_list *fl, node_comp node_fctcomp);
void node_free_data_externa(node *n);
void list_remove(forward_list *l, void *item, node_comp node_fctcomp);
node *node_constructt(void *data, node *next);
void *retorna_node_data(node *n);
#endif