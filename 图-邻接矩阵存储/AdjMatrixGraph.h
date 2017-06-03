#include <iostream>
#include <memory.h>
#include <queue>
#include <stack>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

/*
用邻接矩阵存储图：
由于矩阵本身的增删元素不方便，这里不实现图的增删操作（顶点的增删操作非常麻烦）
*/

/*
概念：
子图：V和E都是原图的子集的图
生成树：包含所有顶点的无环连通子图，无自环；无重边；对吧？？？
生成树的概念与是否有权图无关
无向图如果是连通的，那么一定有生成树；否则一定没有生成树；
有向图如果是强连通的，那么一定有生成树；弱连通无法确定是否有生成树；不连通则一定没有生成树；
*/

#define BUFFERSIZE 512

template <class DataType>
class MGraph
{

public:

	MGraph(DataType a[], int n, bool m_isDirected, bool m_isWeighted);
	~MGraph(){};

	//遍历算法：仅能遍历v顶点所在的连通分量
	void DFSTraverse(int v);
	void DFSTraversefd(int v);
	void BFSTraverse(int v);

	//以下算法主要讨论简单图：无环无重边

	//最小生成树算法：就算所有边的权值总和最小的生成树；
	//调用函数前保证图是无向连通有权图即可，即使原图有自环以及重边(prim需稍加修改)也可以正确得到结果；
	//边的权值可以为负
	void Prim();
	void Kruskal();

	//最短寻路算法：求从v点到其它所有点的最短路径
	//有向图和无向图都可以使用
	//边的权值不可以为负
	void Dijkstra(int v);

private:

	//Kruskal用到
	struct edge
	{
		int from, to;
		int weight;
		static bool cmp(edge a, edge b)
		{
			return a.weight < b.weight;
		}
	};

	//编号对应的实际数据	
	vector<DataType> m_vertexData;

	//结点之间的(无权图)连接关系或边之间的(有权图)权重关系(或者说是代价)；
	//这个写法不好，因为有权图和无权图都要用同一个数据结构；
	//（原本）无权图：0 没连接，1 有连接
	//有权图：无穷大 没连接，其余 有链接
	//为了统一后面的遍历算法，委屈一下无权图，改成无穷大 没连接，其余 有连接
	//这个矩阵只能记录两点之间的一条边，所以这个数据没办法表示两顶点间的多条边
	vector<vector<int>> m_edge;

	//访问记录
	vector<bool> m_visited;

	bool m_isDirected;							//是否有向图            
	bool m_isWeighted;							//是否有权图
	int m_vertexNum;							//点数
	int m_edgeNum;								//边数

	void ClearVisited();						//清空访问记录
	void DFSTraverseKernel(int v);
	int FindRoot(vector<int>& parent, int v);	//判断顶点所属的连通分量
};

//数组a存储着实际的数据，数据直接的联系需要由用户后续输入
//如果想要手动输入边的数据，将此函数中的所有ss改成cin即可
template <class DataType>
MGraph<DataType>::MGraph(DataType a[], int n, bool isDirected, bool isWeighted)
{
#if 1
	//测试数据流，测试prim
	string test = "9 0 1 34 1 4 12 0 5 19 4 5 26 0 2 46 2 5 25 3 5 25 3 4 38 2 3 17";
#endif

#if 0
	//测试数据流，测试Djikstra
	//string test = "7 0 1 10 1 2 50 0 3 30 2 4 10 0 4 100 3 2 20 3 4 60";
#endif
	
	stringstream ss(test);

	//初始化
	m_vertexNum = n;
	m_isDirected = isDirected;
	m_isWeighted = isWeighted;
	ClearVisited();

	//保存实际数据
	for (int i = 0; i < m_vertexNum; i++)
		m_vertexData.push_back(a[i]);

	//初始化边之间的关系
	m_edge.resize(m_vertexNum);
	for (int i = 0; i < m_vertexNum; ++i)
		m_edge[i].resize(m_vertexNum, INT_MAX);
	for (int i = 0; i < m_vertexNum; ++i)
		m_edge[i][i] = 0;

	//输入节点之间的关系
	cout << "请输入边数：";
	ss >> m_edgeNum;
	cout << "请输入边信息：" << endl;
	cout << "格式: 起点编号 中点编号 权重 " << endl;
	cout << "权重 需要根据图的类型选择性输入" << endl;

	int from, to, weight;
	//每次处理一条边的信息
	for (int i = 0; i < m_edgeNum; i++)
	{
		if (m_isWeighted)
		{
			ss >> from >> to >> weight;
			m_edge[from][to] = weight;
		}
		else
		{
			ss >> from >> to;
			m_edge[from][to] = 1;
		}

		if (!m_isDirected)
		{
			if (m_isWeighted)
				m_edge[to][from] = weight;
			else
				m_edge[to][from] = 1;
		}
	}
}

