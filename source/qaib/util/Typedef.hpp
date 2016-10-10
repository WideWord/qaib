#pragma once

#include <memory>

namespace qaib {

    template<typename T> using Ref = std::shared_ptr<T>;
    template<typename T> using WRef = std::weak_ptr<T>;

    template<typename T, typename R> inline Ref<T> RefCast(const Ref<R>& ref) { return std::move(std::static_pointer_cast<T>(ref)); };

}