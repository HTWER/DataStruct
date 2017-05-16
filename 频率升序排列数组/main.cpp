#include "FreqArray.h"
using namespace std;

int main()
{
	FreqArray<int> array;

	array.Insert(1, 3);
	array.Insert(1, 4);
	array.Insert(3, 5);
	array.Insert(2, 6);
	array.PrintList();

	cout << array.Get(1) << endl;;
	cout << array.Delete(2) << endl;

	array.PrintList();
	cout << array.Locate(3) << endl;
	cout << array.Locate(6) << endl;

	cout << array.SeqSearch(3) << endl;
	cout << array.SeqSearch(6) << endl;

	array.PrintList();

	system("pause");
	return 0;
}