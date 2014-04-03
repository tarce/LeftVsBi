/*
 * Queue.h
 *
 *  Created on: Apr 3, 2014
 *      Author: terek
 */

#ifndef QUEUE_H_
#define QUEUE_H_

#include <sstream>

#include "myExceptions.h"

using namespace std;

//circular queue based on array
//much of the code came from undergrad project
template<class T>
class Queue
{
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

template<class T>
Queue<T>::Queue(int initialCapacity) {
	if (initialCapacity < 1){
		ostringstream s;
		s << "Initial capacity = " << initialCapacity << " Must be > 0";
		throw illegalParameterValue(s.str());
	}
	arrayLength = initialCapacity;
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
	if (theFront == theBack)
		throw queueEmpty();
	return queue[(theFront + 1) % arrayLength];
}

template<class T>
void Queue<T>::pop() {
	if (theFront == theBack)
		throw queueEmpty();
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
