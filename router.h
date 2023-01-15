#include "callback.h"

typedef struct router *Router;

Router create_router();

void add_route(Router router, char *key, cbk_method method, MethodType type);

cbk_method get_route_callback(Router router, char *route, MethodType type);