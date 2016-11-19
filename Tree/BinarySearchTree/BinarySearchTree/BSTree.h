#pragma once
#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SERACH_TREE_HPP
#include <iostream>
//����������ڵ�
template <typename T>
struct BSNode
{
	BSNode(T t)
		: value(t), lchild(nullptr), rchild(nullptr) {}
	BSNode() = default;

	T value;
	BSNode<T> *lchild;
	BSNode<T> *rchild;
	BSNode<T> *parent;
};

//���������
template <typename T>
class BSTree
{
private:
	BSNode<T>* root;		//���ڵ�
private:
	BSNode<T>* search(BSNode<T>* &p, T key);
	void remove(BSNode<T>* p, T key);
	void preOrder(BSNode<T>* p);
	void inOrder(BSNode<T>* p);
	void postOrder(BSNode<T>* p);
	T search_minimum(BSNode<T>* p);
	T search_maximum(BSNode<T>* p);
	void destory(BSNode<T>* &p);

public:
	BSTree();
	~BSTree();

	void preOrder();		//ǰ�����������
	void inOrder();			//�������������
	void postOrder();		//��������������
	void layerOrder();		//��α���������

	BSNode<T>* search_recursion(T key);		//�ݹ����	
	BSNode<T>* search_iterator(T key);		//��������

	T search_minimum();		//������СԪ��
	T search_maximum();		//�������Ԫ��

	BSNode<T>* successor(BSNode<T>* pnode);		//����ָ���ڵ��̽ڵ�
	BSNode<T>* predecessor(BSNode<T>* pnode);	//����ָ���ڵ��ǰ���ڵ�

	void insert(T key);		//����ָ��ֵ�ڵ�
	void remove(T key);		//ɾ��ָ��ֵ�ڵ�
	void destory();			
	void print();
};


#endif //BINARY_SEARCH_TREE_HPP

//�ݹ�
template<typename T>
inline BSNode<T>* BSTree<T>::search(BSNode<T>*& pnode, T key)
{
	if (pnode == nullptr)
		return nullptr;
	if (pnode->value == key)
		return pnode;
	if (pnode->value < key)
		return search(pnode->rchild, key);
	return search(pnode->lchild, key);
}

/*
	ɾ��������������ĳ���ڵ������������
	��ɾ���ڵ�ͬʱ������������������
	��ɾ���ڵ�ֻ����������ֻ����������
	��ɾ���ڵ�û��������
	���ڵ�һ����������ǵĴ���ʽ�ǽ�ǰ���ڵ��ֵ�����ڵ�ǰ��㣬�̶�ɾ��ǰ���ڵ㡣
	���ڵڶ������������ֱ���������滻��ɾ�ڵ㡣
	���ڵ�������������ǿ���ֱ��ɾ���ڵ㡣
*/
template<typename T>
inline void BSTree<T>::remove(BSNode<T>* p, T key)
{
	BSNode<T>* pnode = p;
	if (pnode != nullptr)
	{
		if (pnode->value == key)
		{
			BSNode<T>* del_node = nullptr;

			if (pnode->lchild == nullptr || pnode->rchild == nullptr)
			{
				/*
					���������:��ɾ�ڵ�ֻ����������������,����������;
					��û�к���,ֱ��ɾ���ڵ�
				*/
				del_node = pnode;
			}
			else
				/*
					���һ:��ɾ�ڵ�ͬʱ��������������������ɾ���ڵ�ǰ��
				*/
				del_node = predecessor(pnode);

			//��ɾ�ڵ�ֻ��һ���ӽڵ��û���ӽڵ�,�����ӽڵ�ָ��
			BSNode<T>* child_node = nullptr;
			if (del_node->lchild != nullptr)
				child_node = del_node->lchild;
			else
				child_node = del_node->rchild;
			//�ӽڵ�ָ��ɾ�ڵ�ĸ��ڵ�
			if (child_node != nullptr)
				child_node->parent = del_node->parent;
			//��ɾ�ڵ���ͷ�ڵ�
			if (del_node->parent == nullptr)
				root = child_node;

			//��ɾ�ڵ㲻��ͷ�ڵ�,����˫�׽ڵ�ָ�����ӽڵ�
			if (del_node->parent->lchild == del_node)
				del_node->parent->lchild = child_node;
			else if (del_node->parent->rchild == del_node)
				del_node->parent->rchild = child_node;

			if (pnode->value != del_node->value)
				pnode->value = del_node->value;

			delete del_node;
		}
		else if (pnode->value < key)
			remove(pnode->rchild, key);
		else
			remove(pnode->lchild, key);
	}
}

template<typename T>
inline void BSTree<T>::preOrder(BSNode<T>* p)
{
	if (p != nullptr)
	{
		std::cout << p->value << std::endl;
		preOrder(p->lchild);
		preOrder(p->rchild);
	}
}

template<typename T>
inline void BSTree<T>::inOrder(BSNode<T>* p)
{
	if (p != nullptr)
	{
		inOrder(p->lchild);
		std::cout << p->value << std::endl;
		inOrder(p->rchild);
	}
}

