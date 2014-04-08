/*
 * BinomialHeap.h
 *
 *  Created on: Apr 5, 2014
 *      Author: terek
 */

#ifndef BINOMIALHEAP_H_
#define BINOMIALHEAP_H_

#include <iostream>
#include "Queue.h"
#include "BinomialHeapNode.h"

template<class T>
class BinomialHeap {
public:
	BinomialHeapNode<T> * min;

	BinomialHeap();
	~BinomialHeap();
	void push(const T&);
	const T& removeMin();
	void print();
	void levelOrderOutput();
	void levelOrder(void(*)(BinomialHeapNode<T> *));


protected:
	BinomialHeapNode<T> * meld(BinomialHeapNode<T> * &, BinomialHeapNode<T> * &);
	BinomialHeapNode<T> * pairWiseCombine(BinomialHeapNode<T> *);
	static void (*visit)(BinomialHeapNode<T> *);
	static void printElement(BinomialHeapNode<T> *);
};

template <class T>
void (*BinomialHeap<T>::visit)(BinomialHeapNode<T> *);

template<class T>
BinomialHeap<T>::BinomialHeap() {
	min = NULL;
}

template<class T>
BinomialHeap<T>::~BinomialHeap() {
	//TODO:
}

template<class T>
void BinomialHeap<T>::push(const T& element) {

	BinomialHeapNode<T> *new_node = new BinomialHeapNode<T> (element);

	//if heap is empty add node, otherwise add to top level list
	if (min == NULL) {
		min = new_node;
		new_node->sibling = new_node;
	}
	else {
		BinomialHeapNode<T> *temp = min->sibling;
		min->sibling = new_node;
		new_node->sibling = temp;
		if (min->element > new_node->element) {min = new_node;}
	}
}

//melds 2 top level lists, returnin min (assumes min are coming in)
template<class T>
BinomialHeapNode<T> * BinomialHeap<T>::meld(BinomialHeapNode<T> * &min1, BinomialHeapNode<T> * &min2) {
	BinomialHeapNode<T> *temp = min1->sibling;
	min1->sibling = min2->sibling;
	min2->sibling = temp;
	if (min1->element < min2->element) {return min1;}
	else {return min2;}
}

//remove min from binomial heap
template <class T>
const T& BinomialHeap<T>::removeMin() {

	if (min == NULL) {
		ostringstream error;
		error << "tried to removeMin() from empty tree.";
		throw Exception(error.str());
	}

	T minValue = min->element;
	BinomialHeapNode<T> *tempChild = min->child;

	//need to create binomialHeaps and add to top level list
	if (tempChild != NULL) {
		BinomialHeapNode<T> *start = tempChild;
		BinomialHeapNode<T> *curSmallest = tempChild;

		while (tempChild->sibling != start) {
			//find smallest element in child list
			if (tempChild->sibling->element < curSmallest->element) {curSmallest = tempChild->sibling;}
			tempChild = tempChild->sibling;
		}

		//set child to be the min of new top level list;
		tempChild = curSmallest;

		//do copy back trick and meld
		if (min != min->sibling) {
			min->copy(min->sibling);
			min = meld(min, tempChild);
			min = pairWiseCombine(min);
		}
		else {
			min = tempChild;
			min = pairWiseCombine(min);
		}
	}
	//only top level circular list
	else {
		if (min != min->sibling) {
			min->copy(min->sibling);
			min = pairWiseCombine(min);
		}
		else {cout << "Warning: Binomial heap is now empty!" << endl;}
	}

	return minValue;
}

