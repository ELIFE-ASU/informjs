#include "./series.h"

#include <inform/mutual_info.h>
#include <inform/active_info.h>
#include <inform/transfer_entropy.h>

using namespace v8;

auto inform::mutual_info(FunctionCallbackInfo<Value> const& args) -> void {
    auto isolate = args.GetIsolate();

    if (args.Length() < 2) {
        return inform::throws(isolate, Exception::TypeError, "two arguments are required");
    }

    auto const maybe_xs = inform::get_vector(isolate, args[0]);
    if (maybe_xs.IsNothing()) {
        return;
    }

    auto const maybe_ys = inform::get_vector(isolate, args[1]);
    if (maybe_ys.IsNothing()) {
        return;
    }

    auto const xs = maybe_xs.FromJust();
    auto const ys = maybe_ys.FromJust();

    if (xs.size() != ys.size()) {
        return throws(isolate, Exception::TypeError, "time series have different lengths");
    }
    auto series = std::vector<int32_t>(xs.size() + ys.size());
    std::copy(xs.begin(), xs.end(), series.begin());
    std::copy(ys.begin(), ys.end(), series.begin() + xs.size());

    auto bases = std::vector<int>{ series_base(xs), series_base(ys) };

    inform_error err = INFORM_SUCCESS;
    auto mi = inform_mutual_info(series.data(), 2, xs.size(), bases.data(), &err);

    if (err) {
        return throws(isolate, Exception::Error, inform_strerror(&err));
    }

    args.GetReturnValue().Set(Number::New(isolate, mi));
}

auto inform::active_info(FunctionCallbackInfo<Value> const& args) -> void {
    auto isolate = args.GetIsolate();

    if (args.Length() != 2) {
        return inform::throws(isolate, Exception::TypeError, "two arguments are required");
    }

    auto const maybe_xs = inform::get_vector(isolate, args[0]);
    if (maybe_xs.IsNothing()) {
        return;
    }

    auto const maybe_k = inform::get_number<Integer, size_t>(args[1]);
    if (maybe_k.IsNothing()) {
        return throws(isolate, Exception::TypeError, "history length is not an unsigned integer");
    }

    auto const xs = maybe_xs.FromJust();
    auto const k = maybe_k.FromJust();

    auto const b = series_base(xs);

    inform_error err = INFORM_SUCCESS;
    auto ai = inform_active_info(xs.data(), 1, xs.size(), b, k, &err);

    if (err) {
        return throws(isolate, Exception::Error, inform_strerror(&err));
    }

    args.GetReturnValue().Set(Number::New(isolate, ai));
}

auto inform::transfer_entropy(FunctionCallbackInfo<Value> const& args) -> void {
    auto isolate = args.GetIsolate();

    if (args.Length() < 3) {
        return inform::throws(isolate, Exception::TypeError, "three arguments are required");
    }

    auto const maybe_xs = inform::get_vector(isolate, args[0]);
    if (maybe_xs.IsNothing()) {
        return;
    }

    auto const maybe_ys = inform::get_vector(isolate, args[1]);
    if (maybe_ys.IsNothing()) {
        return;
    }

    auto const maybe_k = inform::get_number<Integer, size_t>(args[2]);
    if (maybe_k.IsNothing()) {
        return throws(isolate, Exception::TypeError, "history length is not an unsigned integer");
    }

    auto const xs = maybe_xs.FromJust();
    auto const ys = maybe_ys.FromJust();
    auto const k = maybe_k.FromJust();

    if (xs.size() != ys.size()) {
        return throws(isolate, Exception::TypeError, "time series have different lengths");
    }

    auto const b = std::max(series_base(xs), series_base(ys));

    inform_error err = INFORM_SUCCESS;
    auto te = inform_transfer_entropy(xs.data(), ys.data(), NULL, 0,  1, xs.size(), b, k, &err);

    if (err) {
        return throws(isolate, Exception::Error, inform_strerror(&err));
    }

    args.GetReturnValue().Set(Number::New(isolate, te));
}
