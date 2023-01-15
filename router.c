#include <stdlib.h>
#include "router.h"
#include "tree.h"

struct router {
    Tree tree;
    int num_routes;
};

Router create_router() {
    Router router = malloc(sizeof(struct router));
    router->num_routes = 0;
    router->tree = create_tree();
    return router;
}

void add_route(Router router, char *key, cbk_method method, MethodType type) {
    Tree node;
    router->tree = get_or_create_node(router->tree, key, &node);
    Callbacks callbacks = get_callbacks(node);
    set_callback(callbacks, method, type);
    router->num_routes += 1;
}

cbk_method get_route_callback(Router router, char *route, MethodType type) {
    Tree node = get_node(router->tree, route);
    if (node == NULL) {
        return NULL;
    }
    Callbacks callbacks = get_callbacks(node);
    return get_callback_method(callbacks, type);
}