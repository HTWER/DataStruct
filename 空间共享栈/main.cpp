#include "SpaceSharedStake.h"

int main()
{
	SpaceSharedStack<int> test;

	cout << test.IsEmpty(1) << endl;
	cout << test.IsEmpty(2) << endl;

	for (int i = 1; i <= 50;i++)
	{
		test.Push(1, i);
	}

	for (int i = 100; i >= 51; i--)
	{
		test.Push(2, i);
	}

//	test.Push(1, 50);
	
	cout << test.Pop(1) << endl;
	cout << test.Pop(2) << endl;
	cout << test.GetTop(1) << endl;
	cout << test.GetTop(2) << endl;

	cout << test.IsEmpty(1) << endl;
	cout << test.IsEmpty(2) << endl;

	system("pause");
	return 0;
}