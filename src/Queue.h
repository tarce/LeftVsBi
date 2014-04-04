//============================================================================
// Name        : Queue.h
// Author      : Terek Arce
// Version     : 1.0
// Created     : Apr 3, 2014
// Copyright   : See MIT Liscence
// Description : Queue, a simple queue based off of a circular buffer.
//============================================================================


#ifndef QUEUE_H_
#define QUEUE_H_

#include <sstream>
#include "Exception.h"

using namespace std;

/*
 * Queue definition.
 *
 * See http://en.wikipedia.org/wiki/Circular_buffer#How_it_works
 * for a circular buffer works.
 *
 * A small addition here is that upon filling up, the buffer size doubles.
 */
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
	int start;
	int end;
	int length;
	T *queue;
};

/*
 * Constructs a queue.  The default initial capacity is 10.
 * Throws illegalParameter for initial capacities less than 1.
 */
template<class T>
Queue<T>::Queue(int capacity) {
	if (capacity < 1){
		ostringstream error;
		error << "capacity set to " << capacity << "; must be > 0.";
		throw Exception(error.str());
	}
	start = 0;
	end = 0;
	length = capacity;
	queue = new T[length];
}

/*
 * Destructor.
 */
template<class T>
Queue<T>::~Queue() {
	delete [] queue;
}

/*
 * Returns whether or not the queue is empty.
 */
template<class T>
bool Queue<T>::empty() const {
	return start == end;
}

/*
 * Returns the first element in the queue.
 */
template<class T>
T& Queue<T>::front() {
	if (empty()) {
		ostringstream error;
		error << "tried to front() from empty queue.";
		throw Exception(error.str());
	}
	int pos = (start + 1) % length;
	return queue[pos];
}

/*
 * Removes the first element in the queue.
 */
template<class T>
void Queue<T>::pop() {
	if (empty()) {
		ostringstream error;
		error << "tried to pop() from empty queue.";
		throw Exception(error.str());
	}
	start = (start + 1) % length;
	queue[start].~T();
}

/*
 * Pushes and element into the queue.
 */
template<class T>
void Queue<T>::push(const T& theElement) {

	// Double the queue size if full
	if ((end + 1) % length == start) {

		// create new queue of double the size
		T* newQueue = new T[2 * length];

		// find the first position holding data (aka the front), which
		// is one position after the start pointer.
		int front = (start + 1) % length;

		// see http://www.cplusplus.com/reference/algorithm/copy/ for copy definition
		// if the front is 1 or 0, then copy the whole thing into the new queue
		if (front < 2) {
			copy(queue + front, queue + front + length - 1, newQueue);
		}
		// otherwise, copy the elements starting at front into the queue,
		// and then the elements before front into the queue to keep
		// things in order.
		else {
			copy(queue + front, queue + length, newQueue);
			copy(queue, queue + end + 1, newQueue + length - front);
		}

		// set correct values for start, end, length and queue
		start = 2 * length - 1;
		end = length - 2;
		length *= 2;
		queue = newQueue;
	}

	// push the element into position
	end = (end + 1) % length;
	queue[end] = theElement;
}



#endif /* QUEUE_H_ */
