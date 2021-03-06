#include "InputStreamException.h"

const char* XML_VERSION_STR = "XojStrm1:";

InputStreamException::InputStreamException(string message, string filename, int line)
{
	XOJ_INIT_TYPE(InputStreamException);
	
	this->message = message + ", " + filename + ": " + std::to_string(line);
}

InputStreamException::~InputStreamException() throw ()
{
	XOJ_RELEASE_TYPE(InputStreamException);
}

const char* InputStreamException::what() const throw ()
{
	return this->message.c_str();
}
