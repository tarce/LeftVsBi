/*
 * BinaryTree.h
 *
 *  Created on: Apr 4, 2014
 *      Author: terek
 */

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
	void erase();
	void print();
	void postOrder(void(*)(MinHBLTnode<pair<int,E> >*));
	void levelOrder(void(*)(MinHBLTnode<pair<int,E> > *));
	void pop();
	void push(const E&);
	void initialize(E *, int);

protected:
	//TODO: visit????
	static void (*visit)(MinHBLTnode<pair<int,E> >*);
	static void postOrder(MinHBLTnode<pair<int,E> > *);
	static void destroy(MinHBLTnode<pair<int,E> > *);
	static void printElement(MinHBLTnode<pair<int,E> > *);
	void meld(MinHBLTnode<pair<int,E> >* &, MinHBLTnode<pair<int,E> >* &);
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
 * Erases the entire binary tree.
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
 * Prints the binary tree in level order.
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

	cout << endl;	//TODO: is this necessary?

	int nodesCurrentLevel = 1;
	int nodesNextLevel = 0;
	Queue<MinHBLTnode<pair<int,E> > *> q;
	MinHBLTnode<pair<int,E> > *temp = root;

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

template<class E>
void MinHBLT<E>::pop() {
	if (this->root == NULL) {throw Exception();}

	//create left and right subtrees
	MinHBLTnode<pair<int,E> > *left = this->root->leftChild, *right = this->root->rightChild;

	//delete and remeld
	delete this->root;
	this->root = left;
	meld(this->root, right);
	(this->treeSize)--;
}

template<class E>
void MinHBLT<E>::push(const E& theElement) {

	//create single node
	MinHBLTnode<pair<int,E> > *q = new MinHBLTnode<pair<int,E> > (pair<int,E>(1, theElement));

	// meld with this
	meld(this->root,q);
	this->treeSize++;
}

template<class E>
void MinHBLT<E>::meld(MinHBLTnode<pair<int, E> >* &x, MinHBLTnode<pair<int, E> >* &y) {

	//cases where one tree or the other is empty
	if (y == NULL) {return;}
	if (x == NULL) {x=y; return;}

	//swap x and y if as to maintain min property
	if (x->element.second > y->element.second) {swap(x, y);}		//NOTE: this seemed wrong in the wiki, change sign direction

	meld(x->rightChild,y);

	//check s-values and swap if necessary, updating s-values
	if (x->leftChild == NULL) {
		x->leftChild = x->rightChild;
		x->rightChild = NULL;
		x->element.first = 1;
	}
	else {
		if (x->leftChild->element.first < x->rightChild->element.first) {swap(x->leftChild, x->rightChild);}
		x->element.first = x->rightChild->element.first + 1;
	}
}

template<class E>
void MinHBLT<E>::initialize(E* theElements, int theSize) {
	Queue<MinHBLTnode<pair<int,E> >*> q(theSize);
	this->erase();  // make *this empty

	// init queue of tree
	for (int i = 1; i <= theSize; i++) {q.push(new MinHBLTnode<pair<int,E> > (pair<int,E>(1, theElements[i])));}

	//meld from queue and push back on queue, continue till done
	for (int i = 1; i <= theSize - 1; i++) {
		MinHBLTnode<pair<int,E> > *first = q.front();
		q.pop();
		MinHBLTnode<pair<int,E> > *second = q.front();
		q.pop();
		meld(first, second);
		q.push(first);
	}

	//determine min
	if (theSize > 0)
		this->root = q.front();

	this->treeSize = theSize;
}

#endif /* MINHBLT_H_ */
