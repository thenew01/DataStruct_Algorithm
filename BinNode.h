#pragma once

#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��
#define stature(p) ( (p) ? (p)->height : -1 ) //�ڵ�߶�

typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T>
struct BinNode
{
	T data;
	BinNodePosi(T) parent;
	BinNodePosi(T) lchild;
	BinNodePosi(T) rchild;
	int height;
	int npl;	//Null Path Length;��ʽ�ѣ�Ҳ����height����
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
	
	//��������õ���ֱ�Ӻ��
	template <typename T>
	BinNode* succ() { //��λ�ڵ�v��ֱ�Ӻ��
		BinNode* s = this;
		if (rchild) {
			s = rchild; //��������
			while (HasLChild(*s)) s = s->lchild;
		}
		else {
			while (IsRChild(*s)) s = s->parent;
			s = s->parent;
		}

	}

	//template<typename VST> void travLevel(VST&); //��α���
	//template<typename VST> void travPre(VST&);	//ǰ��
	//template<typename VST> void travIn(VST&);	//����
	//template<typename VST> void travPost(VST&);	//����

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


