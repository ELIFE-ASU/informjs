#include "./series.h"

using namespace v8;

auto inform::add(FunctionCallbackInfo<Value> const& args) -> void {
    auto isolate = args.GetIsolate();

    if (args.Length() < 2) {
        return inform::throws(isolate, Exception::TypeError, "two arguments are required");
    }

	auto const maybe_a = inform::get_number<Number, double>(args[0]);
    if (maybe_a.IsNothing()) {
        return inform::throws(isolate, Exception::TypeError, "first argument is not a number");
    }

	auto const maybe_b = inform::get_number<Number, double>(args[1]);
    if (maybe_b.IsNothing()) {
        return inform::throws(isolate, Exception::TypeError, "second argument is not a number");
    }

    auto value = maybe_a.FromJust() + maybe_b.FromJust();

    args.GetReturnValue().Set(Number::New(isolate, value));
}
