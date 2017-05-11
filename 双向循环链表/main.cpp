#include "DoubleLinkedCircularList.h"

int main()
{
	int a[10] = { 10,9,8,7,6,5,4,3,2,1 };
	LinkList<int> list(a, 10);
	list.PrintList();

	list.Erase(5);
	list.PrintList();

	list.Insert(5, 100);
	list.PrintList();

	list.PrintList2();

	cout << list.At(6) << endl;
	cout << list.Find(7) << endl;
	cout << list.Length() << endl;

	system("pause");
	return 0;
}