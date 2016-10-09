#pragma once

#include <string>
#include <sstream>

namespace qaib {

    class MakeString {
    public:
        template<class T>
        inline MakeString& operator<< (const T& arg) {
            m_stream << arg;
            return *this;
        }
        inline operator std::string() const {
            return m_stream.str();
        }
    protected:
        std::stringstream m_stream;
    };

}