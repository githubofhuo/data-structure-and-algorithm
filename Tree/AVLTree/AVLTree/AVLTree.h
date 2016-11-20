#ifndef _AVLTREE_H
#define _AVLTREE_H
#include  <iostream>

template <typename T>
struct AVLTreeNode
{
	T key;
	size_t height;		// height: 节点的高度，用于计算父节点的平衡因子
	AVLTreeNode<T>* lchild;
	AVLTreeNode<T>* rchild;

	AVLTreeNode(T value, AVLTreeNode<T>* l_node, AVLTreeNode<T>* r_node)
		: key(value), height(0), lchild(l_node), rchild(r_node) {}
};

template <typename T>
class AVLTree
{
private:
	AVLTreeNode<T>* root;
public:
	AVLTree();
	~AVLTree();

	void preOrder();
	void inOrder();
	void postOrder();

	void print();
	void destory();

	void insert(T key);
	void remove(T key);

	AVLTreeNode<T>* search_recurse(T key);
	AVLTreeNode<T>* search_iterator(T key);
	T minimum();
	T maximum();

	int height();	//返回树的高度
private:
	void preOrder(AVLTreeNode<T>* pnode) const;
	void inOrder(AVLTreeNode<T>* pnode) const;
	void postOrder(AVLTreeNode<T>* pnode) const;

	void print(AVLTreeNode<T>* pnode, T key, int driction) const;
	void destory(AVLTreeNode<T>* &pnode) const;
	
	AVLTreeNode<T>* insert(AVLTreeNode<T>* &pnode, T key);
	AVLTreeNode<T>* remove(AVLTreeNode<T>* &pnode, T key);	//删除AVL树中节点pdel,并返回被删除的节点

	AVLTreeNode<T>* minimum(AVLTreeNode<T>* pnode) const;
	AVLTreeNode<T>* maximum(AVLTreeNode<T>* pnode) const;

	int height(AVLTreeNode<T>* pnode);
	int max(int a, int b);

	AVLTreeNode<T>* search_recurse(AVLTreeNode<T>* pnode, T key) const;
	AVLTreeNode<T>* search_iterator(AVLTreeNode<T>* pnode, T key) const;

	AVLTreeNode<T>* leftRotation(AVLTreeNode<T>* pnode);		//单旋:左旋
	AVLTreeNode<T>* rightRotation(AVLTreeNode<T>* pnode);		//单旋:右旋
	AVLTreeNode<T>* leftRightRotation(AVLTreeNode<T>* pnode);	//双旋:先左旋后右旋
	AVLTreeNode<T>* rightLeftRotation(AVLTreeNode<T>* pnode);	//双旋:先右旋后左旋
};
#endif

template<typename T>
inline AVLTree<T>::AVLTree()
	: root(nullptr) {}

template<typename T>
inline AVLTree<T>::~AVLTree()
{
	destory(root);
}

template<typename T>
inline void AVLTree<T>::preOrder()
{
	preOrder(root);
}

template<typename T>
inline void AVLTree<T>::inOrder()
{
	inOrder(root);
}

template<typename T>
inline void AVLTree<T>::postOrder()
{
	postOrder(root);
}

template<typename T>
inline void AVLTree<T>::print()
{
}

template<typename T>
inline void AVLTree<T>::destory()
{
	destory(root);
}

template<typename T>
inline void AVLTree<T>::insert(T key)
{
	insert(root, key);
}

