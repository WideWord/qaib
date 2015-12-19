#pragma once

#include <string>

namespace qaib {

	class Exception {
	private:
		std::string _message;
		std::string _file;
		int _line;
	public:
		Exception(const std::string& message, const char* file, int line);
		virtual ~Exception();

		std::string prettyMessage();
	};

#define qaibExceptionDecl(Name, Message, Parent) class Name: Parent { public: Name(const std::string& message, const char* file, int line) : Parent(std::string(Message) + message, file, line) {} };
#define qaibRaise(Name) throw Name("", __FILE__, __LINE__)
}