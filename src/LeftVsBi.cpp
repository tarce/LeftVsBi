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
#include "Queue.h"
#include "MinHBLT.h"
#include "BinomialHeap.h"
#include "Random.h"

int main(int argc, char *argv[], char *envp[]) {

	string file;
	ifstream myfile;
	string arg = argv[1];
	MinHBLT<int> leftistTree;
	BinomialHeap<int> heap (14); // Note that the default constructor set to 14.

	if (arg == "-il") {
		cout << "Executing leftist tree mode..." << endl;
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
		leftistTree.print();
	}

	else if (arg == "-ib") {
		cout << "Executing binomial heap mode..." << endl;
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
		heap.print();
	}

	//random mode selected
	else if (arg == "-r") {
		cout << "Executing random mode..." << endl;
		int * init;
		int * ops;
		int n = 50;
		cout << "Creating timers" << endl;
		clock_t Start, Time;
		cout << "Exiting timers" << endl;
		float sumLeft = 0.0;
		cout << "sumLeft" << endl;
		float sumBinomial = 0.0;
		cout << "sumBi" << endl;
		//run 5 tests at n = 100
		for (int testing = 0; testing < 5; testing++){
			cout << "starting test " << testing << endl;;
			random_ops(ops, n);							//generate random operations sequence
			random_permutation(init, n+1);				//generate random initialization sequence.  Note +1 is required due to implemetation
			MinHBLT<int> leftistTree;					//create and initialize leftist tree
			leftistTree.initialize(init, n);			//note that first element is 0, so there are 2 0s in the array

			//Timed portion of inserts and deletes STARTS HERE (LEFTIST TREE)
			Start = clock();
			for (int i = 0; i < n; i++) {
				int op = ops[i];						//grab op
				if (op == -1) {
					try {
						leftistTree.pop();
					}
					catch (Exception& e) {
						continue;
					}
				}		//if delete then pop
				else {leftistTree.push(op);}			//if insert then push
			}
			Time = clock() - Start;
			//Timed portion ENDS HERE

			sumLeft += (((float)Time)/CLOCKS_PER_SEC);	//running sum in milli seconds for leftist tree

			BinomialHeap<int> binomialHeap;			//create and initialize binomial heap
			for (int i = 0; i < n; i++) {binomialHeap.push(init[i]);}

			//Timed portion of inserts and deletes STARTS HERE (BINOMIAL HEAP)
			Start = clock();
			for (int i = 0; i < n; i++) {
				cout << "inf?" << i << endl;
				int op = ops[i];
				if (op == -1) {
					cout << "Last op was -1" << endl;
					try {
						binomialHeap.removeMin();
					}
					catch (Exception& e) {
						continue;
					}
				}
				else {binomialHeap.push(op);}
			}
			Time = clock() - Start;
			//Timed portion ENDS HERE

			sumBinomial += (((float)Time)/CLOCKS_PER_SEC);
		}

		//Output results of run
		cout << "Run of: " << n << endl;
		cout << "Binomial: " << sumBinomial/5.0 << endl;
		cout << "Leftist: " << sumLeft/5.0 << endl;
	}
//
//		//from this point on the code repeats for different values of n									//TODO: make func for reps
//		n = 500;
//		for (int testing = 0; testing < 5; testing++){
//			random_ops(ops, n);
//			random_permutation(init, n+1);
//			MinHBLT<int> leftistTree;
//			leftistTree.initialize(init, n);
//			Start = clock();
//			for (int i = 0; i < n; i++) {
//				int op = ops[i];
//				if (op == -1) {
//					try {
//						leftistTree.pop();
//					}
//					catch (Exception& e) {
//						continue;
//					}
//				}
//				else {leftistTree.push(op);}
//			}
//			Time = clock() - Start;
//			sumLeft += (((float)Time)/CLOCKS_PER_SEC);
//			BinomialHeap<int> binomialHeap;
//			for (int i = 0; i < n; i++) {binomialHeap.push(init[i]);}
//			Start = clock();
//			for (int i = 0; i < n; i++) {
//				int op = ops[i];
//				if (op == -1) {
//					try {
//					binomialHeap.removeMin();
//					}
//					catch (Exception& e) {
//						continue;
//					}
//				}
//				else {binomialHeap.push(op);}
//			}
//			Time = clock() - Start;
//			sumBinomial += (((float)Time)/CLOCKS_PER_SEC);
//		}
//		cout << "Run of: " << n << endl;
//		cout << "Binomial: " << sumBinomial/5.0 << endl;
//		cout << "Leftist: " << sumLeft/5.0 << endl;
//
//		n = 1000;
//		for (int testing = 0; testing < 5; testing++){
//			random_ops(ops, n);
//			random_permutation(init, n+1);
//			MinHBLT<int> leftistTree;
//			leftistTree.initialize(init, n);
//			Start = clock();
//			for (int i = 0; i < n; i++) {
//				int op = ops[i];
//				if (op == -1) {
//					try {
//						leftistTree.pop();
//					}
//					catch (Exception& e) {
//						continue;
//					}
//				}
//				else {leftistTree.push(op);}
//			}
//			Time = clock() - Start;
//			sumLeft += (((float)Time)/CLOCKS_PER_SEC);
//			BinomialHeap<int> binomialHeap;
//			for (int i = 0; i < n; i++) {binomialHeap.push(init[i]);}
//			Start = clock();
//			for (int i = 0; i < n; i++) {
//				int op = ops[i];
//				if (op == -1) {
//					try {
//					binomialHeap.removeMin();
//					}
//					catch (Exception& e) {
//						continue;
//					}
//				}
//				else {binomialHeap.push(op);
//				}
//			}
//			Time = clock() - Start;
//			sumBinomial += (((float)Time)/CLOCKS_PER_SEC);
//		}
//		cout << "Run of: " << n << endl;
//		cout << "Binomial: " << sumBinomial/5.0 << endl;
//		cout << "Leftist: " << sumLeft/5.0 << endl;
//
//		n = 2000;
//		for (int testing = 0; testing < 5; testing++){
//			random_ops(ops, n);
//			random_permutation(init, n+1);
//			MinHBLT<int> leftistTree;
//			leftistTree.initialize(init, n);
//			Start = clock();
//			for (int i = 0; i < n; i++) {
//				int op = ops[i];
//				if (op == -1) {
//					try {
//						leftistTree.pop();
//					}
//					catch (Exception& e) {
//						continue;
//					}
//				}
//				else {leftistTree.push(op);}
//			}
//			Time = clock() - Start;
//			sumLeft += (((float)Time)/CLOCKS_PER_SEC);
//			BinomialHeap<int> binomialHeap;
//			for (int i = 0; i < n; i++) {binomialHeap.push(init[i]);}
//			Start = clock();
//			for (int i = 0; i < n; i++) {
//				int op = ops[i];
//				if (op == -1) {
//					try {
//					binomialHeap.removeMin();
//					}
//					catch (Exception& e) {
//						continue;
//					}
//				}
//				else {binomialHeap.push(op);}
//			}
//			Time = clock() - Start;
//			sumBinomial += (((float)Time)/CLOCKS_PER_SEC);
//		}
//		cout << "Run of: " << n << endl;
//		cout << "Binomial: " << sumBinomial/5.0 << endl;
//		cout << "Leftist: " << sumLeft/5.0 << endl;
//
//		n = 3000;
//		for (int testing = 0; testing < 5; testing++){
//			random_ops(ops, n);
//			random_permutation(init, n+1);
//			MinHBLT<int> leftistTree;
//			leftistTree.initialize(init, n);
//			Start = clock();
//			for (int i = 0; i < n; i++) {
//				int op = ops[i];
//				if (op == -1) {
//					try {
//						leftistTree.pop();
//					}
//					catch (Exception& e) {
//						continue;
//					}
//				}
//				else {leftistTree.push(op);}
//			}
//			Time = clock() - Start;
//			sumLeft += (((float)Time)/CLOCKS_PER_SEC);
//			BinomialHeap<int> binomialHeap;
//			for (int i = 0; i < n; i++) {binomialHeap.push(init[i]);}
//			Start = clock();
//			for (int i = 0; i < n; i++) {
//				int op = ops[i];
//				if (op == -1) {
//					try {
//					binomialHeap.removeMin();
//					}
//					catch (Exception& e) {
//						continue;
//					}
//				}
//				else {binomialHeap.push(op);}
//			}
//			Time = clock() - Start;
//			sumBinomial += (((float)Time)/CLOCKS_PER_SEC);
//		}
//		cout << "Run of: " << n << endl;
//		cout << "Binomial: " << sumBinomial/5.0 << endl;
//		cout << "Leftist: " << sumLeft/5.0 << endl;
//
//		n = 4000;
//		for (int testing = 0; testing < 5; testing++){
//			random_ops(ops, n);
//			random_permutation(init, n+1);
//			MinHBLT<int> leftistTree;
//			leftistTree.initialize(init, n);
//			Start = clock();
//			for (int i = 0; i < n; i++) {
//				int op = ops[i];
//				if (op == -1) {
//					try {
//						leftistTree.pop();
//					}
//					catch (Exception& e) {
//						continue;
//					}
//				}
//				else {leftistTree.push(op);}
//			}
//			Time = clock() - Start;
//			sumLeft += (((float)Time)/CLOCKS_PER_SEC);
//			BinomialHeap<int> binomialHeap;
//			for (int i = 0; i < n; i++) {binomialHeap.push(init[i]);}
//			Start = clock();
//			for (int i = 0; i < n; i++) {
//				int op = ops[i];
//				if (op == -1) {
//					try {
//					binomialHeap.removeMin();
//					}
//					catch (Exception& e) {
//						continue;
//					}
//				}
//				else {binomialHeap.push(op);}
//			}
//			Time = clock() - Start;
//			sumBinomial += (((float)Time)/CLOCKS_PER_SEC);
//		}
//		cout << "Run of: " << n << endl;
//		cout << "Binomial: " << sumBinomial/5.0 << endl;
//		cout << "Leftist: " << sumLeft/5.0 << endl;
//
//		n = 5000;
//		for (int testing = 0; testing < 5; testing++){
//			random_ops(ops, n);
//			random_permutation(init, n+1);
//			MinHBLT<int> leftistTree;
//			leftistTree.initialize(init, n);
//			Start = clock();
//			for (int i = 0; i < n; i++) {
//				int op = ops[i];
//				if (op == -1) {
//					try {
//						leftistTree.pop();
//					}
//					catch (Exception& e) {
//						continue;
//					}
//				}
//				else {leftistTree.push(op);}
//			}
//			Time = clock() - Start;
//			sumLeft += (((float)Time)/CLOCKS_PER_SEC);
//			BinomialHeap<int> binomialHeap;
//			for (int i = 0; i < n; i++) {binomialHeap.push(init[i]);}
//			Start = clock();
//			for (int i = 0; i < n; i++) {
//				int op = ops[i];
//				if (op == -1) {
//					try {
//					binomialHeap.removeMin();
//					}
//					catch (Exception& e) {
//						continue;
//					}
//				}
//				else {binomialHeap.push(op);}
//			}
//			Time = clock() - Start;
//			sumBinomial += (((float)Time)/CLOCKS_PER_SEC);
//		}
//		cout << "Run of: " << n << endl;
//		cout << "Binomial: " << sumBinomial/5.0 << endl;
//		cout << "Leftist: " << sumLeft/5.0 << endl;
//	}
//	else {cout << "Invalid command" << endl;}

	myfile.close();
	return 0;
}
