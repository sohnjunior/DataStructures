#include "BST.h"

void main()
{
	BST<int> bst;

	bst.Insert(6);
	bst.Insert(3);
	bst.Insert(8);
	bst.Insert(5);
	bst.Insert(2);
	bst.Insert(9);
	bst.Insert(7);
	bst.Insert(1);
	bst.Insert(4);

	cout << "After Insertion..." << endl;
	bst.InorderTraversal(bst.GetRoot());
	cout << "Inorder .. " << endl;
	bst.PostorderTraversal(bst.GetRoot());
	cout << "Postorder .. " << endl;
	bst.PreorderTraversal(bst.GetRoot());
	cout << "Preorder .. " << endl;

	cout << endl << "After Delete 3..." << endl;
	bst.Delete(3);
	bst.InorderTraversal(bst.GetRoot());
	
	cout << endl << "After Delete 6..." << endl;
	bst.Delete(6);
	bst.InorderTraversal(bst.GetRoot());

	cout << endl << "After Delete 1..." << endl;
	bst.Delete(1);
	bst.InorderTraversal(bst.GetRoot());

	cout << endl << "After Delete 5..." << endl;
	bst.Delete(5);
	bst.InorderTraversal(bst.GetRoot());

	cout << endl << "After Delete 8..." << endl;
	bst.Delete(8);
	bst.InorderTraversal(bst.GetRoot());

	cout << endl << "After Delete 4..." << endl;
	bst.Delete(4);
	bst.InorderTraversal(bst.GetRoot());

	cout << endl << "After Delete 7..." << endl;
	bst.Delete(7);
	bst.InorderTraversal(bst.GetRoot());

	cout << endl << "After Delete 9..." << endl;
	bst.Delete(9);
	bst.InorderTraversal(bst.GetRoot());

	cout << endl << "After Delete 2..." << endl;
	bst.Delete(2);
	bst.InorderTraversal(bst.GetRoot());

	cout << endl << "After Delete 1..." << endl;
	bst.Delete(1);
	bst.InorderTraversal(bst.GetRoot());

	BST<int> small;
	small.Insert(2);
	small.Insert(1);
	small.Insert(3);

	BST<int> big;
	big.Insert(7);
	big.Insert(6);
	big.Insert(5);
	big.Insert(8);
	big.Insert(9);

	BST<int> join1, join2;
	join1.ThreeWayJoin(small, 4, big);
	cout << endl << "Tree way join..." << endl;
	join1.InorderTraversal(join1.GetRoot());

	join2.TwoWayJoin(small, big);
	cout << endl << "Two way join..." << endl;
	join2.InorderTraversal(join2.GetRoot());
}