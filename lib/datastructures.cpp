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

void OP::expand_with_bst(BST* created, std::queue<OP*>& frontier) {
	double d_sqrt = sqrt(this->data);
	double d_floor = floor(this->data);
	double d_times_two = this->data * 2;

	if (!created->includes_double(d_sqrt)) {
		this->left = new OP(d_sqrt, "sqrt", this);
		frontier.push(this->left);
		created->insert(this->left);
	}

	if (!created->includes_double(d_floor)) {
		this->middle = new OP(d_floor, "floor", this);
		frontier.push(this->middle);
		created->insert(this->middle);
	}

	if (!created->includes_double(d_times_two)) {
		this->right = new OP(d_times_two, "times_two", this);
		frontier.push(this->right);
		created->insert(this->right);
	}
}

void OP::expand_with_map(std::unordered_map<double, OP*>& created,
						 std::queue<OP*>& frontier) {
	double d_sqrt = sqrt(this->data);
	double d_floor = floor(this->data);
	double d_times_two = this->data * 2;

	if (created.find(d_sqrt) == created.end()) {
		this->left = new OP(d_sqrt, "sqrt", this);
		frontier.push(this->left);
		created[d_sqrt] = this->left;
	}

	if (created.find(d_floor) == created.end()) {
		this->middle = new OP(d_floor, "floor", this);
		frontier.push(this->middle);
		created[d_floor] = this->middle;
	}

	if (created.find(d_times_two) == created.end()) {
		this->right = new OP(d_times_two, "times_two", this);
		frontier.push(this->right);
		created[d_times_two] = this->right;
	}
}

void OP::print_path() {
	std::stack<OP*> s;

	OP* current = this;

	while (current != NULL) {
		s.push(current);
		current = current->parent;
	}

	while (s.size() > 0) {
		OP* op = s.top();
		s.pop();
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

bool BST::includes_node(OP* op) {
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

bool BST::includes_double(double d) {
	BST* current = this;
	while (current != NULL) {
		if (current->op->data == d) {
			return true;
		} else if (current->op->data > d) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	return false;
}
