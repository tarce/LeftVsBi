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
	int maxDegree;

	BinomialHeap();
	BinomialHeap(int);
	~BinomialHeap();
	void push(const T&);
	void removeMin();
	void print();
	void levelOrder(void(*)(BinomialHeapNode<T> *));

protected:
	void meld(BinomialHeapNode<T> * &);
	void pairWiseCombine();
	static void (*visit)(BinomialHeapNode<T> *);
	static void printElement(BinomialHeapNode<T> *);
};

template <class T>
void (*BinomialHeap<T>::visit)(BinomialHeapNode<T> *);

/*
 * Constructors follow.
 */
template<class T>
BinomialHeap<T>::BinomialHeap() {
	// log(5000) = 13 which is max + 1 for safety.
	// if you want to set your own degree see overloaded constructor.
	maxDegree = 14;
	min = NULL;
}

template<class T>
BinomialHeap<T>::BinomialHeap(int theMaxDegree) {
	maxDegree = theMaxDegree;
	min = NULL;
}

/*
 * Destructor.
 */
template<class T>
BinomialHeap<T>::~BinomialHeap() {
	//TODO:
}

/*
 * Pushes an element into the binomial heap (top level list).
 * Also determines new min if necessary.
 */
template<class T>
void BinomialHeap<T>::push(const T& element) {

	BinomialHeapNode<T> *new_node = new BinomialHeapNode<T> (element);

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

/*
 * Removes the minimum from the binomial heap.
 * This operation melds and combines the trees in to one tree.
 */
template <class T>
void BinomialHeap<T>::removeMin() {

	if (min == NULL) {
		ostringstream error;
		error << "tried to removeMin() from empty tree.";
		throw Exception(error.str());
	}

	BinomialHeapNode<T> *tempChild = min->child;

	// case where min has children
	if (tempChild != NULL) {

		// find the smallest child
		BinomialHeapNode<T> *start = tempChild;
		BinomialHeapNode<T> *curSmallest = tempChild;
		while (tempChild->sibling != start) {
			//find smallest element in child list
			if (tempChild->sibling->element < curSmallest->element) {
				curSmallest = tempChild->sibling;
			}
			tempChild = tempChild->sibling;
		}

		// meld the new tree with the other top level trees and combine
		if (min != min->sibling) {
			min->copy(min->sibling); //copy back trick
			meld(curSmallest);
			pairWiseCombine();
		}
		// only one top level, so combine the new top level trees
		else {
			min = curSmallest;
			pairWiseCombine();
		}
	}

	// case where min has no children (only top level list)
	else {
		// only one top level, so combine the new top level trees
		if (min != min->sibling) {
			min->copy(min->sibling);
			pairWiseCombine();
		}
		// no tree is left so set min back to null
		else {
			min = NULL;
		}
	}
}

/*
 * Melds a new tree with the current top level list pointed to by min.
 * Also determines a new min if necessary.
 */
template<class T>
void BinomialHeap<T>::meld(BinomialHeapNode<T> * &newTree) {

	// combine lists
	BinomialHeapNode<T> *temp = min->sibling;
	min->sibling = newTree->sibling;
	newTree->sibling = temp;

	// determine new min
	if (min->element >= newTree->element) {
		min = newTree;
	}
}

/*
 * Perform a pairwise combine of the binomial heap's trees.
 */
template <class T>
void BinomialHeap<T>::pairWiseCombine()
{
	// initialize a table to hold pairs to be combined
	BinomialHeapNode<T> ** pairTable;
	pairTable = new BinomialHeapNode<T> * [maxDegree];
	for (int i = 0; i < maxDegree; i++) {pairTable[i] = NULL;}

	// break circular list
	BinomialHeapNode<T> *b4min = min;
	while (b4min->sibling != min) {b4min = b4min->sibling;}
	b4min->sibling = NULL;

	// run through each not inserted tree and combine if needed
	BinomialHeapNode<T> * notInserted = min;
	while (notInserted != NULL) {

		BinomialHeapNode<T> * curTree = notInserted;
		int degree = curTree->degree;

		// if a tree of this degree not in table, add it to the table
		if (pairTable[degree] == NULL) { pairTable[degree] = curTree;}

		// otherwise, combine with the tree(s) in the table
		else {

			// continue combining until a tree whose degree
			// is not in the table is formed
			bool done = false;
			while(!done) {

				// get the tree from the table
				BinomialHeapNode<T> *tableTree = pairTable[degree];
				pairTable[degree] = NULL;

				// determine who is the root and combine trees

				// if tableTree is the root
				if (tableTree->element < curTree->element) {

					// if tableTree does not have a child, make curTree its child
					if(tableTree->child == NULL) {
						tableTree->child = curTree;
						curTree->sibling = curTree;
						tableTree->degree = 1;
					}

					// if tableTree has children, add curTree to its children list
					else {
						BinomialHeapNode<T> *temp = tableTree->child->sibling;
						tableTree->child->sibling = curTree;
						curTree->sibling = temp;
						tableTree->degree = (tableTree->degree) + 1;
					}

					// if no tree of this degree is in the table
					// add the new tree to table, otherwise continue loop
					degree = tableTree->degree;
					if (pairTable[degree] == NULL) {
						pairTable[degree] = tableTree;
						done = true;
					}
				}

				// if curTree is the root
				else {

					// if curTree has no children, make tableTree its child
					if(curTree->child == NULL) {
						curTree->child = tableTree;
						tableTree->sibling = tableTree;
						curTree->degree = 1;
					}

					// if curTree has children, add tableTree to its children list
					else {
						BinomialHeapNode<T> *temp = curTree->child->sibling;
						curTree->child->sibling = tableTree;
						tableTree->sibling = temp;
						curTree->degree = (curTree->degree) + 1;
					}

					// if no tree of this degree is in the table
					// add the new tree to table, otherwise continue loop
					degree = curTree->degree;
					if (pairTable[degree] == NULL) {
						pairTable[degree] = curTree;
						done = true;
					}
				}
			} /* end while pairwise combine */
		}

		// update notInserted to next tree
		if (notInserted->sibling != NULL) {
			BinomialHeapNode<T> * temp = notInserted;
			notInserted = notInserted->sibling;
			temp->sibling = NULL;
		}
		else {notInserted = NULL;}

	} /* end while not inserted */


	// set the min and re-complete the top level circular list
	BinomialHeapNode<T> * curTree = NULL;
	BinomialHeapNode<T> * start = NULL;
	for (int i = 0; i < maxDegree; i++) {
		if (pairTable[i] != NULL) {
			if (curTree == NULL) {
				curTree = pairTable[i];
				min = pairTable[i];
				start = pairTable[i];
				pairTable[i] = NULL;
			}
			else {
				BinomialHeapNode<T> * temp = pairTable[i];
				if (temp->element < min->element) {min = temp;}
				curTree->sibling = temp;
				curTree = curTree->sibling;
			}
		}
	}
	curTree->sibling = start ; //complete circular list
}

/*
 * Lever order traversal of the binomial heap.
 */
template<class T>
void BinomialHeap<T>::levelOrder(void(*theVisit)(BinomialHeapNode<T> *)) {

	Queue<BinomialHeapNode<T>*> parents;
	Queue<BinomialHeapNode<T>*> children;
	BinomialHeapNode<T> * start;

	parents.push(min);
	start = min->sibling;
	while (start != min) {
		parents.push(start);
		start = start->sibling;
	}

	while(!parents.empty()) {
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
			parents.pop();
		}
		cout << endl;
		while (!children.empty()) {
			parents.push(children.front());
			children.pop();
		}
	}
}

/*
 * Prints the binomial heap in level order.
 */
template <class T>
void BinomialHeap<T>::print() {
	levelOrder(printElement);
}

/*
 * Outputs the element of the binomial heap node.
 */
template <class T>
void BinomialHeap<T>::printElement(BinomialHeapNode<T> *t) {
	cout << t->element << ' ';
}

#endif /* BINOMIALHEAP_H_ */
