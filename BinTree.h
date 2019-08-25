#pragma once


#include "BinNode.h"

template <typename T> 
class BinTree
{
private:
	int _size;
	BinNode* _root;
	virtual int updateHeight(BinNode* x) {
		return x->height = 1 + max(stature(x->lchild), stature(x->rchild));
	}
	void updateHeightAbove(BinNode* x) {
		while (x) {
			updateHeight(x);
			x = x->parent;
		}
	}

public:
	BinTree() :_size(0), _root(NULL);
	~BinTree() { if (_size > 0) remove(_root); }
	int size() const {
		return _size;
	}
	bool empty() { return !_root; }
	BinNode* root() { return _root; }
	BinNode* invertAsRoot(T const& e) {
		_size = 1; return _root = new BinNode<T>(e);
	}
	BinNode* insertAsLC(BinNode* x, T const& e) {
		_size++; x->insertAsLC(e);
		updateHeightAbove(x);
		return x->lchild;
	}
	
	BinNode* insertAsRC(BinNode* x, T const& e) {
		_size++;
		x->insertAsRC(x);
		updateHeightAbove(x);
		return x->rchild;
	}

	BinNode* attachAsLC(BinNode* x, BinTree<T>* &t) {
		if (x->lchild = t._root)
			x->lchild->parent = x;
		_size += t->_size;
		updateHeightAbove(x);
		t->_root = NULL:
		t->_size = 0;
		release(t);
		t = NULL:
		return x;
	}
	BinNode* attachAsRC(BinNode* x, BinTree<T>*& t) {
		if (x->rchild = t->_root)
			x->rchild->parent = x;
		_size += t->_size;
		updateHeightAbove(x);
		t->_root = NULL:
		t->_size = 0;
		release(t);
		t = NULL:
		return x;
	}
	
	int remove(BinNode* x) {
		FromParentTo(*x) = NULL:
		updateHeightAbove(x->parent);
		int n = removeAt(x);
		_size -= n;
		return n;
	}
	template <typename T>
	static int removeAt(BinNode* x) {
		if (!x) return 0;
		int n = 1 + removeAt(x->lchild) + removeAt(x->rchild);
		release(x->data);
		release(x);
		return n;
	}
	//摘除为一颗独立子树
	BinTree<T>* secede(BinNode* x) {
		FromParentTo(x) = NULL;
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
		if (_root) _root->travLevel(visit) 
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
	template <typename T, typename VST>
	void travPre_R(BinNode* x, VST& visit) {
		if (!x) return;
		visit(x->data);
		travPre_R(x->lchild, visit);
		travPre_R(x->rchild, visit);
	}

	template <typename T, typename VST>
	void travPost_R(BinNode* x, VST& visit) {
		if (x == NULL)
			return;

		travPost_R(x->lchild, visit);
		travPost_R(x->rchild, visit);
		visit(x->data);
	}

	template <typename T, typename VST>
	void travIn_R(BinNode* x, VST& visit) {
		if (x == NULL)return;
		travIn_R(x->lchild, visit);
		visit(x->data);
		travIn_R(x->rchild, visit);
	}

	//迭代遍历
	template <typename T, typename VST>
	void travPre_I2(BinNode* x, VST& visit) {
		stack<BinNode*> s;
		while (true) {
			visitAlongLeftBranch(x, visit, s);
			if( s.empty()) break;
			x = s.pop();
		}
	}

	template <typename T>
	static void visitAlongLeftBranch(BinNode* x, stack<BinNode*> s) {
		while (x) {
			visit(x->data);
			s.push(x->rchild);
			x = x->lchild;
		}
	}

	template <typename T, typename VST>
	void travIn_I1(BinNode* x, VST& visit) {
		stack<BinNode*> s;
		while (true) {
			goAlongLeftBranch(x, s);
			if (s.empty()) break;
			x = s.pop();
			visit(x->data);
			x = x->rchild;
		}
	}

	template <typename T, typename VST>
	static void goAlongLeftBranch(BinNode* x, stack<BinNode*>& S) {
		while (x)
		{
			S.push(x);
			x = x->lchild;
		}
	}

	template <typename T, typename VST>
	void travIn_I2(BinNode* x, VST& visit) {
		stach<BinNode* > s;
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

	template <typename T, typename VST>
	void travIn_I3(BinNode* x, VST& visit) {
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

	bool  operator<(BinTree const& t) {
		return _root && t.root && lt(_root, t._root);
	}
	bool operator==(BinTree const& t) {
		return _root && t._root && _root == t._root;
	}
}
private:

};

BinTree::BinTree()
{
}

BinTree::~BinTree()
{
}