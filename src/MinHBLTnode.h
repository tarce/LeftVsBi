//============================================================================
// Name        : MinHBLTnode.h
// Author      : Terek Arce
// Version     : 1.0
// Created     : Apr 4, 2014
// Copyright   : See MIT Liscence
// Description : MinHBLT Node, a struct that is used in constructing the min
//               height biased leftist tree.
//============================================================================


#ifndef MINHBLTNODE_H_
#define MINHBLTNODE_H_

#include <stddef.h>

template <class T>
struct MinHBLTnode {

	T element;	// the element stored in the tree
	MinHBLTnode<T> *leftChild;	// pointer to left subtree
	MinHBLTnode<T> *rightChild;  // pointer to right subtree

	/*
	 * Constructors follow.
	 */
	MinHBLTnode() {
		leftChild = NULL;
		rightChild = NULL;
	}

	MinHBLTnode(const T& theElement) {
		element = theElement;
		leftChild = NULL;
		rightChild = NULL;
	}
	MinHBLTnode(const T& theElement,
			MinHBLTnode *theLeftChild,
			MinHBLTnode *theRightChild) {
		element = theElement;
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};

#endif /* MINHBLTNODE_H_ */
