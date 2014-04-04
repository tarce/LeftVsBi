//============================================================================
// Name        : Queue.h
// Author      : Terek Arce
// Version     : 1.0
// Created     : Apr 3, 2014
// Copyright   : See MIT Liscence
// Description : Queue, a simple circular queue founded on an array.
//============================================================================


#ifndef QUEUE_H_
#define QUEUE_H_

#include <sstream>
#include "Exceptions.h"

using namespace std;

template<class T>
class Queue {

public:
	Queue(int initialCapacity = 10);
	~Queue();
	bool empty() const;
	T& front();
	void pop();
	void push(const T& theElement);

private:
	int theFront;
	int theBack;
	int arrayLength;
	T *queue;
};

/*
 * Constructs a queue.  The default initial capacity is 10.
 * Throws illegalParameter for initial capacities less than 1.
 *
 */
template<class T>
Queue<T>::Queue(int capacity) {
	if (capacity < 1){
		ostringstream error;
		error << "capacity set to " << capacity << "; must be > 0.";
		throw Exception(error.str());
	}
	arrayLength = capacity;
	queue = new T[arrayLength];
	theFront = 0;
	theBack = 0;
}

template<class T>
Queue<T>::~Queue() {
	delete [] queue;
}

template<class T>
bool Queue<T>::empty() const {
	return theFront == theBack;
}

template<class T>
T& Queue<T>::front() {
	if (empty()) {
		ostringstream error;
		error << "tried to front() from empty queue.";
		throw Exception(error.str());
	}
	return queue[(theFront + 1) % arrayLength];
}

template<class T>
void Queue<T>::pop() {
	if (empty()) {
		ostringstream error;
		error << "tried to pop() from empty queue.";
		throw Exception(error.str());
	}
	theFront = (theFront + 1) % arrayLength;
	queue[theFront].~T();
}

template<class T>
void Queue<T>::push(const T& theElement) {
	if ((theBack + 1) % arrayLength == theFront) {
		T* newQueue = new T[2 * arrayLength];
		int start = (theFront + 1) % arrayLength;

		if (start < 2) {copy(queue + start, queue + start + arrayLength - 1, newQueue);}
		else {
			copy(queue + start, queue + arrayLength, newQueue);
			copy(queue, queue + theBack + 1, newQueue + arrayLength - start);
		}
		theFront = 2 * arrayLength - 1;
		theBack = arrayLength - 2;
		arrayLength *= 2;
		queue = newQueue;
	}
	theBack = (theBack + 1) % arrayLength;
	queue[theBack] = theElement;
}



#endif /* QUEUE_H_ */