template <class DataType>
void MGraph<DataType>::DFSTraverse(int v)
{
	ClearVisited();
	DFSTraverseKernel(v);
}

template <class DataType>
void MGraph<DataType>::DFSTraverseKernel(int v)
{
	cout << m_vertexData[v] << " ";
	m_visited[v] = true;

	for (int i = 0; i < m_vertexNum; ++i)
	{
		if (m_edge[v][i] != INT_MAX && !m_visited[i])
			DFSTraverseKernel(i);
	}
}

template <class DataType>
void MGraph<DataType>::DFSTraversefd(int v)
{
	ClearVisited();

	cout << m_vertexData[v] << " ";
	m_visited[v] = true;

	stack<int> stackv;
	stackv.push(v);

	int num;
	while (!stackv.empty())
	{
		num = stackv.top();

		int i;
		for (i = 0; i < m_vertexNum; i++)
		{
			if (m_edge[num][i] != INT_MAX && !m_visited[i])
				break;
		}

		if (i == m_vertexNum)
			stackv.pop();
		else
		{
			cout << m_vertexData[i] << " ";
			m_visited[i] = true;
			stackv.push(i);
		}
	}
}

template <class DataType>
void MGraph<DataType>::BFSTraverse(int v)
{
	ClearVisited();

	//一定要入栈前要先进行访问
	cout << m_vertexData[v] << " ";
	m_visited[v] = true;

	queue<int> queuev;
	queuev.push(v);

	while (!queuev.empty())
	{
		int head = queuev.front();
		queuev.pop();

		for (int i = 0; i < m_vertexNum; ++i)
		{
			if (m_edge[head][i] != INT_MAX &&!m_visited[i]){
				cout << m_vertexData[i] << " ";
				m_visited[i] = true;
				queuev.push(i);
			}
		}
	}
}

template <class DataType>
void MGraph<DataType>::ClearVisited()
{
	m_visited.resize(0);
	m_visited.resize(m_vertexNum, false);
}

template <class DataType>
void MGraph<DataType>::Prim()
{
	vector<int> vertexOfRes;
	vector<int> vertexOfOri;

	//先将其中一个顶点放进结果中
	vertexOfRes.push_back(0);
	for (int i = 1; i < m_vertexNum; ++i)
		vertexOfOri.push_back(i);

	for (int count = 0; count < m_vertexNum - 1;++count)
	{
		//查找出res的点到Ori的点的最小权值边
		int indexOfVertexInRes = 0;
		int indexOfVertexInOri = 0;
		int minWeight = INT_MAX;
		for (int i = 0; i < vertexOfRes.size(); ++i)
		{
			for (int j = 0; j < vertexOfOri.size(); ++j)
			{
				if (m_edge[vertexOfRes[i]][vertexOfOri[j]] < minWeight)
				{
					minWeight = m_edge[vertexOfRes[i]][vertexOfOri[j]];
					indexOfVertexInRes = i;
					indexOfVertexInOri = j;
				}
			}
		}

		//输出当前先连接上的边
		cout << "#" << vertexOfRes[indexOfVertexInRes] << " 连接 " << "#" << vertexOfOri[indexOfVertexInOri] << " 权值为：" << minWeight << endl;
			
		//将找到的Ori的点调换到Res中
		vertexOfRes.push_back(vertexOfOri[indexOfVertexInOri]);
		vertexOfOri.erase(vertexOfOri.begin()+indexOfVertexInOri);
	}
}

