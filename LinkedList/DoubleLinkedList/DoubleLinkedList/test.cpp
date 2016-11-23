#pragma once
#include "DoubleLinkedList.h"
#include <iostream>
using namespace std;
int main()
{
	DoubleLinkedList<int> dlink;
	//�������
	for (int i = 0; i < 10; i++)
	{
		dlink.insert(0, i + 10);
	}
	dlink.insert(0, 100);
	dlink.insert_last(1000);
	cout << "������:" << dlink.size() << endl;

	//ɾ������
	dlink.delete_front();
	dlink.delete_last();
	dlink.del(3);


	DoubleLinkedList<int>::pointer ptr = dlink.getHead();
	ptr = ptr->next_ptr;
	while (ptr != dlink.getHead())
	{
		cout << ptr->_value << endl;
		ptr = ptr->next_ptr;
	}

	getchar();
	return 0;
}
