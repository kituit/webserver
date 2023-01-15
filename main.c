#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "callback.h"
#include "router.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 12000

void test(char **args);
void test1(char **args);

Router init_routes(void) {
    Router router = create_router();
    
    add_route(router, "hello", test, GET);
    add_route(router, "hello", test1, POST);
    add_route(router, "ok", test, DELETE);
    add_route(router, "melon", test1, PUT);
    
    return router;
}

int main(void) {
    Router router = init_routes();

    cbk_method foo = get_route_callback(router, "melon", PUT);
    foo(NULL);

    return 0;
}

void test(char **args) {
    printf("Hello world\n");
}

void test1(char **args) {
    printf("Hello Cool\n");
}