#include "./series.h"

using namespace v8;

void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "add", inform::add);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init);
