#ifndef UNDEFINED_EX
#define UNDEFINED_EX

#include <exception>
using namespace std;

class Undefined_exception : public exception
{
	virtual const char* what() const throw()
	{
		return "Undefined";
	}
} udex;

#endif // !UNDEFINED_EX