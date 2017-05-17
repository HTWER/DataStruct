#include "OrderTree.h"

int main()
{
	OrderTree<char> test;     
	test.ConstructByCin();	//��������A B # D # # C # #

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
	test.LeverOrder();
	cout << endl;

	system("pause");
	return 0;
}