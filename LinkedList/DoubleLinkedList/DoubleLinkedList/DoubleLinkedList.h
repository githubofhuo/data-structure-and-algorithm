#pragma once
#ifndef _DOUBLELINKEDLIST_H
#define _DOUBLELINKEDLIST_H

template <typename T>
struct Node
{
public:
	Node() = default;
	Node(T value, Node<T>* ptrptr, Node<T>* nextptr)
		: _value(value), pre_ptr(ptrptr), next_ptr(nextptr) {}

public:
	T _value;
	Node<T>* pre_ptr;
	Node<T>* next_ptr;
};

/*
	ͷ�ڵ㲻��
*/
template <typename T>
class DoubleLinkedList
{
public:
	typedef Node<T>* pointer;
public:
	DoubleLinkedList();
	~DoubleLinkedList();
public:
	Node<T>* insert(int index, T value);
	Node<T>* insert_front(T value);		//ͷ�ڵ㲻�������뵽ͷ�ڵ��1�ڵ�֮��
	Node<T>* insert_last(T value);

	Node<T>* del(int index);
	Node<T>* delete_front();
	Node<T>* delete_last();
	
	bool isEmpty();
	int size();

	T get(int index);
	T get_front();
	T get_last();
	Node<T>* getHead();

private:
	Node<T>* phead;
	int count;
private:
	Node<T>* getNode(int index);
};
#endif

template<typename T>
inline DoubleLinkedList<T>::DoubleLinkedList()
{
	phead = new Node<T>(0, nullptr, nullptr);
	phead->next_ptr = phead;
	phead->pre_ptr = phead;
	count = 0;
}

template<typename T>
inline DoubleLinkedList<T>::~DoubleLinkedList()	{}

/*
 *	���ڵ�λ�ò��뵽��index֮ǰ
 */
template<typename T>
inline Node<T>* DoubleLinkedList<T>::insert(int index, T value)
{
	if (index == 0)
		return insert_front(value);

	Node<T>* pnode = getNode(index);
	if (pnode == nullptr)
		return nullptr;

	Node<T>* newNode = new Node<T>(value, pnode->pre_ptr, pnode);
	pnode->pre_ptr->next_ptr = newNode;
	pnode->pre_ptr = newNode;
	count++;

	return newNode;
}
/*
*���½ڵ�嵽��һ��λ��
*/
template<typename T>
inline Node<T>* DoubleLinkedList<T>::insert_front(T value)
{
	Node<T>* newNode = new Node<T>(value, phead, phead->next_ptr);
	phead->next_ptr->pre_ptr = newNode;
	phead->next_ptr = newNode;
	count++;
	return newNode;
}
/*
*���½ڵ�嵽����β��
*/
template<typename T>
inline Node<T>* DoubleLinkedList<T>::insert_last(T value)
{
	Node<T>* newNode = new Node<T>(value, phead->pre_ptr, phead);
	phead->pre_ptr->next_ptr = newNode;
	phead->pre_ptr = newNode;
	count++;
	return newNode;
}

/*
	ɾ��ָ��λ�õ�Ԫ��
	���ر�ɾ���ڵ��ǰһ�ڵ�
*/
template<typename T>
inline Node<T>* DoubleLinkedList<T>::del(int index)
{
	if (index == 0)
		return delete_front();
	if (index == count - 1)
		return delete_last();
	if (index >= count)
		return nullptr;
	
	Node<T>* pnode = getNode(index);
	pnode->pre_ptr->next_ptr = pnode->next_ptr;
	pnode->next_ptr->pre_ptr = pnode->pre_ptr;

	Node<T>* ptemp = pnode->pre_ptr;
	delete pnode;
	count--;
	return ptemp;
}

/*
	ɾ�������һ���ڵ�
	����ɾ��������ĵ�һ���ڵ�
*/
template<typename T>
inline Node<T>* DoubleLinkedList<T>::delete_front()
{
	if (count == 0)
		return nullptr;
	Node<T>* pnode = phead->next_ptr;
	phead->next_ptr = pnode->next_ptr;
	pnode->next_ptr->pre_ptr = phead;

	delete pnode;
	count--;
	return phead->next_ptr;
}

/*
	ɾ������ĩΪ�ڵ�
	����ɾ��������β��Ԫ��
*/
template<typename T>
inline Node<T>* DoubleLinkedList<T>::delete_last()
{
	if (count == 0)
		return nullptr;

	Node<T>* pnode = phead->pre_ptr;
	pnode->pre_ptr->next_ptr = phead;
	phead->pre_ptr = pnode->pre_ptr;

	delete pnode;
	count--;
	return phead->pre_ptr;
}

template<typename T>
inline bool DoubleLinkedList<T>::isEmpty()
{
	return count == 0;
}

template<typename T>
inline int DoubleLinkedList<T>::size()
{
	return count;
}

template<typename T>
inline T DoubleLinkedList<T>::get(int index)
{
	Node<T>* pnode = getNode(index);
	return pnode->_value;
}

//���ص�һ���ڵ��ֵ
template<typename T>
inline T DoubleLinkedList<T>::get_front()
{
	return phead->next_ptr->_value;
}

template<typename T>
inline T DoubleLinkedList<T>::get_last()
{
	return phead->pre_ptr->_value;
}

template<typename T>
inline Node<T>* DoubleLinkedList<T>::getHead()
{
	return phead;
}

template<typename T>
inline Node<T>* DoubleLinkedList<T>::getNode(int index)
{
	if (index >= count || index < 0)
		return nullptr;

	//ǰ�벿��
	if (index <= count / 2)
	{
		Node<T>* pnode = phead->next_ptr;
		while(index)
		{
			pnode = pnode->next_ptr;
			index--;
		}
		return pnode;
	}

	//��벿��
	index = count - index - 1;
	Node<T>* pnode = phead->pre_ptr;
	while(index)
	{
		pnode = pnode->pre_ptr;
		index--;
	}
	return pnode;
}
