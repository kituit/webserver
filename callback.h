#define GET 0
#define POST 1
#define DELETE 2
#define PUT 3

typedef int MethodType;
typedef struct callbacks_str *Callbacks;
typedef void (*cbk_method)(char **args);

Callbacks create_callbacks();

void set_callback(Callbacks callbacks, cbk_method method, MethodType type);

cbk_method get_callback_method(Callbacks callbacks, MethodType type);