template<typename T>
inline void AVLTree<T>::remove(T key)
{
	remove(root, key);
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::search_recurse(T key)
{
	return search_recurse(root, key);
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::search_iterator(T key)
{
	return search_iterator(root, key);
}

template<typename T>
inline T AVLTree<T>::minimum()
{
	AVLTreeNode<T>* result_node =  minimum(root);
	if (result_node != nullptr)
		return result_node->key;
}

template<typename T>
inline T AVLTree<T>::maximum()
{
	AVLTreeNode<T>* result_node = maximum(root);
	if (result_node != nullptr)
		return result_node->key;
}

template<typename T>
inline int AVLTree<T>::height()
{
	return height(root);
}

template<typename T>
inline void AVLTree<T>::preOrder(AVLTreeNode<T>* pnode) const
{
	if (pnode != nullptr)
	{
		std::cout << pnode->key << std::endl;
		inOrder(pnode->lchild);
		inOrder(pnode->rchild);
	}
}

template<typename T>
inline void AVLTree<T>::inOrder(AVLTreeNode<T>* pnode) const
{
	if (pnode != nullptr)
	{
		inOrder(pnode->lchild);
		std::cout << pnode->key << std::endl;
		inOrder(pnode->rchild);
	}
}

template<typename T>
inline void AVLTree<T>::postOrder(AVLTreeNode<T>* pnode) const
{
	if (pnode != nullptr)
	{
		inOrder(pnode->lchild);
		inOrder(pnode->rchild);
		std::cout << pnode->key << std::endl;
	}
}

template<typename T>
inline void AVLTree<T>::print(AVLTreeNode<T>* pnode, T key, int driction) const
{
}

template<typename T>
inline void AVLTree<T>::destory(AVLTreeNode<T>*& pnode) const
{
	if (pnode != nullptr)
	{
		destory(pnode->lchild);
		destory(pnode->rchild);
		delete pnode;
		pnode = nullptr;
	}
}
/*
	插入操作
	返回插入后的根节点
*/
template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::insert(AVLTreeNode<T>*& pnode, T key)
{
	//寻找插入位置
	if (pnode == nullptr)
	{
		pnode = new AVLTreeNode<T>(key, nullptr, nullptr);
	}
	else if (key > pnode->key)
	{
		pnode->rchild = insert(pnode->rchild, key);
		//插入到右节点后失衡
		if (height(pnode->rchild) - height(pnode->lchild) == 2)
		{
			//插入右子树的右节点,左旋
			if (key > pnode->rchild->key)
				pnode = leftRotation(pnode);
			//插入右子树的左节点,先右旋后左旋
			else if (key < pnode->rchild->key)
				pnode = rightLeftRotation(pnode);
		}
	}
	else if (key < pnode->key)
	{
		pnode->lchild = insert(pnode->lchild, key);
		//插入到左节点后失衡
		if (height(pnode->lchild) - height(pnode->rchild) == 2)
		{
			//插入到左子树的左节点,右旋
			if (key < pnode->lchild->key)
				pnode = leftRotation(pnode);
			//插入到左子树的右节点,先左旋后右旋
			else if (key > pnode->lchild->key)
				pnode = leftRightRotation(pnode);
		}
	}

	pnode->height = max(height(pnode->lchild), height(pnode->rchild)) + 1;
	return pnode;
}

/*
	四种失衡调整
	类型			使用情形
	单左旋		在左子树插入左孩子节点，使得平衡因子绝对值由1增至2
	单右旋		在右子树插入右孩子节点，使得平衡因子绝对值由1增至2
	先左旋后右旋	在左子树插入右孩子节点，使得平衡因子绝对值由1增至2
	先右旋后左旋	在右子树插入左孩子节点，使得平衡因子绝对值由1增至2
*/
template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::remove(AVLTreeNode<T>*& pnode, T key)
{
	if (pnode != nullptr)
	{
		if (pnode->key == key)
		{
			//维护AVL树有序
			if (pnode->rchild != nullptr && pnode->lchild != nullptr)
			{
				//左子树比右子树高,在左子树上选择节点替换
				if (height(pnode->lchild) > height(pnode->rchild))
				{
					//用左子树最大节点替换被删除节点，删除最大节点
					AVLTreeNode<T>* left_max_node = maximum(pnode->lchild);
					pnode->key = left_max_node->key;			//left_max_node的值覆盖被删除节点的值
					
					//递归删除最大节点
					pnode->lchild = remove(pnode->lchild, left_max_node->key);
				}
				else
				{
					//在右子树上选择节点替换
					//用右子树最小节点替换被删除节点，删除最小节点
					AVLTreeNode<T>* right_min_node = minimum(pnode->rchild);
					pnode->key = right_min_node->key;

					pnode->rchild = remove(pnode->rchild, right_min_node->key);
				}
			}
			else
			{
				AVLTreeNode<T>* temp_node = pnode;
				if (pnode->lchild != nullptr)
					pnode = pnode->lchild;
				else if (pnode->rchild != nullptr)
					pnode = pnode->rchild;

				delete temp_node;
				return nullptr;
			}
		}
		else if (pnode->key < key)
		{
			pnode->rchild = remove(pnode->rchild, key);
			//删除右子树节点导致不平衡
			if (height(pnode->lchild) - height(pnode->rchild) == 2)
			{
				//在左子树上插入右节点导致失衡
				if (height(pnode->lchild->rchild) > height(pnode->lchild->lchild))
					pnode = leftRightRotation(pnode);
				else	//在左子树插入右节点导致失衡
					pnode = rightRotation(pnode);
			}
		}
		else if (pnode->key > key)
		{
			pnode->lchild = remove(pnode->lchild, key);
			//删除左节点导致不平衡
			if (height(pnode->rchild) - height(pnode->lchild) == 2)
			{
				//在右子树上插入左节点导致失衡
				if (height(pnode->rchild->lchild) > height(pnode->rchild->rchild))
					pnode = rightLeftRotation(pnode);
				else		//在右子树上插入右节点
					pnode = leftRotation(pnode);
			}
		}
		return pnode;
	}
	return nullptr;
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::minimum(AVLTreeNode<T>* pnode) const
{
	if (pnode != nullptr)
	{
		while (pnode->lchild != nullptr)
			pnode = pnode->lchild;
		return pnode;
	}
	return nullptr;
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::maximum(AVLTreeNode<T>* pnode) const
{
	if (pnode != nullptr)
	{
		while (pnode->rchild != nullptr)
			pnode = pnode->rchild;
		return pnode;
	}
	return nullptr;
}

template<typename T>
inline int AVLTree<T>::height(AVLTreeNode<T>* pnode)
{
	if (pnode != nullptr)
	{
		return pnode->height;
	}
	return 0;
}

template<typename T>
inline int AVLTree<T>::max(int a, int b)
{
	return (a > b ? a : b);
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::search_recurse(AVLTreeNode<T>* pnode, T key) const
{
	if (pnode != nullptr)
	{
		if (key == pnode)
			return pnode;
		else if (key > pnode)
			return search_recurse(pnode->rchild, key);
		else
			return search_recurse(pnode->lchild, key);
	}
	return nullptr;
}

template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::search_iterator(AVLTreeNode<T>* pnode, T key) const
{
	while (pnode != nullptr)
	{
		if (pnode->key == key)
			return pnode;
		else if (pnode->key < key)
			pnode = pnode->rchild;
		else
			pnode = pnode->lchild;
	}
	return nullptr;
}

/*
	左旋操作
	插入情况"在右子树插入右孩子导致AVL失衡"
	pnode为最小失衡子树的根节点
	返回旋转后的根节点
*/
template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::leftRotation(AVLTreeNode<T>* pnode)
{
	AVLTreeNode<T>* root_node = pnode;
	AVLTreeNode<T>* rchild_node = root_node->rchild;
	root_node->rchild = rchild_node->lchild;
	rchild_node->lchild = root_node;

	root_node->height = max(height(root_node->lchild), height(root_node->rchild)) + 1;
	rchild_node->height = max(height(rchild_node->lchild), height(rchild_node->rchild)) + 1;
	
	return rchild_node;
}

/*
	右旋操作
	插入情况是“在左子树上插入左孩子导致AVL树失衡”
	pnode为最小失衡子树的根节点
	返回旋转后的根节点
*/
template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::rightRotation(AVLTreeNode<T>* pnode)
{
	AVLTreeNode<T>* root_node = pnode;
	AVLTreeNode<T>* lchild_node = root_node->lchild;
	root_node->lchild = lchild_node->rchild;
	lchild_node->rchild = root_node;

	root_node->height = max(height(root_node->lchild), height(root_node->rchild)) + 1;
	lchild_node->height = max(height(lchild_node->lchild), height(lchild_node->rchild)) + 1;

	return lchild_node;

}

/*
	先右旋后左旋
	插入情况是"在右子树上插入左孩子导致AVL树失衡"
	pnode为最小失衡子树的根节点
	返回旋转后的根节点
*/
template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::leftRightRotation(AVLTreeNode<T>* pnode)
{
	AVLTreeNode<T>* rchild_node = rightRotation(pnode->rchild);
	pnode->rchild = rchild_node;
	return leftRotation(pnode);
}

/*
	先左旋后右旋
	在左子树上插入右孩子导致AVL树失衡
	pnode为最小失衡子树跟节点
	返回旋转后的根节点
*/
template<typename T>
inline AVLTreeNode<T>* AVLTree<T>::rightLeftRotation(AVLTreeNode<T>* pnode)
{
	AVLTreeNode<T>* lchild_node = leftRotation(pnode->lchild);
	pnode->lchild = lchild_node;
	return rightRotation(pnode);
}