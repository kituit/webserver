#include "callback.h"

typedef struct node *Tree;

Tree create_tree();

Tree get_or_create_node(Tree tree, char *key, Tree *result);

Tree get_node(Tree tree, char *key);

Callbacks get_callbacks(Tree node);

void print_tree(Tree tree);