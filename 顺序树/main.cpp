#include "OrderTree.h"

int main()
{
	OrderTree<char> test;     
	//test.LevelConstructByCin();	//测试数据A B C # D
	test.PreConstructByCin();		//测试数据A B # D # # C # #

	cout << "前序遍历： ";
	test.PreOrder();
	cout << endl;

	cout << "中序遍历： ";
	test.InOrder();
	cout << endl;

	cout << "后序遍历： ";
	test.PostOrder();
	cout << endl;

	cout << "层序遍历： ";
	test.LevelOrder();
	cout << endl;

	system("pause");
	return 0;
}