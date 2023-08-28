/*
* Jacob Rizzo
 * Coding 07
 * Purpose: creation of and interface for binary search tree ADT
 */

#ifndef BINTREE_BINTREE_H
#define BINTREE_BINTREE_H

#include <iostream>
#include <string>
#include "data.h"

using std::cout;
using std::endl;
using std::string;

class BinTree {
public:
	BinTree();
	~BinTree();

	//public methods without private overloads
	bool isEmpty();
	int getCount();
	bool getRootData(Data*);
	void displayTree();

	//public methods with private overloads
	void clear();
	bool addNode(int, string);
	bool removeNode(int);
	bool getNode(Data*, int);
	bool contains(int);
	int getHeight();

	//public display methods with private overloads
	void displayPreOrder();
	void displayPostOrder();
	void displayInOrder();

private:
	//private attributes
	DataNode* root;
	int count;

	//private overloads
	void clear(DataNode*);
	bool addNode(DataNode*, DataNode**);
	DataNode* removeNode(int, DataNode*);
	bool getNode(Data*, int, DataNode*);
	bool contains(int, DataNode*);
	int getHeight(DataNode*);
	void displayPreOrder(DataNode*);
	void displayPostOrder(DataNode*);
	void displayInOrder(DataNode*);

	//private method to help with removeNode method
	DataNode* minValueNode(DataNode*);


};






#endif /* BINTREE_BINTREE_H */

