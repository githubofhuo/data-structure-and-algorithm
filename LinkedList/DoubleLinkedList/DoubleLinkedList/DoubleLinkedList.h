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
	头节点不动
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
	Node<T>* insert_front(T value);		//头节点不动，插入到头节点和1节点之间
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
 *	将节点位置插入到到index之前
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
*将新节点插到第一个位置
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
*将新节点插到链表尾部
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
	删除指定位置的元素
	返回被删除节点的前一节点
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
	删除链表第一个节点
	返回删除后链表的第一个节点
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
	删除链表末为节点
	返回删除后链表尾部元素
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

//返回第一个节点的值
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

	//前半部分
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

	//后半部分
	index = count - index - 1;
	Node<T>* pnode = phead->pre_ptr;
	while(index)
	{
		pnode = pnode->pre_ptr;
		index--;
	}
	return pnode;
}
