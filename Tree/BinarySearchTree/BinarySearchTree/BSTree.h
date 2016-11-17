#pragma once
#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SERACH_TREE_HPP

//����������ڵ�
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

	BSNode<T>* successor(BSNode<T>* x);		//����ָ���ڵ��̽ڵ�
	BSNode<T>* predecessor(BSNode<T>* x);	//����ָ���ڵ��ǰ���ڵ�

	void insert(T key);		//����ָ��ֵ�ڵ�
	void remove(T key);		//ɾ��ָ��ֵ�ڵ�
	void destory();			
	void print();
};
#endif //BINARY_SEARCH_TREE_HPP
