/*
 * BinaryTree.h
 *
 *  Created on: Apr 4, 2014
 *      Author: terek
 */

#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#include <iostream>
#include "Queue.h"
#include "BinaryTreeNode.h"
#include "Exception.h"

template<class E>
class BinaryTree {
public:
	BinaryTreeNode<E> *root;	// pointer to root
	int treeSize;	// number of nodes in tree

	BinaryTree();
	~BinaryTree();
	void erase();
	void print();
	void postOrder(void(*)(BinaryTreeNode<E>*));
	void levelOrder(void(*)(BinaryTreeNode<E> *));

protected:
	//TODO: visit????
	static void (*visit)(BinaryTreeNode<E>*);
	static void postOrder(BinaryTreeNode<E> *);
	static void garbage(BinaryTreeNode<E> *);
	static void printElement(BinaryTreeNode<E> *);
};

template <class E>
void (*BinaryTree<E>::visit)(BinaryTreeNode<E>*);

/*
 * Constructor.
 */
template <class E>
BinaryTree<E>::BinaryTree() {
	 root = NULL;
	 treeSize = 0;
}

/*
 * Destructor.
 */
template <class E>
BinaryTree<E>::~BinaryTree() {
	erase();
}

/*
 * Erases the entire binary tree.
 */
template <class E>
void BinaryTree<E>::erase(){
	postOrder(garbage);
	root = NULL;
	treeSize = 0;
}

/*
 * Deletes a node.
 */
template <class E>
void BinaryTree<E>::garbage(BinaryTreeNode<E> *node) {
	delete node;
}

/*
 * Post-order traversal for visiting the tree.
 */
template <class E>
void BinaryTree<E>::postOrder(void(*theVisit)(BinaryTreeNode<E>*)) {
	visit = theVisit;
	postOrder(root);
}

/*
 * (protected) Post-order traversal of the tree.
 */
template <class E>
void BinaryTree<E>::postOrder(BinaryTreeNode<E> *t) {
	if (t != NULL) {
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		BinaryTree<E>::visit(t);
	}
}

/*
 * Prints the binary tree in level order.
 */
template <class E>
void BinaryTree<E>::print() {
	levelOrder(printElement);
	cout << endl;		//TODO: is this necessary?
}

/*
 * Prints an element of the tree.
 */
template <class E>
void BinaryTree<E>::printElement(BinaryTreeNode<E> *t) {
	cout << t->element << ' ';
}

/*
 * Level-order visitor traversal of the tree.
 */
template <class E>
void BinaryTree<E>::levelOrder(void(*theVisit)(BinaryTreeNode<E> *)) {

	cout << endl;	//TODO: is this necessary?

	int nodesCurrentLevel = 1;
	int nodesNextLevel = 0;
	Queue<BinaryTreeNode<E>*> q;
	BinaryTreeNode<E> *temp = root;

	while (temp != NULL) {
		theVisit(temp);  // visit t

		// put temp's children on q
		if (temp->leftChild != NULL) {
			q.push(temp->leftChild);
			nodesNextLevel += 1;
		}
		if (temp->rightChild != NULL) {
			q.push(temp->rightChild);
			nodesNextLevel += 1;
		}

		// get next node to visit
		try {temp = q.front();}
		catch (Exception& e) {return;}

		q.pop();
		nodesCurrentLevel--;

		//determine if on next level
		if (nodesCurrentLevel == 0) {
			cout << endl;
			nodesCurrentLevel = nodesNextLevel;
			nodesNextLevel = 0;
		}
	}
}



#endif /* BINARYTREE_H_ */
