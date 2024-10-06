#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <math.h>
#include <iostream>
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

class Stack {
  private:
	std::vector<OP*> stack;

  public:
	int size();
	void push(OP*);
	OP* pop();
};

class Queue {
  private:
	std::vector<OP*> queue;

  public:
	int size();
	void enqueue(OP*);
	OP* dequeue();
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