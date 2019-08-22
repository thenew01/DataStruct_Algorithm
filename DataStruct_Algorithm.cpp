// DataStruct_Algorithm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>


#define BinNodePosi(T) BinNode<T>* //节点位置
#define stature(p) ((p) ? (p)->height : -1) //节点高度

typedef enum { RB_RED, RB_BLACK } RBColor;

template <typename T>
struct BinNode
{
	T data;
	BinNodePosi(T) parent;
	BinNodePosi(T) lchild;
	BinNodePosi(T) rchild;
	int height;
	int npl;	//Null Path Length;左式堆，也可用height代替
	RBColor color;
	BinNode() : parent(NULL), lchild(NULL), rchild(NULL), height(0), npl(1), color(RB_RED)
	{ }

	BinNode(T e, BinNode<T>* p = NULL, BinNode<T>* lc = NULL, BinNode<T>* rc = NULL,
			int h = 0, int l = 1, RBColor c = RB_RED ) :
		data(e), parent(p),	lchild(lc),	rchild(rc),	height(h), npl(l), color(c)
	{ }

	int size();
	BinNode<T>* insertAsLC(T const& e) { return lchild = new BinNode(e, this); }
	BinNode<T>* insertAsRC(T const& e) { return rchild = new BinNode(e, this); }
	BinNode<T>* succ();

	//template<typename VST> void travLevel(VST&); //层次遍历
	//template<typename VST> void travPre(VST&);	//前序
	//template<typename VST> void travIn(VST&);	//中序
	//template<typename VST> void travPost(VST&);	//后序

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


int main()
{
    //std::cout << "Hello World!\n";



}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
;
