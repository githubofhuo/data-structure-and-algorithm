#ifndef _SINGLE_LINKED_LIST_H
#define _SINGLE_LINKED_LIST_H

#include <assert.h>
#include <iostream>

template <typename T>
class SingleNode
{
public:
	T data;
	SingleNode<T>* next;
public:
	SingleNode()
		:data(T()), next(NULL) {}
	SingleNode(const T& InitData)
		:data(InitData), next(NULL) {}
	SingleNode(const T& InitData, SingleNode<T> *p)
		:data(InitData), next(p) {}
	~SingleNode() {}

	T& GetData(void) { return data; }
};

template <typename T>
class SingleLinkedList
{
protected:
	int length;
	SingleNode<T>* NodeHead;

public:
	SingleLinkedList()
		:length(0), NodeHead(NULL) {}
	SingleLinkedList(const T& InitData)
		:length(0), NodeHead(NULL) 
	{
		AddHead(InitData);
	}
	~SingleLinkedList();

public:
	int IsEmpty() const { return 0 == length; }
	int GetLength() const { return length; }
	int InsertBefore(const int position, const T& data);
	int InsertAfter(const int position, const T& data);
	int AddHead(const T& data);
	int AddTail(const T& data);
	int RemoveAt(const int position);
	int RemoveHead();
	int RemoveTail();
	void RemoveAll();

	T& GetTail();
	T GetTail() const;
	T& GetHead();
	T GetHead() const;
	T& GetAt(const int position);
	T GetAt(const int position) const;
	void SetAt(const int position, const T& data);
	
	// occurence:�ڼ��γ���
	// return appeared position, -1 if not found;
	int Find(const T& data, size_t occurrence=1) const;
};


template <typename T>
SingleLinkedList<T>::~SingleLinkedList()
{
	RemoveAll();
}

//���ز���ڵ��λ��, ʧ�ܷ���-1
template<typename T>
inline int SingleLinkedList<T>::InsertBefore(const int position, const T& data)
{
	assert(1 <= position && position <= length);
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

	//����Ϊ��
	if (NULL == NodeHead)
	{
		newNode->next = NULL;
		NodeHead = newNode;
		CurrentPosition = 1;
		length++;
	}
	else //������
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

//�����²���node��position, ʧ�ܷ���-1
template<typename T>
int SingleLinkedList<T>::InsertAfter(const int position, const T& data)
{
	assert(1 <= position && position <= length + 1);

	SingleNode<T>* tempNode;
	SingleNode<T>* newNode;
	size_t position_t;

	try
	{
		newNode = new SingleNode<T>(data);
	}
	catch (std::bad_alloc execption)
	{
		std::cerr << "bad_alloc excetption!" << std::endl;
		return -1;
	}
	newNode->data = data;

	// ������
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
		++length;
		position_t = position + 1;
		return position_t;
	}
}

template<typename T>
int SingleLinkedList<T>::AddHead(const T& data)
{
	SingleNode<T>* newNode;
	try
	{
		newNode = new SingleNode<T>(data, NodeHead);
	}
	catch (const std::bad_alloc exception)
	{
		std::cerr << "bad_alloc exception��" << std::endl;
		return -1;
	}
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
	catch (std::exception error)
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
	for (int i = 0; i<count; i++)
	{
		try
		{
			tempNode = NodeHead->next;
			delete NodeHead;
			NodeHead = tempNode;
		}
		catch (std::exception error)
		{
			std::cerr << "Exception occurs while deleting node" << i << "\n" << error.what() << std::endl;
		}
	}
	length = 0;
}

template<typename T>
T & SingleLinkedList<T>::GetTail()
{
	assert(length >= 1);
	int count;
	SingleNode<T>* tempNode = NodeHead;
	count = length;
	for (int i = 1; i < count; i++)
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
	assert(1 <= position && position <= length);

	SingleNode<T>* tempNode = NodeHead;
	for (int i = 1; i < position; i++)
	{
		tempNode = tempNode->next;
	}
	return tempNode->data;
}

template<typename T>
T SingleLinkedList<T>::GetAt(const int position) const
{
	assert(1 <= position && position <= length);

	SingleNode<T>* tempNode = NodeHead;
	for (int i = 1; i < position; i++)
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
	for (int i = 1; i<position; i++)
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
	for (int i = 0; i < count; i++)
	{
		if (data == tempNode->data && occurrenceCount == occurrence)
			return i + 1;
		tempNode = tempNode->next;
	}

	return -1;
}

#endif //_SINGLE_LINKED_LIST_H
