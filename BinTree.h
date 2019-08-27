#pragma once


#include "BinNode.h"
#include <stack>
using namespace std;

template <typename T> 
class BinTree
{
private:
	int _size;
	BinNode<T>* _root;
	virtual int updateHeight(BinNode<T>* x) {
		return x->height = 1 + max(stature(x->lchild), stature(x->rchild));
	}
	void updateHeightAbove(BinNode<T>* x) {
		while (x) {
			updateHeight(x);
			x = x->parent;
		}
	}

public:
	BinTree() :_size(0), _root(nullptr){}
	virtual ~BinTree()
	{
		if (_size > 0) remove(_root);
	}
	
	int size() const {
		return _size;
	}
	bool empty() { return !_root; }

	BinNode<T>* root() { return _root; }

	BinNode<T>* invertAsRoot(T const& e) {
		_size = 1; return _root = new BinNode<T>(e);
	}
	
	BinNode<T>* insertAsLC(BinNode<T>* x, T const& e) {
		_size++; x->insertAsLC(e);
		updateHeightAbove(x);
		return x->lchild;
	}
	
	BinNode<T>* insertAsRC(BinNode<T>* x, T const& e) {
		_size++;
		x->insertAsRC(x);
		updateHeightAbove(x);
		return x->rchild;
	}

	BinNode<T>* attachAsLC(BinNode<T>* x, BinTree<T>* &t) {
		if (x->lchild = t._root)
			x->lchild->parent = x;
		_size += t->_size;
		updateHeightAbove(x);
		t->_root = nullptr;
		t->_size = 0;
		release(t);
		t = nullptr;
		return x;
	}
	BinNode<T>* attachAsRC(BinNode<T>* x, BinTree<T>*& t) {
		if (x->rchild = t->_root)
			x->rchild->parent = x;
		_size += t->_size;
		updateHeightAbove(x);
		t->_root = nullptr;
		t->_size = 0;
		release(t);
		t = nullptr;
		return x;
	}
	
	int remove(BinNode<T>* x) {
		FromParentTo(*x) = nullptr;
		updateHeightAbove(x->parent);
		int n = removeAt(x);
		_size -= n;
		return n;
	}

	static int removeAt(BinNode<T>* x) {
		if (!x) return 0;
		int n = 1 + removeAt(x->lchild) + removeAt(x->rchild);
		release(x->data);
		release(x);
		return n;
	}
	//摘除为一颗独立子树
	BinTree<T>* secede(BinNode<T>* x) {
		FromParentTo(x) = nullptr;
		updateHeightAbove(x->parent);
		BinTree<T>* S = new BinTree<T>;
		S->_root = x;
		x->parent = NULL;
		S->_size = x->size();
		_size -= S->_size;
		return S;
	}

	template < typename VST>
	void travLevel(VST* visit) {
		if (_root) _root->travLevel(visit);
	};

	template <typename VST>
	void travPre(VST* visit) {
		if (_root) _root->travPre(visit);
	}

	template <typename VST>
	void travIn(VST* visit) {
		if (_root) _root->travIn(visit);
	}

	template <typename VST>
	void travPost(VST* visit) {
		if (_root) _root->travPost(visit);
	}

	//递归遍历
	template < typename VST>
	void travPre_R(BinNode<T>* x, VST& visit) {
		if (!x) return;
		visit(x->data);
		travPre_R(x->lchild, visit);
		travPre_R(x->rchild, visit);
	}

	template < typename VST>
	void travPost_R(BinNode<T>* x, VST& visit) {
		if (x == nullptr)
			return;

		travPost_R(x->lchild, visit);
		travPost_R(x->rchild, visit);
		visit(x->data);
	}

	template < typename VST>
	void travIn_R(BinNode<T>* x, VST& visit) {
		if (x == nullptr)return;
		travIn_R(x->lchild, visit);
		visit(x->data);
		travIn_R(x->rchild, visit);
	}

	//迭代遍历
	template < typename VST>
	void travPre_I2(BinNode<T>* x, VST& visit) {
		stack<BinNode<T>*> s;
		while (true) {
			visitAlongLeftBranch(x, visit, s);
			if( s.empty()) break;
			x = s.pop();
		}
	}

	
	static void visitAlongLeftBranch(BinNode<T>* x, stack<BinNode<T>*> s) {
		while (x) {
			visit(x->data);
			s.push(x->rchild);
			x = x->lchild;
		}
	}

	template <typename VST>
	void travIn_I1(BinNode<T>* x, VST& visit) {
		stack<BinNode<T>*> s;
		while (true) {
			goAlongLeftBranch(x, s);
			if (s.empty()) break;
			x = s.pop();
			visit(x->data);
			x = x->rchild;
		}
	}

	template < typename VST>
	static void goAlongLeftBranch(BinNode<T>* x, stack<BinNode<T>*>& S) {
		while (x)
		{
			S.push(x);
			x = x->lchild;
		}
	}

	template < typename VST>
	void travIn_I2(BinNode<T>* x, VST& visit) {
		stack<BinNode<T>* > s;
		while (true)
		{
			if (x) {
				s.push(x);
				x = x->lchild;
			}
			else if (!s.empty()) {
				x = s.pop();
				visit(x->data);
				x = x->rchild;
			}
			else
				break;
		}
	}

	template <typename VST>
	void travIn_I3(BinNode<T>* x, VST& visit) {
		bool backtrack = false;
		while (true) {
			if (!backtrack && HasLChild(*x)) {
				x = x->lchild;
			}
			else {
				visit(x->data);
				if (HasRChild(*x)) {
					x = x->rchild;
					backtrack = false;
				}
				else {
					if( !(x = x->succ()) ) break;
					backtrack = true;
				}
			}
		}
	}

	static void gotoHeighestLeafVisibleFromLeft(stack<BinNode<T>*> S )
	{
		while( BinNode<T> * x = S.top)
		{
			if( HasLChild(*x))
			{
				if (HasRChild(*x)) S.push(x->rchild);
				S.push(x->lchild);
			}
			else
			{
				S.push(x->rchild);
			}
		}
		S.pop();
	}

	template < typename VST>
	void travPost_I(BinNode<T>* x, VST& visit)
	{
		stack<BinNode<T>*> S;
		if (x) S.push(x);
		while(!S.empty())
		{
			if (S.top() != x->parent)
				gotoHeighestLeafVisibleFromLeft(S);
			x = S.top;
			visit(x->data);
		}
	}
	

	bool  operator<(BinTree<T> const& t) {
		return _root && t.root && lt(_root, t._root);
	}
	bool operator==(BinTree<T> const& t) {
		return _root && t._root && _root == t._root;
	}

private:

};
