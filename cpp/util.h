#pragma once

#include <algorithm>
#include <node.h>
#include <numeric>
#include <v8.h>
#include <vector>

namespace inform {
    using namespace v8;

    using Series = std::vector<int32_t>;

    template <typename Iterator, typename Type = typename std::iterator_traits<Iterator>::value_type>
    auto series_base(Iterator start, Iterator stop) -> Type {
        return std::accumulate(start, stop, Type{2},
            [](Type x, Type y) { return std::max(x, y + 1); });
    }

    template <typename Container, typename Type = typename Container::value_type>
    auto series_base(Container series) -> Type {
        return series_base(series.begin(), series.end());
    }

    template <typename ExceptionType>
    auto throws(Isolate *isolate, ExceptionType type, std::string message) -> void {
        auto msg = String::NewFromUtf8(isolate, message.data(), NewStringType::kNormal);
        isolate->ThrowException(type(msg.ToLocalChecked()));
    }

    template <typename V8Type, typename CType>
    auto get_number(Local<Value> const &arg) -> Maybe<CType> {
        if (arg->IsNumber()) {
            return Just(static_cast<CType>(arg.As<V8Type>()->Value()));
        }
        return Nothing<CType>();
    }

    auto get_vector(Isolate *isolate, Local<Value> const &arg) -> Maybe<Series>;
}
