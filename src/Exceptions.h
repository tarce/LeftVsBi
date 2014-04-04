//============================================================================
// Name        : Exceptions.h
// Author      : Terek Arce
// Version     : 1.0
// Created     : Apr 3, 2014
// Copyright   : See MIT Liscence
// Description : Defines various exceptions that might be thrown.
//============================================================================


#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <string>
#include <iostream>

using namespace std;

/*
 * Illegal parameter exceptions that might be thrown.
 */
class Exception {

public:
	Exception(string);
	void outputMessage();

private:
	string message;
};

Exception::Exception(string theMessage) {
	message = theMessage;
}

void Exception::outputMessage() {
	cout << message << endl;
}

#endif /* EXCEPTIONS_H_ */
