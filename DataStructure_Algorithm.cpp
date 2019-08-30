// DataStructure_Algorithm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "BinTree.h"
#include "bst.h"
#include "AVL.h"

void print(int e)
{
	printf("%d ", e);
}

int main()
{
    std::cout << "Hello World!\n";

	int a[] = { 1, 2, 4, 3, 6, 8, 0, 5, 7, 9 };
	auto tree = new BST<int>;
	auto root0 = tree->invertAsRoot(11);
	auto node = root0;
	for (int i=0;i<sizeof(a)/sizeof(a[0]);i++)
	{
		node = tree->insert(a[i]);
	}
	auto t1 = tree->secede(tree->root()->lchild);
	//auto t2 = tree->secede(tree->root()->rchild);

	tree->travIn(print);
	
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
