#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <math.h>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

class BST;
class OP;

class OP {
  public:
	double data;
	std::string type;

	OP* parent = NULL;

	OP* left = NULL;
	OP* middle = NULL;
	OP* right = NULL;

	OP(double, std::string, OP*);

	void expand();
	void expand_with_map(std::unordered_map<double, OP*>&, std::queue<OP*>&);
	void expand_with_bst(BST*, std::queue<OP*>&);

	void print_path();
};

class BST {
  public:
	OP* op;

	BST* parent = NULL;

	BST* left = NULL;
	BST* right = NULL;

	BST(OP*, BST*);

	void insert(OP*);

	bool includes_node(OP*);
	bool includes_double(double);
};

#endif