template <class DataType>
void MGraph<DataType>::Kruskal()
{
	//将所有边的信息都保存到一个数组中
	vector<edge> edges;
	for (int i = 0; i < m_vertexNum; ++i)
	{
		for (int j = 0; j < m_vertexNum;++j)
		{
			if (m_edge[i][j] != INT_MAX)
			{
				edge temp;
				temp.from = i;
				temp.to = j;
				temp.weight = m_edge[i][j];
				edges.push_back(temp);
			}
		}
	}

	//对所有的边按照权值从小到大进行排序
	sort(edges.begin(), edges.end(), edge::cmp);

	//创建数组记录每一个顶点的父亲
	//用于后面判断两个顶点在已找出的边中是否属于同一个连通分量
	//parent[i] = j;代表i顶点的父亲为j
	vector<int> parent;
	for (int i = 0; i < m_vertexNum;++i)
		parent.push_back(-1);

	//遍历排好序的边的数组
	int count = 0;				
	for (int i = 0; i < edges.size();++i)
	{
		edge temp = edges[i];

		//查找当前检查的边的顶点是否属于用一个连通分量
		int vex1 = FindRoot(parent, temp.from);
		int vex2 = FindRoot(parent, temp.to);

		//若不属于同一连通分量,则该边属于最小生成树的一条边
		if (vex1 != vex2)
		{
			cout << "#" << temp.from << " 连接到 " << "#" << temp.to << " 权值为：" << temp.weight << endl;
			parent[vex2] = vex1;	//vex2和vex1的位置可以交换

			++count;				//记录已找到的边数
			if (count == m_vertexNum - 1)
				break;
		}
	}
}

template <class DataType>
int MGraph<DataType>::FindRoot(vector<int>& parent, int v)
{
	while (parent[v] != -1)
		v = parent[v];
	return v;
}

template <class DataType>
void MGraph<DataType>::Dijkstra(int v)
{
	int *dist = new int[m_vertexNum];			//从v点到所有顶点的最短路径值
	string *path = new string[m_vertexNum];		//从v点到所有顶点的最短路径
	bool *s = new bool[m_vertexNum];			//记录下标对应顶点是否已找到了最短路径
	
	//初始化
	for (int i = 0; i < m_vertexNum; ++i)
	{
		dist[i] = m_edge[v][i];
		if (m_edge[v][i] != INT_MAX)
		{
			char buffer[BUFFERSIZE];
			sprintf_s(buffer, "#%d#%d", v, i);
			path[i] = buffer;
		}
		else
		{
			path[i] = "";
		}
	}

	memset(s, false, m_vertexNum);		//注意：sizeof不可以计算new出来的数组
	s[v] = true;

	//处理剩下的m_vertexNum - 1个顶点
	for (int i = 0; i < m_vertexNum - 1; ++i)
	{
		//寻找s[j]==false且dist[j]值最小的顶点k
		int k;
		for (k = 0; k < m_vertexNum && s[k] == true; ++k);

		for (int j = 0; j < m_vertexNum; ++j)
		{
			if (s[j] == false && dist[j] < dist[k])
				k = j;
		}

		//输出dist[k]，path[k]
		cout << "#" << v << " 到 " << "#" << k << " 最短路径长度：" << dist[k] << " 最短路径：" << path[k] << endl;

		//s登记k
		s[k] = true;		//登记可以放在最后，k点即使不登记，下面循环中的if第三条件在遇上j==k的时候也不会成立

		//用k顶点去连接所有的s[i]==false的顶点i，若得到的数值比原本数值更小，则更新dist[i]和path[i]
		for (int j = 0; j < m_vertexNum; ++j)
		{
			if (s[j] == false && m_edge[k][j]!=INT_MAX && dist[k] + m_edge[k][j] < dist[j])	//第一个条件可以删除，因为如果一个顶点已经找到了最小边，第三个条件一定不成立
			{
				dist[j] = dist[k] + m_edge[k][j];
				char buffer[BUFFERSIZE];
				sprintf_s(buffer, "#%d", j);
				path[j] = path[k] + buffer;
			}
		}
	}
}









