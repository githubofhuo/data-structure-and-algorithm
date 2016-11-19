#pragma once
#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SERACH_TREE_HPP
#include <iostream>
//二叉查找树节点
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

//二叉查找树
template <typename T>
class BSTree
{
private:
	BSNode<T>* root;		//根节点
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

	void preOrder();		//前序遍历二叉树
	void inOrder();			//中序遍历二叉树
	void postOrder();		//后续遍历二叉树
	void layerOrder();		//层次遍历二叉树

	BSNode<T>* search_recursion(T key);		//递归查找	
	BSNode<T>* search_iterator(T key);		//迭代查找

	T search_minimum();		//查找最小元素
	T search_maximum();		//查找最大元素

	BSNode<T>* successor(BSNode<T>* pnode);		//查找指定节点后继节点
	BSNode<T>* predecessor(BSNode<T>* pnode);	//查找指定节点的前驱节点

	void insert(T key);		//插入指定值节点
	void remove(T key);		//删除指定值节点
	void destory();			
	void print();
};


#endif //BINARY_SEARCH_TREE_HPP

//递归
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
	删除二叉排序树的某个节点有三种情况：
	被删除节点同时有左子树与右子树。
	被删除节点只有左子树或只有右子树。
	被删除节点没有子树。
	对于第一种情况，我们的处理方式是将前驱节点的值保存在当前结点，继而删除前驱节点。
	对于第二种情况，我们直接用子树替换被删节点。
	对于第三种情况，我们可以直接删除节点。
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
					情况二，三:被删节点只有左子树或右子树,用子树代替;
					或没有孩子,直接删除节点
				*/
				del_node = pnode;
			}
			else
				/*
					情况一:被删节点同时有左子树与右子树，则删除节点前驱
				*/
				del_node = predecessor(pnode);

			//被删节点只有一个子节点或没有子节点,保存子节点指针
			BSNode<T>* child_node = nullptr;
			if (del_node->lchild != nullptr)
				child_node = del_node->lchild;
			else
				child_node = del_node->rchild;
			//子节点指向被删节点的父节点
			if (child_node != nullptr)
				child_node->parent = del_node->parent;
			//被删节点是头节点
			if (del_node->parent == nullptr)
				root = child_node;

			//被删节点不是头节点,更改双亲节点指向新子节点
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
//一个节点的后继节点也有三种情况
//它有右子树；则其后继节点为其右子树的最左节点
//它没有右子树，但它本身是一个左孩子，则后继节点为它的双亲
//它没有右子树，但它本身是一个右孩子，则其后继节点为“具有左孩子的最近父节点”
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
	对于一棵二叉排序树，中序遍历时刚好可以输出一个非递减的序列。
	一个节点的前驱节点有3种情况：
	它有左子树，则左子树根节点为其前驱节点
	它没有左子树，且它本身为右子树，则其父节点为其前驱节点
	它没有左子树，且它本身为左子树，则它的前驱节点为“第一个拥有右子树的父节点”
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
	//进入循环为第三周情况;否则第二种
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

	//寻找插入位置
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

	//如果是空树则新节点为根
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
