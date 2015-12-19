#include <qaib/util/Exception.hpp>

#include <sstream>

namespace qaib {

	Exception::Exception(const std::string& message, const char* file, int line) {
		_message = message;
		_file = file;
		_line = line;
	}

	Exception::~Exception() {}

	std::string Exception::prettyMessage() {
		std::stringstream ss;
		ss << _file << ":" << _line << " " << _message;
		return ss.str();
	}

}