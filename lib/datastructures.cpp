#include "../include/datastructures.h"

OP::OP(double data, std::string type, OP* parent) {
	this->data = data;
	this->type = type;

	this->parent = parent;

	this->left = NULL;
	this->middle = NULL;
	this->right = NULL;
}

void OP::expand() {
	double d_sqrt = sqrt(this->data);
	double d_floor = floor(this->data);
	double d_times_two = this->data * 2;

	this->left = new OP(d_sqrt, "sqrt", this);
	this->middle = new OP(d_floor, "floor", this);
	this->right = new OP(d_times_two, "times_two", this);
}

void OP::print_path() {
	Stack s;

	OP* current = this;

	while (current != NULL) {
		s.push(current);
		current = current->parent;
	}

	while (s.size() > 0) {
		OP* op = s.pop();
		if (op->type == "root") {
			std::cout << "start at " << op->data << std::endl;
		} else if (op->type == "sqrt") {
			std::cout << "sqrt(" << op->parent->data << ") = " << op->data
					  << std::endl;
		} else if (op->type == "floor") {
			std::cout << "floor(" << op->parent->data << ") = " << op->data
					  << std::endl;
		} else if (op->type == "times_two") {
			std::cout << op->parent->data << " * 2 = " << op->data << std::endl;
		}
	}
}

void Stack::push(OP* op) {
	stack.push_back(op);
}

OP* Stack::pop() {
	OP* top = stack.back();
	stack.pop_back();

	return top;
}

int Stack::size() {
	return this->stack.size();
}

void Queue::enqueue(OP* op) {
	queue.push_back(op);
}

OP* Queue::dequeue() {
	OP* front = queue.front();
	queue.erase(queue.begin());
	return front;
}

int Queue::size() {
	return this->queue.size();
}

BST::BST(OP* op, BST* parent) {
	this->op = op;

	this->parent = parent;

	this->left = NULL;
	this->right = NULL;
}

void BST::insert(OP* op) {
	BST* current = this;
	while (true) {
		if (current->op->data == op->data) {
			return;
		} else if (current->op->data > op->data) {
			if (current->left == NULL) {
				BST* newLeaf = new BST(op, current);
				current->left = newLeaf;
				return;
			}
			current = current->left;
		} else {
			if (current->right == NULL) {
				BST* newLeaf = new BST(op, current);
				current->right = newLeaf;
				return;
			}
			current = current->right;
		}
	}
}

bool BST::includes(OP* op) {
	BST* current = this;
	while (current != NULL) {
		if (current->op->data == op->data) {
			return true;
		} else if (current->op->data > op->data) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	return false;
}
