/*
 * Random.h
 *
 *  Created on: Apr 8, 2014
 *      Author: terek
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//permutes and returns an array of elements
template <class T>
bool random_permutation(T * &a, int n){
	int index;
	T temp;

	a = new T [n];
	a[0] = 0;									//special case for array to be initialized

	//create numbers
	for (int i = 1; i < n; i++){a[i]=i-1;}
	srand(time(NULL));

	//swap numbers at random indices
	for (int i = 1; i < n; i++){
		index = rand() % (n-1) + 1;
		temp = a[index];
		a[index] = a[i];
		a[i] = temp;
	}
	return true;
}

//creates an array of random insert and delete operations
template <class T>
bool random_ops(T * &a, int n){

	a = new T [n];
	srand (time(NULL));

	for (int i = 0; i < n; i++){
		int op = rand() % 2;		// compute a radom 0/1
		if (op == 1) {a[i] = -1;}				// delete op
		else {
			int num = rand() % n;
			a[i] = num;							//insert op
		}
	}
	return true;
}





#endif /* RANDOM_H_ */
