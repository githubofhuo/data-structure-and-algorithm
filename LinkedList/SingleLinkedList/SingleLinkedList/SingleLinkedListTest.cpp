#include "SingleLinkedList.h"
#include <iostream>
using namespace std;

int main()
{
	int i;
	int nCount;
	SingleLinkedList<int> slist;
	
	slist.InsertAfter(slist.InsertAfter(slist.AddHead(1), 2), 3);
	slist.InsertAfter(slist.InsertAfter(slist.GetLength(), 4), 5);
	slist.InsertAfter(slist.GetLength(), 6);
	slist.AddTail(10);
	slist.InsertAfter(slist.InsertBefore(slist.GetLength(), 7), 8);
	slist.SetAt(slist.GetLength(), 9);
	slist.RemoveHead();
	slist.RemoveTail();

	// print out elements
	nCount = slist.GetLength();
	for (i = 0; i < nCount; ++i)
		cout << slist.GetAt(i + 1) << endl;
	return 0;
}
