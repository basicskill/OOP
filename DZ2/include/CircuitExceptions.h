#ifndef _EXCEPTIONS_H_
#define _EXCEPTIONS_H_

#include <exception>
#include <iostream>
#include <string.h>
using namespace std;

class CircuitException : public exception {
    public:
    CircuitException(const char* msg) : exception(), msg_(msg) {};
    const char * what () const throw () {
        return msg_;
    }
    private:
        const char* msg_;
};

#endif // !_EXCEPTIONS_H_
