#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <math.h>
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <vector>

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
	bool includes(OP*);
};

#endif