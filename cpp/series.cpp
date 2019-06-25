#include "./series.h"

#include <algorithm>
#include <inform/mutual_info.h>
#include <numeric>

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

	auto bases = std::vector<int>{
    	std::accumulate(xs.begin(), xs.end(), 2,
        	[](int32_t x, int32_t y){ return std::max(x, y + 1); }),
		std::accumulate(ys.begin(), ys.end(), 2,
        	[](int32_t x, int32_t y){ return std::max(x, y + 1); })
	};

    inform_error err = INFORM_SUCCESS;
    auto mi = inform_mutual_info(series.data(), 2, xs.size(), bases.data(), &err);

    if (err) {
        return throws(isolate, Exception::Error, inform_strerror(&err));
    }

    args.GetReturnValue().Set(Number::New(isolate, mi));
}
