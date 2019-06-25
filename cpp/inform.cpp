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
        } else if (arg->IsInt32Array()) {
            auto const array = arg.As<Int32Array>();
            auto const len = array->Length();
            auto series = Series(len);
            array->CopyContents(series.data(), sizeof(int32_t)*len);
            return Just(series);
        } else if (arg->IsArrayBuffer()) {
            auto const array = arg.As<ArrayBuffer>();

            if (array->ByteLength() % sizeof(int32_t) != 0) {
                throws(isolate, Exception::TypeError,
                    "array buffer length is inconsistent with 32-bit integer contents");
                return Nothing<Series>();
            }

            auto const len = array->ByteLength() / sizeof(int32_t);
            auto const data = static_cast<int32_t*>(array->GetContents().Data());
			auto series = Series(data, data+len);

            return Just(series);
        }
        throws(isolate, Exception::TypeError, "time series is not an array");
        return Nothing<Series>();
    }

    void init(Local<Object> exports) {
        NODE_SET_METHOD(exports, "mutualInfo", inform::mutual_info);
        NODE_SET_METHOD(exports, "transferEntropy", inform::transfer_entropy);
    }

    NODE_MODULE(NODE_GYP_MODULE_NAME, init);
}
