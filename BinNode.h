#pragma once
#include <cstddef>

template< typename T>
struct BinNode;

#define BinNodePosi(T) BinNode<T>* //�ڵ�λ��

#define stature(p) ( (p) ? (p)->height : -1 ) //�ڵ�߶�

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
			IsRoot(x) ? this->_root : \
			( IsLChild(x) ? (x).parent->lchild : (x).parent->rchild ) \
			)

#define release(p) { if(p) delete p;}
typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T>
struct BinNode
{
public:
	T data;
	BinNode* parent;
	BinNode* lchild;
	BinNode* rchild;
	int height;
	int npl;	//Null Path Length;��ʽ�ѣ�Ҳ����height����
	RBColor color;
	BinNode() : parent(NULL), lchild(NULL), rchild(NULL), height(0), npl(1), color(RB_RED)
	{ }

	BinNode(T e, BinNode<T>* p = NULL, BinNode<T>* lc = NULL, BinNode<T>* rc = NULL,
		int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), lchild(lc), rchild(rc), height(h), npl(l), color(c)
	{ }

	int size() 
	{
		return 0;
	}

	BinNode<T>* insertAsLC(T const& e) { return lchild = new BinNode(e, this); }
	BinNode<T>* insertAsRC(T const& e) { return rchild = new BinNode(e, this); }
	
	//��������õ���ֱ�Ӻ��
	//BinNode<T>* success(); //��λ�ڵ�v��ֱ�Ӻ��
	BinNode<T>* success() { //��λ�ڵ�v��ֱ�Ӻ��
		BinNode<T>* s = this;
		if (rchild) {
			s = rchild; //��������
			while (HasLChild(*s)) s = s->lchild;
		}
		else {
			while (IsRChild(*s)) s = s->parent;
			s = s->parent;
		}

		return s;
	}


	//template<typename VST> void travLevel(VST&); //��α���
	//template<typename VST> void travPre(VST&);	//ǰ��
	//template<typename VST> void travIn(VST&);	//����
	//template<typename VST> void travPost(VST&);	//����

	template <typename VST>
	void travIn(VST& visit) {
		/*switch (rand() % 5)
		{
		case 1:
			travIn_I1(this, visit); break;
		case 2:
			travIn_I2(this, visit); break;
		case 3:
			travIn_I3(this, visit); break;
		case 4:
			travIn_I4(this, visit); break;
		default:
			travIn_I5(this, visit); break;
		}*/
	}

	bool operator<(BinNode const& bn) { return data < bn.data; }
	bool operator==(BinNode const& bn) { return data == bn.data; }

};



