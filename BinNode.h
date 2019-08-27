#pragma once

template< typename T>
struct BinNode;

#define BinNodePosi(T) BinNode<T>* //节点位置

#define stature(p) ( (p) ? (p)->height : -1 ) //节点高度
#include <cstddef>

typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T>
struct BinNode
{
	T data;
	BinNode* parent;
	BinNode* lchild;
	BinNode* rchild;
	int height;
	int npl;	//Null Path Length;左式堆，也可用height代替
	RBColor color;
	BinNode() : parent(NULL), lchild(NULL), rchild(NULL), height(0), npl(1), color(RB_RED)
	{ }

	BinNode(T e, BinNode<T>* p = NULL, BinNode<T>* lc = NULL, BinNode<T>* rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lchild(lc), rchild(rc), height(h), npl(l), color(c)
	{ }

	//int size() { return };
	BinNode<T>* insertAsLC(T const& e) { return lchild = new BinNode(e, this); }
	BinNode<T>* insertAsRC(T const& e) { return rchild = new BinNode(e, this); }
	
	//中序遍历用到的直接后继
	BinNode* succ() { //定位节点v的直接后继
		BinNode* s = this;
		if (rchild) {
			s = rchild; //右子树中
			while (HasLChild(*s)) s = s->lchild;
		}
		else {
			while (IsRChild(*s)) s = s->parent;
			s = s->parent;
		}

	}

	//template<typename VST> void travLevel(VST&); //层次遍历
	//template<typename VST> void travPre(VST&);	//前序
	//template<typename VST> void travIn(VST&);	//中序
	//template<typename VST> void travPost(VST&);	//后序

	//template <typename VST>
	//void travIn(VST& visit) {
	//	switch (rand() % 5)
	//	{
	//	case 1:
	//		travIn_I1(this, visit);break;
	//	case 2:
	//		travI_I2(this, visit);break;
	//	case 3:
	//		travIn_I3(this, visit); break;
	//	case 4:
	//		travIn_I4(this, visit);break;
	//	default:
	//		travIn_I5(this, visit);break;
	//	}
	//}
	//
	bool operator<(BinNode const& bn) { return data < bn.data; }
	bool operator==(BinNode const& bn) { return data == bn.data; }

};

#define IsRoot(x) (!((x).parent))
#define IsLChild(x) ( !IsRoot(x) && ( &(x) == (x).parent->lchild ) )
#define IsRChild(x) ( !IsRoot(x) && ( &(x) == (x).parent->rchild ) )
#define HasParent(x) ( !IsRoot(x) )
#define HasLChild(x) ( (x).lchild )
#define HasRChild(x) ( (x).rchild )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) )
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) )
#define IsLeaf(x) ( !HasChild(x) )
#define sibling(p) ( IsLChild( *(p) ) ? (p)->parent->rchild : (p)->lchild )
#define uncle(p) ( IsLChild( *((p)->parent) ) ? (x)->parent->rchild : (x)->parent->lchild )
#define FromParentTo(x) ( \
			IsRoot(x) ? _root : \
			( IsLChild(x) ? (x).parent->lchild : (x).parent->rchild ) \
			) 


