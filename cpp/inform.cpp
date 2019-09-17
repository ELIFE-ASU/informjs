#include "./series.h"

namespace inform {
    using namespace v8;

    void init(Local<Object> exports) {
        NODE_SET_METHOD(exports, "mutualInfo", inform::mutual_info);
        NODE_SET_METHOD(exports, "activeInfo", inform::active_info);
        NODE_SET_METHOD(exports, "transferEntropy", inform::transfer_entropy);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, init);
}
