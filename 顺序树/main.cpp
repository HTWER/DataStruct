#include "OrderTree.h"

int main()
{
	OrderTree<char> test;     
	//test.LevelConstructByCin();	//��������A B C # D
	test.PreConstructByCin();		//��������A B # D # # C # #

	cout << "ǰ������� ";
	test.PreOrder();
	cout << endl;

	cout << "��������� ";
	test.InOrder();
	cout << endl;

	cout << "��������� ";
	test.PostOrder();
	cout << endl;

	cout << "��������� ";
	test.LevelOrder();
	cout << endl;

	system("pause");
	return 0;
}