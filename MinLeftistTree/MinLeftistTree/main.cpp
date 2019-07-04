#include "MinLeftistTree.h"

int main() {

	MinLeftistTree<int>	tree;

	tree.Push(50);
	tree.Push(7);
	tree.Push(4);
	tree.Push(29);
	tree.Push(11);
	tree.Push(13);

	puts("========== POP 3 NODES ==========");
	for (int i = 0; i < 3; i++) {
		int ret = tree.Top();
		cout << ret << endl;
		tree.Pop();
	}
	puts("=================================");

	return 0;
}