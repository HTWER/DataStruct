#include "InfixToSuffix.h"

int main()
{
	string ori = "-35+7-80+(8*9)+7/-4";      //"3*(4+2)/2-5";
	vector<string> tar;

	tar = InfixToSuffix(ori);
	cout << "²âÊÔ" << CalSuffix(tar) << endl;

	system("pause");
	return 0;
}