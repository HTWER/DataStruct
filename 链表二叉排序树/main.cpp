#include "LinkedBinarySortTree.h"

int main()
{
	//���Զ���������
	 int a[10] = { 63, 55, 90, 58, 70, 42, 10, 45, 83, 67 };
	 LinkedBinarySortTree<int> tree(a, 10);

	 tree.InsertBST(100);

	 tree.DeleteBST(90);

	 TreeNode<int> * res = tree.SearchBST(70);
	 cout << res->data << endl;

	 cout << "�ݹ�ǰ�������  ";
	 tree.PreOrder();
	 cout << endl;

	 cout << "�ǵݹ�ǰ�������";
	 tree.PreOrderfd();
	 cout << endl;

	 cout << "�ݹ����������  ";
	 tree.InOrder();
	 cout << endl;

	 cout << "�ǵݹ����������";
	 tree.InOrderfd();
	 cout << endl;

	 cout << "�ݹ���������  ";
	 tree.PostOrder();
	 cout << endl;

	 cout << "�ǵݹ���������";
	 tree.PostOrderfd();
	 cout << endl;

	 cout << "���������      ";
	 tree.LeverOrder();
	 cout << endl;

	system("pause");
	return 0;
}