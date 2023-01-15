#include <stdlib.h>
#include "callback.h"

struct callbacks_str {
    cbk_method get;
    cbk_method post;
    cbk_method delete;
    cbk_method put;
};

Callbacks create_callbacks() {
    Callbacks callbacks = malloc(sizeof(struct callbacks_str));
    callbacks->get = NULL;
    callbacks->post = NULL;
    callbacks->delete = NULL;
    callbacks->put = NULL;
}

void set_callback(Callbacks callbacks, cbk_method method, MethodType type) {
    switch (type) {
        case GET: callbacks->get = method; break;
        case POST: callbacks->post = method; break;
        case DELETE: callbacks->delete = method; break;
        case PUT: callbacks->put = method; break;
    }
}

cbk_method get_callback_method(Callbacks callbacks, MethodType type) {
    switch (type) {
        case GET: return callbacks->get;
        case POST: return callbacks->post;
        case DELETE: return callbacks->delete;
        case PUT: return callbacks->put;
        default: return NULL;
    }
}