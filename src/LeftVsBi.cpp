//============================================================================
// Name        : LeftVsBi.cpp
// Author      : Terek Arce
// Version     : 1.0
// Created     : Apr 3, 2014
// Copyright   : See MIT Liscence
// Description : LeftVsBi, a timing of min leftist tree Vs binomial heap
//============================================================================

#include <iostream>
#include <fstream>
//#include <sstream>
//#include <string>
//#include <time.h>
#include "Queue.h"
#include "MinHBLT.h"
#include "BinomialHeap.h"

//using namespace std;

int main(int argc, char *argv[], char *envp[]) {

	string file;
	ifstream myfile;
	string arg = argv[1];
	MinHBLT<int> leftistTree;
	BinomialHeap<int> heap (14); // Note that the default constructor set to 14.

	if (arg == "-il") {
		file = argv[2];
		myfile.open(file.c_str());
		bool start = true;
		while (myfile.is_open() && myfile.good()) {

			string line;
			getline (myfile,line);
			istringstream first_line(line);
			string first_char;
			first_line >> first_char;
			if (first_char == "I" && start) {
				int key;
				first_line >> key;
				int init[2] = {0, key};
				leftistTree.initialize(init, 1);
				start = false;
			}
			else if (first_char == "I"){
				int key;
				first_line >> key;
				leftistTree.push(key);
			}
			else if (first_char == "D") {
				try {leftistTree.pop();}
				catch (Exception& e) {
					//e.outputMessage();
				}
			}
			else {break;}
		}
		//print final tree
		leftistTree.print();
	}

	else if (arg == "-ib") {
		file = argv[2];
		myfile.open(file.c_str());
		bool start = true;
		while (myfile.is_open() && myfile.good()) {

			string line;
			getline (myfile,line);
			istringstream first_line(line);
			string first_char;
			first_line >> first_char;

			if (first_char == "I") {
				int key;
				first_line >> key;
				heap.push(key);
			}
			else if (first_char == "D") {
				try {heap.removeMin();}
				catch (Exception& e) {
					//e.outputMessage();
				};
			}
			else {break;}
		}
		//print final heap
		heap.print();
	}
	myfile.close();
}
