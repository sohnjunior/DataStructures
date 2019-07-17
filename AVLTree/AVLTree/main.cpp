#include "AVLTree.h"
#include <string>
using namespace std;

int main() {
	AVL<string>	tree;

	// insert 12 month
	tree.Insert("MAR");
	tree.Insert("MAY");
	tree.Insert("NOV");
	tree.Insert("AUG");
	tree.Insert("APR");
	tree.Insert("JAN");
	tree.Insert("DEC");
	tree.Insert("JULY");
	tree.Insert("FEB");
	tree.Insert("JUNE");
	tree.Insert("OCT");
	tree.Insert("SEPT");

	// display the tree
	puts("\n========== After Insertion ==========");
	tree.DisplayTree(tree.GetRoot());
	puts("\n=====================================");

	// delete september
	tree.Delete("SEPT");
	// display the tree
	puts("\n========== After Delete September ==========");
	tree.DisplayTree(tree.GetRoot());
	puts("\n============================================");

	// delete january
	tree.Delete("JAN");
	// display the tree
	puts("\n========== After Delete January ==========");
	tree.DisplayTree(tree.GetRoot());
	puts("\n==========================================");

	// delete december
	tree.Delete("DEC");
	// display the tree
	puts("\n========== After Delete December ==========");
	tree.DisplayTree(tree.GetRoot());
	puts("\n===========================================");

	AVL<int>	inttree;

	// insert 10 element
	for (int i = 0; i < 10; i++)
		inttree.Insert(i + 1);

	// display the tree
	puts("\n========== After Insertion ==========");
	inttree.DisplayTree(inttree.GetRoot());
	puts("\n=====================================");

	// delete 7
	inttree.Delete(7);
	// display the tree
	puts("\n========== After Delete 7 ==========");
	inttree.DisplayTree(inttree.GetRoot());
	puts("\n============================================");

	// delete 4
	inttree.Delete(4);
	// display the tree
	puts("\n========== After Delete 4 ==========");
	inttree.DisplayTree(inttree.GetRoot());
	puts("\n==========================================");

	// delete 1, 3
	inttree.Delete(1);
	inttree.Delete(3);
	// display the tree
	puts("\n========== After Delete 1, 3 ==========");
	inttree.DisplayTree(inttree.GetRoot());
	puts("\n===========================================");

	return 0;
}