#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "FreqArray.h"
using namespace std;

int main()
{
	FreqArray<int> array;

	srand(1);  

	for (int i = 1; i <= 99;i++)
	{
		int test = (rand() % 2 ? -1 : 1)*rand() % 360;
		array.Insert(i,test);
	}

//	array.ArraySort();
    
	array.PrintList();

	cout << endl << array.SeqSearch(361) << endl;
	cout << endl << array.SeqSearch(163) << endl;
	cout << endl << array.SeqSearch(218) << endl;

	array.PrintList();

	cin.get();
	return 0;
}