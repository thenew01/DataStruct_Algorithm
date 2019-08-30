#pragma once
#include "BST.h"

#define Balanced(x) ( stature((x).lchild) == stature((x).rchild ) )	//����ƽ������
#define BalFactor(x) ( stature((x).lchild) - stature((x).rchild ) )		//ƽ������
#define AvlBalanced(x) ( -2 < BalFactor(x) ) && ( BalFactor(x) < 2)	//AVLƽ������

#define tallerChild(x) (\
	stature((x)->lchild) > stature((x)->rchild) ? (x)->lchild : (\
	stature((x)->rchild) > stature((x)->lchild) ? (x)->rchild : \
	( IsLChild( *(x) ) ? (x)->lchild : (x)->rchild )\
	)\
	)

template <typename T>
class AVL: public BST<T>
{
public:
	BinNode<T>* insert(const T& e)
	{
		BinNode<T>* x = this->search(e);
		if (x)
			return x;
		x = new BinNode<T>(e, this->_hot);
		this->_size++;
		for ( BinNode<T>* g = this->_hot; g; g = g->parent)
		{
			if (!AvlBalanced(*g))
			{
				FromParentTo(*g) = this->rotateAt(tallerChild((tallerChild(g))));
				break; //�������׺������͸��׾��ָ�ƽ��
			}
			else
			{
				this->updateHeight(g);
			}
		}
		return x;
	}
	bool remove(const T& e)
	{
		BinNode<T>*& x = this->search(e);
		if (x == nullptr)
			return false;
		this->removeAt(x, this->_hot);
		this->_size--;
		for (BinNode<T>* g = this->_hot; g; g = g->parent)
		{
			if( !AvlBalanced(*g) )
			{
				g = FromParentTo(*g) = this->rotateAt(tallerChild((tallerChild(g))));
			}
			this->updateHeightAbove(g);
		}

		return true;
	}
};

