#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"
#include "callback.h"


struct node {
    char *key;
    Callbacks callbacks;
    struct node *left;
    struct node *right;
};
typedef struct node *Tree;

Tree create_tree() {
    return NULL;
}

static Tree create_node(char *key) {
    Tree new_node = malloc(sizeof(struct node));
    new_node->key = malloc(sizeof(char) * strlen(key));
    strcpy(new_node->key, key);
    new_node->callbacks = create_callbacks();
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

Tree get_or_create_node(Tree tree, char *key, Tree *result) {
    if (tree == NULL) {
        Tree new_node = create_node(key);
        *result = new_node;
        return new_node;
    }

    int cmp = strcmp(key, tree->key);
    if (cmp < 0) {
        tree->left = get_or_create_node(tree->left, key, result);
    } else if (cmp > 0) {
        tree->right = get_or_create_node(tree->right, key, result);
    } else {
        *result = tree;
    }
    return tree;
}

Tree get_node(Tree tree, char *key) {
    if (tree == NULL) {
        return NULL;
    }

    int cmp = strcmp(key, tree->key);
    if (cmp < 0) {
        return get_node(tree->left, key);
    } else if (cmp > 0) {
        return get_node(tree->right, key);
    } else {
        return tree;
    }
}

Callbacks get_callbacks(Tree node) {
    return node->callbacks;
}

void print_tree(Tree tree) {
    if (tree == NULL) {
        return;
    }

    print_tree(tree->left);
    printf("%s\n", tree->key);
    print_tree(tree->right);
}

