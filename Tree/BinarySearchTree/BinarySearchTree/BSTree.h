#pragma once
#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SERACH_TREE_HPP

//二叉查找树节点
template <typename T>
struct BSNode
{
	BSNode(T, t)
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

	BSNode<T>* successor(BSNode<T>* x);		//查找指定节点后继节点
	BSNode<T>* predecessor(BSNode<T>* x);	//查找指定节点的前驱节点

	void insert(T key);		//插入指定值节点
	void remove(T key);		//删除指定值节点
	void destory();			
	void print();
};
#endif //BINARY_SEARCH_TREE_HPP
