#include "./series.h"

namespace inform {
	using namespace v8;
	
	auto get_vector(Isolate *isolate, Local<Value> const &arg) -> Maybe<Series> {
		auto context = isolate->GetCurrentContext();
		if (arg->IsArray()) {
			auto const array = arg.As<Array>();
			auto const len = array->Length();
			auto series = Series(len);
	
			for (size_t i = 0; i < len; ++i) {
				auto const datum = array->Get(context, i).ToLocalChecked();
				if (datum->IsInt32()) {
					series[i] = datum.As<Int32>()->Value();
				} else {
					throws(isolate, Exception::TypeError,
						"element of time series is not an integer");
					return Nothing<Series>();
				}
			}
			return Just(series);
		}
		throws(isolate, Exception::TypeError, "time series is not an array");
		return Nothing<Series>();
	}
	
	void init(Local<Object> exports) {
	    NODE_SET_METHOD(exports, "mutualInfo", inform::mutual_info);
	}
	
	NODE_MODULE(NODE_GYP_MODULE_NAME, init);
}
