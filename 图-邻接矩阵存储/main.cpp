#include "AdjMatrixGraph.h"

int main()
{

#if 1
	//������С�������㷨
	int a[6] = { 0, 1, 2, 3, 4, 5 };	//�������ݸ� "9 0 1 34 1 4 12 0 5 19 4 5 26 0 2 46 2 5 25 3 5 25 3 4 38 2 3 17";
	MGraph<int>  MM(a, 6, false, true);		
#endif
	
#if 0
	//����Djikstra
	int a[5] = { 0, 1, 2, 3, 4 };		//�������ݸ�"7 0 1 10 1 2 50 0 3 30 2 4 10 0 4 100 3 2 20 3 4 60"
	MGraph<int>  MM(a, 5, true, true);		
#endif
	

	cout << endl;
	cout << "�ݹ�DFS������  ";
	MM.DFSTraverse(0);
	cout << endl;

	cout << endl;
	cout << "�ǵݹ�DFS������";
	MM.DFSTraversefd(0);
	cout << endl;

	cout << endl;
	cout << "BFS������      ";
	MM.BFSTraverse(1);
	cout << endl;

	cout << endl;
	cout << "primʵ�ֵ���С������:" << endl;
	MM.Prim();
	cout << endl;

	cout << endl;
	cout << "Kruskalʵ�ֵ���С������:" << endl;
	MM.Kruskal();
	cout << endl;

	cout << endl;
	cout << "Djikstraʵ�ֵ����·��:" << endl;
	MM.Dijkstra(0);
	cout << endl;

	system("pause");
	return 0;
}