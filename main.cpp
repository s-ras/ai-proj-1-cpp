#include <chrono>
#include "include/datastructures.h"

const int START = 4;

void gather_input(int&, int&);

OP* UNIFIED_BFS_GRAPH_WITH_BST(OP*, int);

OP* UNIFIED_BFS_GRAPH_WITH_HASH_MAP(OP*, int);

int main() {
	int goal, alg;

	gather_input(goal, alg);

	OP* root = new OP(START, "root", NULL);

	OP* solution = NULL;

	auto start = std::chrono::high_resolution_clock::now();

	switch (alg) {
		case 1:
			solution = UNIFIED_BFS_GRAPH_WITH_BST(root, goal);
			break;
		case 2:
			solution = UNIFIED_BFS_GRAPH_WITH_HASH_MAP(root, goal);
			break;
		default:
			std::cout << "Invalid algorithm" << std::endl;
			exit(1);
	}

	auto end = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> duration = end - start;
	std::cout << "Execution time: " << duration.count() << " ms" << std::endl;

	if (solution != NULL) {
		solution->print_path();
	}

	return 0;
}

void gather_input(int& goal, int& alg) {
	std::cout << "Which algorithm would you like to use?" << std::endl;
	std::cout << "1. BFS with BST" << std::endl;
	std::cout << "2. BFS with Hash Map" << std::endl;
	std::cin >> alg;
	std::cout << "Which number are you trying to reach? ";
	std::cin >> goal;
}

OP* UNIFIED_BFS_GRAPH_WITH_BST(OP* root, int goal) {
	std::queue<OP*> frontier;
	BST* created = new BST(root, NULL);
	frontier.push(root);
	while (frontier.size() > 0) {
		OP* op = frontier.front();
		frontier.pop();
		if (op->data == goal) {
			return op;
		} else {
			op->expand_with_bst(created, frontier);
		}
	}
	std::cout << "No solution was found" << std::endl;
	return NULL;
}

OP* UNIFIED_BFS_GRAPH_WITH_HASH_MAP(OP* root, int goal) {
	std::queue<OP*> frontier;
	std::unordered_map<double, OP*> created;
	frontier.push(root);
	while (frontier.size() > 0) {
		OP* op = frontier.front();
		frontier.pop();
		if (op->data == goal) {
			return op;
		} else {
			op->expand_with_map(created, frontier);
		}
	}
	std::cout << "No solution was found" << std::endl;
	return NULL;
}
