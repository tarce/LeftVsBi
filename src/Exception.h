//============================================================================
// Name        : Exceptions.h
// Author      : Terek Arce
// Version     : 1.0
// Created     : Apr 3, 2014
// Copyright   : See MIT Liscence
// Description : Defines various exceptions that might be thrown.
//============================================================================


#ifndef EXCEPTION_H_
#define EXCEPTION_H_

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

/*
 * Sets the message of the exception.
 * The message should be defined in the code throwing the exception.
 */
Exception::Exception(string theMessage) {
	message = theMessage;
}

/*
 * Outputs the error message of the exception.
 */
void Exception::outputMessage() {
	cout << message << endl;
}

#endif /* EXCEPTION_H_ */
