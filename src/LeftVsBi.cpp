//============================================================================
// Name        : LeftVsBi.cpp
// Author      : Terek Arce
// Version     : 1.0
// Created     : Apr 3, 2014
// Copyright   : See MIT Liscence
// Description : LeftVsBi, a timing of min leftist tree Vs binomial heap
//============================================================================

#include <iostream>
#include "Queue.h"
#include "MinHBLT.h"

using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	try {
		Queue<int> q (1);
		q.push(1);
		int result = q.front();
		cout << result;
	}
	catch (Exception& e){
		cout << "Exception caught: ";
		e.outputMessage() ;
	}

}