//performs pairwise combine of binomial heaps
template <class T>
BinomialHeapNode<T> * BinomialHeap<T>::pairWiseCombine(BinomialHeapNode<T> *node)
{
	BinomialHeapNode<T> *start = node;
	int maxDegree = 14;						//log(5000) = 13 which is max + 1 for safety

	BinomialHeapNode<T> ** pairTable;
	pairTable = new BinomialHeapNode<T> * [maxDegree];
	for (int i = 0; i < maxDegree; i++) {pairTable[i] = NULL;}

	//break circular list
	while (start->sibling != node) {start = start->sibling;}
	start->sibling = NULL;

	start = node;
	BinomialHeapNode<T> * notInserted = start;

	while (notInserted != NULL) {
		start = notInserted;

		if (notInserted->sibling != NULL) {
			BinomialHeapNode<T> * temp = notInserted;
			notInserted = notInserted->sibling;
			temp->sibling = NULL;
		}
		else {notInserted = NULL;}

		int degree = start->degree;

		//now check to see if table has entry
		if (pairTable[degree] == NULL) { pairTable[degree] = start;}
		else { //need to combine
			while(true) {
				//grab node that is in table
				BinomialHeapNode<T> *h1 = pairTable[degree];
				pairTable[degree] = NULL;

				if (h1->element < start->element) {
					//perform appropriate insertiong into child list
					if(h1->child == NULL) {
						h1->child = start;
						start->sibling = start;
						h1->degree = 1;
					}
					else {
						BinomialHeapNode<T> *secondChild = h1->child->sibling;
						h1->child->sibling = start;
						start->sibling = secondChild;
						h1->degree = (h1->degree) + 1;
					}

					//need to check if new heap still needs pairwise combining
					start = h1;
					degree = start->degree;
					if (pairTable[degree] == NULL) {  //no updated needed
						pairTable[degree] = start;
						break;
					}
					else {continue;} //keep going
				}
				else {
					//perform appropriate insertiong into child list
					if(start->child == NULL) {
						start->child = h1;
						h1->sibling = h1;
						start->degree = 1;
					}
					else {
						BinomialHeapNode<T> *secondChild = start->child->sibling;
						start->child->sibling = h1;
						h1->sibling = secondChild;
						start->degree = (start->degree) + 1;
					}

					degree = start->degree;

					if (pairTable[degree] == NULL) {  //no updated needed
						pairTable[degree] = start;
						break;
					}
					else {continue;} //keep going
				}
			}
		}
	}

	start = NULL;							//reference start
	BinomialHeapNode<T> * tempMin = NULL;	//iterate through
	BinomialHeapNode<T> * temp = NULL;		//will store min

	for (int i = 0; i < maxDegree; i++) {
		if (pairTable[i] != NULL) {
			if (start == NULL) {
				start = tempMin = temp = pairTable[i];
				pairTable[i] = NULL;
			}
			else {
				BinomialHeapNode<T> * temp2 = pairTable[i];
				if (temp2->element < tempMin->element) { tempMin = temp2;}
				start->sibling = temp2;
				start = start->sibling;
			}
		}
	}

	start->sibling = temp ; //complete circular list

	for (int i = 0; i < maxDegree; i++) {
		pairTable[i] = NULL;
	}

	return tempMin;
}

template<class T>
void BinomialHeap<T>::levelOrderOutput() {

	Queue<BinomialHeapNode<T>*> parents;
	Queue<BinomialHeapNode<T>*> children;
	BinomialHeapNode<T> * start;

	//push min and min's siblings on the parents queue
	parents.push(min);
	start = min->sibling;
	while (start != min) {
		parents.push(start);
		start = start->sibling;
	}

	while(!parents.empty()) {

		//remove parents from queue, printing them and adding their children to children queue
		while (!parents.empty()){
			BinomialHeapNode<T> * temp = parents.front();
			if (temp->child != NULL) {
				BinomialHeapNode<T> * childStart = temp->child->sibling;
				children.push(temp->child);
				while (childStart != temp->child) {
					children.push(childStart);
					childStart = childStart->sibling;
				}
			}
			//theVisit(temp);
			cout << temp->element << " ";
			parents.pop();
		}
		cout << endl;
		//at this point parents is empty
		//push children onto parents
		while (!children.empty()) {
			parents.push(children.front());
			children.pop();
		}
	}
}

template<class T>
void BinomialHeap<T>::levelOrder(void(*theVisit)(BinomialHeapNode<T> *)) {

	Queue<BinomialHeapNode<T>*> parents;
	Queue<BinomialHeapNode<T>*> children;
	BinomialHeapNode<T> * start;

	//push min and min's siblings on the parents queue
	parents.push(min);
	start = min->sibling;
	while (start != min) {
		parents.push(start);
		start = start->sibling;
	}

	while(!parents.empty()) {

		//remove parents from queue, printing them and adding their children to children queue
		while (!parents.empty()){
			BinomialHeapNode<T> * temp = parents.front();
			if (temp->child != NULL) {
				BinomialHeapNode<T> * childStart = temp->child->sibling;
				children.push(temp->child);
				while (childStart != temp->child) {
					children.push(childStart);
					childStart = childStart->sibling;
				}
			}
			theVisit(temp);
			//cout << temp->element << " ";
			parents.pop();
		}
		cout << endl;
		//at this point parents is empty
		//push children onto parents
		while (!children.empty()) {
			parents.push(children.front());
			children.pop();
		}
	}
}

template <class T>
void BinomialHeap<T>::print() {
	levelOrder(printElement);
//	cout << endl;		//TODO: is this necessary?
}

template <class T>
void BinomialHeap<T>::printElement(BinomialHeapNode<T> *t) {
	cout << t->element << ' ';
}

#endif /* BINOMIALHEAP_H_ */
