//============================================================================
// Name        : MinHBLT.h
// Author      : Terek Arce
// Version     : 1.0
// Created     : Apr 5, 2014
// Copyright   : See MIT Liscence
// Description : MinHBLT, a minimum height biased leftist tree.
//============================================================================

#ifndef MINHBLT_H_
#define MINHBLT_H_

#include <iostream>
#include "Queue.h"
#include "MinHBLTnode.h"
#include "Exception.h"

template<class E>
class MinHBLT {
public:
	MinHBLTnode<pair<int,E> > *root;	// pointer to root
	int treeSize;	// number of nodes in tree

	MinHBLT();
	~MinHBLT();
	void initialize(E *, int);
	void push(const E&);
	void pop();
	void erase();
	void print();
	void postOrder(void(*)(MinHBLTnode<pair<int,E> >*));
	void levelOrder(void(*)(MinHBLTnode<pair<int,E> > *));

protected:
	void meld(MinHBLTnode<pair<int,E> >* &, MinHBLTnode<pair<int,E> >* &);
	static void destroy(MinHBLTnode<pair<int,E> > *);
	static void printElement(MinHBLTnode<pair<int,E> > *);
	static void postOrder(MinHBLTnode<pair<int,E> > *);
	static void (*visit)(MinHBLTnode<pair<int,E> >*);
};

template <class E>
void (*MinHBLT<E>::visit)(MinHBLTnode<pair<int,E> >*);

/*
 * Constructor.
 */
template <class E>
MinHBLT<E>::MinHBLT() {
	 root = NULL;
	 treeSize = 0;
}

/*
 * Destructor.
 */
template <class E>
MinHBLT<E>::~MinHBLT() {
	erase();
}

/*
 * Initializes a min height biased leftist tree using a queue in O(n) time.
 * See: http://en.wikipedia.org/wiki/Leftist_tree#Initializing_a_height_biased_leftist_tree
 */
template<class E>
void MinHBLT<E>::initialize(E* elements, int size) {

	Queue<MinHBLTnode<pair<int,E> >*> q(size);
	erase();

	// put all the elements in the queue
	for (int i = 1; i <= size; i++) {
		q.push(new MinHBLTnode<pair<int,E> > (pair<int,E>(1, elements[i])));
	}

	// pop 2 trees from the queue and meld them
	// then push the result back on queue
	// continue till done
	for (int i = 1; i <= size - 1; i++) {
		MinHBLTnode<pair<int,E> > *first = q.front();
		q.pop();
		MinHBLTnode<pair<int,E> > *second = q.front();
		q.pop();
		meld(first, second);
		q.push(first);
	}

	// set the root if the tree is not empty
	if (size > 0)
		root = q.front();
	treeSize = size;
}

/*
 * Push an element into the tree.
 */
template<class E>
void MinHBLT<E>::push(const E& element) {
	MinHBLTnode<pair<int,E> > *q = new MinHBLTnode<pair<int,E> > (pair<int,E> (1, element));
	meld(root,q);
	treeSize++;
}

/*
 * Pops the top/min element from the tree.
 */
template<class E>
void MinHBLT<E>::pop() {
	if (root == NULL) {
		ostringstream error;
		error << "tried to pop() from empty tree.";
		throw Exception(error.str());
	}

	// create left and right subtrees
	MinHBLTnode<pair<int,E> > *left = root->leftChild;
	MinHBLTnode<pair<int,E> > *right = root->rightChild;

	// delete and remeld
	delete root;
	root = left;
	meld(root, right);
	treeSize--;
}

/*
 * Melds to min HBLT trees together.
 * See: http://en.wikipedia.org/wiki/Leftist_tree#Merging_height_biased_leftist_trees
 */
template<class E>
void MinHBLT<E>::meld(MinHBLTnode<pair<int, E> >* &root1,
                      MinHBLTnode<pair<int, E> >* &root2) {

	// cases where one tree or the other is empty
	if (root2 == NULL) {return;}
	if (root1 == NULL) {root1=root2; return;}

	// if needed, swap root1 and root2 so as to maintain min property
	if (root1->element.second > root2->element.second) {
		swap(root1, root2);
	}

	meld(root1->rightChild, root2);

	// check s-values and swap if necessary, updating s-values
	if (root1->leftChild == NULL) {
		root1->leftChild = root1->rightChild;
		root1->rightChild = NULL;
		root1->element.first = 1;
	}
	else {
		if (root1->leftChild->element.first < root1->rightChild->element.first) {
			swap(root1->leftChild, root1->rightChild);
		}
		root1->element.first = root1->rightChild->element.first + 1;
	}
}

/*
 * Erases the entire HBLT tree.
 */
template <class E>
void MinHBLT<E>::erase(){
	postOrder(destroy);
	root = NULL;
	treeSize = 0;
}

/*
 * Deletes a node.
 */
template <class E>
void MinHBLT<E>::destroy(MinHBLTnode<pair<int,E> > *node) {
	delete node;
}

/*
 * Post-order traversal for visiting the tree.
 */
template <class E>
void MinHBLT<E>::postOrder(void(*theVisit)(MinHBLTnode<pair<int,E> >*)) {
	visit = theVisit;
	postOrder(root);
}

/*
 * (protected) Post-order traversal of the tree.
 */
template <class E>
void MinHBLT<E>::postOrder(MinHBLTnode<pair<int,E> > *t) {
	if (t != NULL) {
		postOrder(t->leftChild);
		postOrder(t->rightChild);
		MinHBLT<E>::visit(t);
	}
}

/*
 * Prints the tree in level order.
 */
template <class E>
void MinHBLT<E>::print() {
	levelOrder(printElement);
	cout << endl;		//TODO: is this necessary?
}

/*
 * Prints an element of the tree.
 */
template <class E>
void MinHBLT<E>::printElement(MinHBLTnode<pair<int,E> > *t) {
	cout << t->element.second << ' ';
}

/*
 * Level-order visitor traversal of the tree.
 */
template <class E>
void MinHBLT<E>::levelOrder(void(*theVisit)(MinHBLTnode<pair<int,E> > *)) {

	cout << endl;

	int nodesCurrentLevel = 1;
	int nodesNextLevel = 0;
	Queue<MinHBLTnode<pair<int,E> > *> q;
	MinHBLTnode<pair<int,E> > *temp = root;

	while (temp != NULL) {
		theVisit(temp);

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

		// determine if you should move on to next level
		if (nodesCurrentLevel == 0) {
			cout << endl;
			nodesCurrentLevel = nodesNextLevel;
			nodesNextLevel = 0;
		}
	}
}

#endif /* MINHBLT_H_ */
