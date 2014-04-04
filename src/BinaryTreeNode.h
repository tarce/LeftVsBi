//============================================================================
// Name        : BinaryTreeNode.h
// Author      : Terek Arce
// Version     : 1.0
// Created     : Apr 4, 2014
// Copyright   : See MIT Liscence
// Description : Binary Tree Node, a struct that is used in constructing the binary tree
//============================================================================


#ifndef BINARYTREENODE_H_
#define BINARYTREENODE_H_

#include <stddef.h>

template <class T>
struct BinaryTreeNode {

	T element;						// the element stored in the tree
	BinaryTreeNode<T> *leftChild;	// pointer to left subtree
	BinaryTreeNode<T> *rightChild;  // pointer to right subtree

	/*
	 * Constructors follow.
	 */
	BinaryTreeNode() {
		leftChild = NULL;
		rightChild = NULL;
	}

	BinaryTreeNode(const T& theElement) {
		element = theElement;
		leftChild = NULL;
		rightChild = NULL;
	}
	BinaryTreeNode(const T& theElement,
			BinaryTreeNode *theLeftChild,
			BinaryTreeNode *theRightChild) {
		element = theElement;
		leftChild = theLeftChild;
		rightChild = theRightChild;
	}
};

#endif /* BINARYTREENODE_H_ */
