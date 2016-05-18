#pragma once

#include <memory>

namespace qaib {

    template<typename T> using Ref = std::shared_ptr<T>;
    template<typename T> using WRef = std::weak_ptr<T>;

}