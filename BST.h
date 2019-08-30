#pragma once

#include "BinTree.h"

template <typename T>
class BST : public BinTree<T>
{
protected:
	BinNode<T>* _hot;

	/*
	 *		 b
		a			c
	T0		T1	T2		T3
	 */
	BinNode<T>* connect34(
		BinNode<T>* a, BinNode<T>* b, BinNode<T>* c,
		BinNode<T>* T0, BinNode<T>* T1, BinNode<T>* T2,BinNode<T>* T3)
	{
		a->lchild = T0;	if (T0) T0->parent = a;
		a->rchild = T1;	if (T1) T1->parent = a; this->updateHeight(a);		
		c->lchild = T2;	if (T2) T2->parent = c;
		c->rchild = T3;	if (T3) T3->parent = c;	this->updateHeight(c);
		b->lchild = a; a->parent = b;
		b->rchild = c; c->parent = b; this->updateHeight(b);
		return b;
	}

	BinNode<T>* rotateAt(BinNode<T>* v)
	{
		BinNode<T>* p = v->parent;
		BinNode<T>* g = p->parent;
		if( IsLChild(*p)) //zig
		{
			if( IsLChild(*v)) //zig-zig
			{
				p->parent = g->parent;
				return connect34(v, p, g, v->lchild, v->rchild, p->rchild, g->rchild);
			}
			else //v is right child ,zig-zag
			{
				v->parent = g->parent;
				return connect34(p, v, g, p->lchild, v->lchild, v->rchild, g->rchild);
			}
		}
		else // p is right child
		{
			if( IsLChild(*v))
			{
				v->parent = g->parent;
				return connect34(g, v, p, g->lchild, v->lchild, v->rchild, p->rchild);
			}
			else //v is right child.zag-zag
			{
				p->parent = g->parent;
				return connect34(g, p, v, g->lchild, p->lchild, v->lchild, v->rchild);
			}
		}
	}
public:
	BST() { _hot = nullptr; }
	virtual BinNode<T>*& search(const T& e)
	{
		return searchIn(this->_root, e, _hot = nullptr);
	}
	virtual BinNode<T>* insert(const T& e)
	{
		BinNode<T>*& x = search(e);
		if (x)
			return x;
		this->_size++;
		x = new BinNode<T>(e, _hot);
		this->updateHeightAbove(x);
		return  x;
	}
	virtual bool remove(const T& e)
	{
		BinNode<T>*& x = search(e);
		if (x == nullptr)
			return false;
		removeAt(x, _hot);
		this->_size--;
		this->updateHeightAbove(_hot);
		return true;
	}

	static BinNode<T>* removeAt(BinNode<T>*& x, BinNode<T>*& hot)
	{
		BinNode<T>* w = x;
		BinNode<T>* succ = nullptr;
		if (!HasLChild(*x))
			succ = x = x->rchild;
		else if (!HasRChild(*x))
			succ = x = x->lchild;
		else
		{
			w = w->success();
			swap(x->data, w->data);
			BinNode<T>* u = w->parent;
			((u == x) ? u->rchild : u->lchild) = succ = w->rchild;
		}
		hot = w->parent;
		if (succ) succ->parent = hot;
		//release(w->data);
		release(w);
		return succ;
	}
	
	static BinNode<T>*& searchIn( BinNode<T>*& v, const T& e, BinNode<T>*& hot)
	{
		if (v == nullptr || e == v->data)
			return v;
		hot = v;
		return searchIn( ( ( e < v->data ) ? v->lchild : v->rchild ), e, hot);
	}

	
};