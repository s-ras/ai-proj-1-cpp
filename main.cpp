#include <chrono>
#include "include/datastructures.h"

const int START = 4;

void gather_input(int&);

OP* BFS_GRAPH(OP*, int);

int main() {
	int goal;

	gather_input(goal);

	OP* root = new OP(START, "root", NULL);

	OP* solution = NULL;

	auto start = std::chrono::high_resolution_clock::now();

	solution = BFS_GRAPH(root, goal);

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> duration = end - start;
	std::cout << "Execution time: " << duration.count() << " ms" << std::endl;

	if (solution != NULL) {
		solution->print_path();
	}

	return 0;
}

void gather_input(int& goal) {
	std::cout << "Which number are you trying to reach?\t";
	std::cin >> goal;
}

OP* BFS_GRAPH(OP* root, int goal) {
	Queue frontier;
	BST created = BST(root, NULL);
	frontier.enqueue(root);
	if (frontier.size() < 1) {
		std::cout << "Error, frontier cannot be empty at the begining of the "
					 "algorithm"
				  << std::endl;
		return NULL;
	}
	while (frontier.size() > 0) {
		OP* op = frontier.dequeue();
		if (op->data == goal) {
			return op;
		} else {
			op->expand();
			if (!created.includes(op->left)) {
				frontier.enqueue(op->left);
				created.insert(op->left);
			}
			if (!created.includes(op->middle)) {
				frontier.enqueue(op->middle);
				created.insert(op->middle);
			}
			if (!created.includes(op->right)) {
				frontier.enqueue(op->right);
				created.insert(op->right);
			}
		}
	}
	std::cout << "No solution was found" << std::endl;
	return NULL;
}
