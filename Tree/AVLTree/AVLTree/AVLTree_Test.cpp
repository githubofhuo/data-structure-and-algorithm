#include <cstdio>
#include <iostream>
#include "AVLTree.h"
using namespace std;

int main(int argc, char* argv[])
{
	AVLTree<int> a;
	for (int i = 0; i < 10; i++)
		a.insert(i);
	cout << "���ߣ�" << a.height() << endl;

	cout << "�������:" << endl;
	a.inOrder();

	cout << "ɾ��Ԫ��10" << endl;
	a.remove(10);

	AVLTreeNode<int>* b = a.search_iterator(10);

	if (b != nullptr)
		cout << b->key;
	else
		cout << "�޴�Ԫ��" << endl;

	getchar();

	return 0;
}
