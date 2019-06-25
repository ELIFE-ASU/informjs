#include <node.h>
#include <v8.h>

using namespace v8;

auto add(FunctionCallbackInfo<Value> const& args) -> void {
    auto isolate = args.GetIsolate();

    if (args.Length() < 2) {
        auto msg = String::NewFromUtf8(isolate, "two arguments required",
            NewStringType::kNormal);
        isolate->ThrowException(Exception::TypeError(msg.ToLocalChecked()));
        return;
    }

    if (!args[0]->IsNumber()) {
        auto msg = String::NewFromUtf8(isolate, "first argument is not a number",
            NewStringType::kNormal);
        isolate->ThrowException(Exception::TypeError(msg.ToLocalChecked()));
        return;
    }

    if (!args[1]->IsNumber()) {
        auto msg = String::NewFromUtf8(isolate, "second argument is not a number",
            NewStringType::kNormal);
        isolate->ThrowException(Exception::TypeError(msg.ToLocalChecked()));
        return;
    }

    auto value = args[0].As<Number>()->Value() + args[1].As<Number>()->Value();

    args.GetReturnValue().Set(Number::New(isolate, value));
}

void init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "add", add);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, init);
