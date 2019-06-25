#include "./inform.h"

namespace inform {
    using namespace v8;

    auto mutual_info(v8::FunctionCallbackInfo<v8::Value> const& args) -> void;
    auto transfer_entropy(v8::FunctionCallbackInfo<v8::Value> const& args) -> void;
}
