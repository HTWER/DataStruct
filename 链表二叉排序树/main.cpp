#include "LinkedBinarySortTree.h"

int main()
{
	//测试二叉排序树
	 int a[10] = { 63, 55, 90, 58, 70, 42, 10, 45, 83, 67 };
	 LinkedBinarySortTree<int> tree(a, 10);

	 tree.InsertBST(100);

	 tree.DeleteBST(90);

	 TreeNode<int> * res = tree.SearchBST(70);
	 cout << res->data << endl;

	 cout << "递归前序遍历：  ";
	 tree.PreOrder();
	 cout << endl;

	 cout << "非递归前序遍历：";
	 tree.PreOrderfd();
	 cout << endl;

	 cout << "递归中序遍历：  ";
	 tree.InOrder();
	 cout << endl;

	 cout << "非递归中序遍历：";
	 tree.InOrderfd();
	 cout << endl;

	 cout << "递归后序遍历：  ";
	 tree.PostOrder();
	 cout << endl;

	 cout << "非递归后序遍历：";
	 tree.PostOrderfd();
	 cout << endl;

	 cout << "层序遍历：      ";
	 tree.LeverOrder();
	 cout << endl;

	system("pause");
	return 0;
}