#include "SinglyLinkedList.h"

int main()
{
	SLinkedList<int> list;

	list.AppendNode(1);
	list.AppendNode(2);
	list.AppendNode(3);
	list.InsertNode(1, 4);
	list.InsertNode(3, 5);

	cout << "list : ";
	list.DisplayList();
	cout << endl;

	int pos = list.FindNode(4);
	cout << "4 is at " << pos << endl;

	Node<int>* node = list.GetNodeAt(4);
	cout << node->getData() << endl;

	int size = list.GetSize();
	cout << size << endl;

	list.DeleteNode(3);
	list.DeleteNode(1);
	cout << "after delete list : ";
	list.DisplayList();
	cout << endl;
	size = list.GetSize();
	cout << size << endl;

	return 0;
}