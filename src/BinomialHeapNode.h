//============================================================================
// Name        : BinomialHeapNode.h
// Author      : Terek Arce
// Version     : 1.0
// Created     : Apr 5, 2014
// Copyright   : See MIT Liscence
// Description : Binomial Heap Node, a struct that is used in constructing the min
//               binomial heap.
//============================================================================



#ifndef BINOMIALHEAPNODE_H_
#define BINOMIALHEAPNODE_H_

#include <stddef.h>

template <class T>
struct BinomialHeapNode {
	T element;
	int degree;
	BinomialHeapNode<T> *child;
	BinomialHeapNode<T> *sibling;

	/*
	 * Constructors follow.
	 */
	BinomialHeapNode() {
		element = NULL;
		child = NULL;
		sibling = NULL;
		degree = 0;
	}
	BinomialHeapNode(const T& theElement){
		element = theElement;
		child = NULL;
		sibling = NULL;
		degree = 0;
	}

	/*
	 * Copies a node to another node.
	 */
	void copy (BinomialHeapNode* src) {
	   element = src->element;
	   child = src->child;
	   sibling = src->sibling;
	   degree = src->degree;
	}
};

#endif /* BINOMIALHEAPNODE_H_ */
