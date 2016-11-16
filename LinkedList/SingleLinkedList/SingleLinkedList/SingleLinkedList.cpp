#include "SingleLinkedList.h"
#include <iostream>
#include <exception>
//#include <new>
#include <cassert>

template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
	RemoveAll();
}

//返回插入节点的位置, 失败返回-1
template<typename T>
inline int SingleLinkedList<T>::InsertBefore(const int position, const T& data)
{
	assert(1 <= position && position <= this.length);
	int i;
	int CurrentPosition;
	SingleNode<T>* tempNode1;
	SingleNode<T>* tempNode2;
	SingleNode<T>* newNode;

	try
	{
		newNode = new SingleNode<T>(data);
	}
	catch (const std::bad_alloc& execption)
	{
		std::cerr << "bad_alloc exception when new the newNode." << std::endl;
		CurrentPosition = -1;
		return CurrentPosition;
	}

	//链表为空
	if(NULL == NodeHead)
	{
		newNode->next = NULL;
		NodeHead = newNode;
		CurrentPosition = 1;
		length++;
	}
	else //链表不空
	{
		tempNode1 = NodeHead;
		for (int i = 1; i < position; i++)
		{
			tempNode2 = tempNode1;
			tempNode1 = tempNode1->next;
		}
		newNode->next = tempNode1;
		tempNode2->next = newNode;
		CurrentPosition = position;
		++length;
	}

	return CurrentPosition;
}

//返回新插入node的position, 失败返回-1
template<typename T>
int SingleLinkedList<T>::InsertAfter(const int position, const T& data)
{
	assert(1 <= position && position <= length);

	SingleNode<T>* tempNode;
	SingleNode<T>* newNode;
	size_t position_t;

	try
	{
		newNode = new SingleNode<T>(data);
	}
	catch(std::bad_alloc& execption)
	{
		std::cerr << "bad_alloc excetption!" << std::endl;
		return -1;
	}
	newNode->data = data;

	// 空链表
	if (NULL == NodeHead)
	{
		newNode->next = NULL;
		NodeHead = newNode;
		++length;
		position_t = 1;
		return position_t;
	}
	else
	{
		tempNode = NodeHead;
		for (int i = 1; i < position; i++)
		{
			tempNode = tempNode->next;
		}
		newNode->next = tempNode->next;
		tempNode->next = newNode;
		position_t = position+1;
		return position_t;
	}
}

template<typename T>
int SingleLinkedList<T>::AddHead(const T& data)
{
	SingleNode<T>* newNode;
	try
	{
		newNode = new SingleNode<T>(data);
	}
	catch (const std::bad_alloc& exception)
	{
		std::cerr << "bad_alloc exception！" << std::endl;
		return -1;
	}
	newNode->next = NodeHead;
	NodeHead = newNode;
	++length;

	return 1;
}

template<typename T>
int SingleLinkedList<T>::AddTail(const T& data)
{
	return InsertAfter(GetLength(), data);
}

// if success, return deleted node position
// if failed, return -1
template<typename T>
int SingleLinkedList<T>::RemoveAt(const int position)
{
	assert(1 <= position && position <= length);
	int i;
	SingleNode<T>* tempNode1;
	SingleNode<T>* tempNode2;

	tempNode1 = NodeHead;
	try
	{
		// head node?
		if (1 == position)
		{
			NodeHead = NodeHead->next;
			delete tempNode1;
			--length;
		}
		else
		{
			for (i = 1; i < position; i++)
			{
				// tempNode2 will go to the previous node of the target node after loop finished
				tempNode2 = tempNode1;
				tempNode1 = tempNode1->next;
			}
			tempNode2->next = tempNode1->next;
			delete tempNode1;
			--length;
		}
		return position;
	}
	catch(std::exception& error)
	{
		std::cerr << error.what() << std::endl;
		return -1;
	}
}

template<typename T>
int SingleLinkedList<T>::RemoveHead()
{
	assert(0 != length);
	return RemoveAt(1);
}

template<typename T>
int SingleLinkedList<T>::RemoveTail()
{
	assert(0 != length);
	return RemoveAt(length);
}

//if success, return 0;
//if fail at node i, return i(1 <= i <= length)
template<typename T>
void SingleLinkedList<T>::RemoveAll()
{
	int count;
	SingleNode<T>* tempNode;
	
	count = length;
	for(int i=0;i<count;i++)
	{
		try 
		{
			tempNode = NodeHead->next;
			delete NodeHead;
			NodeHead = tempNode;
		}
		catch(std::exception& error)
		{
			std::cerr << "Exception occurs while deleting node" << i << "\n" << error.what() << std::endl;
		}
	}
	length = 0;
}

template<typename T>
T & SingleLinkedList<T>::GetTail()
{
	assert(1 != length);
	int count;
	SingleNode<T>* tempNode = NodeHead;
	count = length;
	for(int i=1; i < count; i++)
	{
		tempNode = tempNode->next;
	}
	return tempNode->data;
}

template<typename T>
T SingleLinkedList<T>::GetTail() const
{
	return GetTail();
}

template<typename T>
T & SingleLinkedList<T>::GetHead()
{
	assert(0 != length);
	return NodeHead->data;
}

template<typename T>
T SingleLinkedList<T>::GetHead() const
{
	assert(0 != length);
	return NodeHead->data;
}

template<typename T>
T & SingleLinkedList<T>::GetAt(const int position)
{
	return GetAt(position);
}

template<typename T>
T SingleLinkedList<T>::GetAt(const int position) const
{
	assert(1 <= position && position <= length);
	
	SingleNode<T>* tempNode = NodeHead;
	for(int i=1; i < position; i++)
	{
		tempNode = tempNode->next;
	}
	return tempNode->data;
}

template<typename T>
void SingleLinkedList<T>::SetAt(const int position, const T& data)
{
	assert(1 <= position && position <= length);
	
	SingleNode<T>* tempNode = NodeHead;
	for(int i=1;i<position;i++)
	{
		tempNode = tempNode->next;
	}
	tempNode->data = data;
}

template<typename T>
int SingleLinkedList<T>::Find(const T & data, size_t occurrence) const
{
	assert(1 <= occurrence && occurrence <= length);
	SingleNode<T>* tempNode = NodeHead;
	int count = length;
	int occurrenceCount = 0;
	for(int i=0; i < count; i++)
	{
		if (data == tempNode->data && occurrenceCount == occurrence)
			return i + 1;
		tempNode = tempNode->next;
	}

	return -1;
}