template<typename T>
inline void BSTree<T>::postOrder(BSNode<T>* p)
{
	if (p != nullptr)
	{
		postOrder(p->lchild);
		postOrder(p->rchild);
		std::cout << p->value <<std::endl;
	}
}

template<typename T>
inline T BSTree<T>::search_minimum(BSNode<T>* p)
{
	if (p->lchild != nullptr)
		return search_minimum(p->lchild);
	return p->value;
}

template<typename T>
inline T BSTree<T>::search_maximum(BSNode<T>* p)
{
	if (p->rchild != nullptr)
		return search_maximum(p->rchild);
	return p->value;
}

template<typename T>
inline void BSTree<T>::destory(BSNode<T>*& p)
{
	if (p != nullptr)
	{
		if (p->lchild != nullptr)
			destory(p->lchild);
		if (p->rchild != nullptr)
			destory(p->rchild);
		delete p;
		p = nullptr;
	}
}

template<typename T>
inline BSTree<T>::BSTree()
	: root(nullptr) {}

template<typename T>
inline BSTree<T>::~BSTree()
{
	destory(root);
}

template<typename T>
inline void BSTree<T>::preOrder()
{
	preOrder(root);
}

template<typename T>
inline void BSTree<T>::inOrder()
{
	inOrder(root);
}

template<typename T>
inline void BSTree<T>::postOrder()
{
	postOrder(root);
}

template<typename T>
inline void BSTree<T>::layerOrder()
{
}

template<typename T>
inline BSNode<T>* BSTree<T>::search_recursion(T key)
{
	return search(root, key);
}

template<typename T>
inline BSNode<T>* BSTree<T>::search_iterator(T key)
{
	BSNode<T> *pnode = root;
	while (pnode != nullptr)
	{
		if (key == pnode->value)
			return pnode;
		if (key > pnode->value)
			pnode = pnode->rchild;
		else
			pnode = pnode->lchild;
	}
	return nullptr;
}

template <typename T>
T BSTree<T>::search_minimum()
{
	return search_minimum(root);
}

template<typename T>
inline T BSTree<T>::search_maximum()
{
	return search_maximum(root);
}

//
//һ���ڵ�ĺ�̽ڵ�Ҳ���������
//�����������������̽ڵ�Ϊ��������������ڵ�
//��û��������������������һ�����ӣ����̽ڵ�Ϊ����˫��
//��û��������������������һ���Һ��ӣ������̽ڵ�Ϊ���������ӵ�������ڵ㡱
template<typename T>
inline BSNode<T>* BSTree<T>::successor(BSNode<T>* pnode)
{
	if (pnode->rchild != nullptr)
	{
		pnode = pnode->rchild;
		while (pnode->lchild != nullptr)
		{
			pnode = pnode->lchild;
		}
		return pnode;
	}

	BSNode<T>* parent_node = pnode->parent;
	while (parent_node != nullptr && parent_node->rchild == pnode)
	{
		pnode = parent_node;
		parent_node = parent_node->parent;
	}
}

/*
	����һ�ö������������������ʱ�պÿ������һ���ǵݼ������С�
	һ���ڵ��ǰ���ڵ���3�������
	�����������������������ڵ�Ϊ��ǰ���ڵ�
	��û������������������Ϊ�����������丸�ڵ�Ϊ��ǰ���ڵ�
	��û������������������Ϊ��������������ǰ���ڵ�Ϊ����һ��ӵ���������ĸ��ڵ㡱
*/
template<typename T>
inline BSNode<T>* BSTree<T>::predecessor(BSNode<T>* pnode)
{
	if (pnode->lchild != nullptr)
	{
		pnode = pnode->lchild;
		while(pnode->rchild != nullptr)
		{
			pnode = pnode->rchild;
		}
		return pnode;
	}

	BSNode<T>* parent_node = pnode->parent;
	//����ѭ��Ϊ���������;����ڶ���
	while (parent_node != nullptr && parent_node->lchild == pnode)
	{
		pnode = parent_node;
		parent_node = parent_node->parent;
	}
	return parent_node;
}

template<typename T>
inline void BSTree<T>::insert(T key)
{
	BSNode<T>* parent_node = nullptr;
	BSNode<T>* temp_node = root;

	//Ѱ�Ҳ���λ��
	while(temp_node != nullptr)
	{
		parent_node = temp_node;
		if (key > parent_node->value)
			temp_node = temp_node->rchild;
		else if (key < parent_node->value)
			temp_node = temp_node->lchild;
		else
			break;
	}

	temp_node = new BSNode<T>(key);

	//����ǿ������½ڵ�Ϊ��
	if (parent_node == nullptr)
		root = temp_node;
	else
	{
		if (key > parent_node->value)
			parent_node->rchild = temp_node;
		else
			parent_node->lchild = temp_node;
	}
	temp_node->parent = parent_node;
}

template<typename T>
inline void BSTree<T>::remove(T key)
{
	remove(root, key);
}

template<typename T>
inline void BSTree<T>::destory()
{
	destory(root);
}

template<typename T>
inline void BSTree<T>::print()
{}
