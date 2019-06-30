#include "WinnerTree.h"

int main()
{
	WinnerTree<int> wtree;

	wtree.Init();

	Record<int>* winner;
	for (int i = 0; i < 2; i++) {
		winner = wtree.GetWinner();
		puts("========== winner ==========");
		cout << winner->GetKey() << endl;	// who is winner?
		puts("============================");
		if (!wtree.NextWinner())	// find next winner
			break;
	}

	return 0;
}