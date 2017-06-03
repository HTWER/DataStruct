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
���ڽӾ���洢ͼ��
���ھ��������ɾԪ�ز����㣬���ﲻʵ��ͼ����ɾ�������������ɾ�����ǳ��鷳��
*/

/*
���
��ͼ��V��E����ԭͼ���Ӽ���ͼ
���������������ж�����޻���ͨ��ͼ�����Ի������رߣ��԰ɣ�����
�������ĸ������Ƿ���Ȩͼ�޹�
����ͼ�������ͨ�ģ���ôһ����������������һ��û����������
����ͼ�����ǿ��ͨ�ģ���ôһ����������������ͨ�޷�ȷ���Ƿ���������������ͨ��һ��û����������
*/

#define BUFFERSIZE 512

template <class DataType>
class MGraph
{

public:

	MGraph(DataType a[], int n, bool m_isDirected, bool m_isWeighted);
	~MGraph(){};

	//�����㷨�����ܱ���v�������ڵ���ͨ����
	void DFSTraverse(int v);
	void DFSTraversefd(int v);
	void BFSTraverse(int v);

	//�����㷨��Ҫ���ۼ�ͼ���޻����ر�

	//��С�������㷨���������бߵ�Ȩֵ�ܺ���С����������
	//���ú���ǰ��֤ͼ��������ͨ��Ȩͼ���ɣ���ʹԭͼ���Ի��Լ��ر�(prim���Լ��޸�)Ҳ������ȷ�õ������
	//�ߵ�Ȩֵ����Ϊ��
	void Prim();
	void Kruskal();

	//���Ѱ·�㷨�����v�㵽�������е�����·��
	//����ͼ������ͼ������ʹ��
	//�ߵ�Ȩֵ������Ϊ��
	void Dijkstra(int v);

private:

	//Kruskal�õ�
	struct edge
	{
		int from, to;
		int weight;
		static bool cmp(edge a, edge b)
		{
			return a.weight < b.weight;
		}
	};

	//��Ŷ�Ӧ��ʵ������	
	vector<DataType> m_vertexData;

	//���֮���(��Ȩͼ)���ӹ�ϵ���֮���(��Ȩͼ)Ȩ�ع�ϵ(����˵�Ǵ���)��
	//���д�����ã���Ϊ��Ȩͼ����Ȩͼ��Ҫ��ͬһ�����ݽṹ��
	//��ԭ������Ȩͼ��0 û���ӣ�1 ������
	//��Ȩͼ������� û���ӣ����� ������
	//Ϊ��ͳһ����ı����㷨��ί��һ����Ȩͼ���ĳ������ û���ӣ����� ������
	//�������ֻ�ܼ�¼����֮���һ���ߣ������������û�취��ʾ�������Ķ�����
	vector<vector<int>> m_edge;

	//���ʼ�¼
	vector<bool> m_visited;

	bool m_isDirected;							//�Ƿ�����ͼ            
	bool m_isWeighted;							//�Ƿ���Ȩͼ
	int m_vertexNum;							//����
	int m_edgeNum;								//����

	void ClearVisited();						//��շ��ʼ�¼
	void DFSTraverseKernel(int v);
	int FindRoot(vector<int>& parent, int v);	//�ж϶�����������ͨ����
};

//����a�洢��ʵ�ʵ����ݣ�����ֱ�ӵ���ϵ��Ҫ���û���������
//�����Ҫ�ֶ�����ߵ����ݣ����˺����е�����ss�ĳ�cin����
template <class DataType>
MGraph<DataType>::MGraph(DataType a[], int n, bool isDirected, bool isWeighted)
{
#if 1
	//����������������prim
	string test = "9 0 1 34 1 4 12 0 5 19 4 5 26 0 2 46 2 5 25 3 5 25 3 4 38 2 3 17";
#endif

#if 0
	//����������������Djikstra
	//string test = "7 0 1 10 1 2 50 0 3 30 2 4 10 0 4 100 3 2 20 3 4 60";
#endif
	
	stringstream ss(test);

	//��ʼ��
	m_vertexNum = n;
	m_isDirected = isDirected;
	m_isWeighted = isWeighted;
	ClearVisited();

	//����ʵ������
	for (int i = 0; i < m_vertexNum; i++)
		m_vertexData.push_back(a[i]);

	//��ʼ����֮��Ĺ�ϵ
	m_edge.resize(m_vertexNum);
	for (int i = 0; i < m_vertexNum; ++i)
		m_edge[i].resize(m_vertexNum, INT_MAX);
	for (int i = 0; i < m_vertexNum; ++i)
		m_edge[i][i] = 0;

	//����ڵ�֮��Ĺ�ϵ
	cout << "�����������";
	ss >> m_edgeNum;
	cout << "���������Ϣ��" << endl;
	cout << "��ʽ: ����� �е��� Ȩ�� " << endl;
	cout << "Ȩ�� ��Ҫ����ͼ������ѡ��������" << endl;

	int from, to, weight;
	//ÿ�δ���һ���ߵ���Ϣ
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

	//һ��Ҫ��ջǰҪ�Ƚ��з���
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

	//�Ƚ�����һ������Ž������
	vertexOfRes.push_back(0);
	for (int i = 1; i < m_vertexNum; ++i)
		vertexOfOri.push_back(i);

	for (int count = 0; count < m_vertexNum - 1;++count)
	{
		//���ҳ�res�ĵ㵽Ori�ĵ����СȨֵ��
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

		//�����ǰ�������ϵı�
		cout << "#" << vertexOfRes[indexOfVertexInRes] << " ���� " << "#" << vertexOfOri[indexOfVertexInOri] << " ȨֵΪ��" << minWeight << endl;
			
		//���ҵ���Ori�ĵ������Res��
		vertexOfRes.push_back(vertexOfOri[indexOfVertexInOri]);
		vertexOfOri.erase(vertexOfOri.begin()+indexOfVertexInOri);
	}
}

template <class DataType>
void MGraph<DataType>::Kruskal()
{
	//�����бߵ���Ϣ�����浽һ��������
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

	//�����еı߰���Ȩֵ��С�����������
	sort(edges.begin(), edges.end(), edge::cmp);

	//���������¼ÿһ������ĸ���
	//���ں����ж��������������ҳ��ı����Ƿ�����ͬһ����ͨ����
	//parent[i] = j;����i����ĸ���Ϊj
	vector<int> parent;
	for (int i = 0; i < m_vertexNum;++i)
		parent.push_back(-1);

	//�����ź���ıߵ�����
	int count = 0;				
	for (int i = 0; i < edges.size();++i)
	{
		edge temp = edges[i];

		//���ҵ�ǰ���ıߵĶ����Ƿ�������һ����ͨ����
		int vex1 = FindRoot(parent, temp.from);
		int vex2 = FindRoot(parent, temp.to);

		//��������ͬһ��ͨ����,��ñ�������С��������һ����
		if (vex1 != vex2)
		{
			cout << "#" << temp.from << " ���ӵ� " << "#" << temp.to << " ȨֵΪ��" << temp.weight << endl;
			parent[vex2] = vex1;	//vex2��vex1��λ�ÿ��Խ���

			++count;				//��¼���ҵ��ı���
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
	int *dist = new int[m_vertexNum];			//��v�㵽���ж�������·��ֵ
	string *path = new string[m_vertexNum];		//��v�㵽���ж�������·��
	bool *s = new bool[m_vertexNum];			//��¼�±��Ӧ�����Ƿ����ҵ������·��
	
	//��ʼ��
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

	memset(s, false, m_vertexNum);		//ע�⣺sizeof�����Լ���new����������
	s[v] = true;

	//����ʣ�µ�m_vertexNum - 1������
	for (int i = 0; i < m_vertexNum - 1; ++i)
	{
		//Ѱ��s[j]==false��dist[j]ֵ��С�Ķ���k
		int k;
		for (k = 0; k < m_vertexNum && s[k] == true; ++k);

		for (int j = 0; j < m_vertexNum; ++j)
		{
			if (s[j] == false && dist[j] < dist[k])
				k = j;
		}

		//���dist[k]��path[k]
		cout << "#" << v << " �� " << "#" << k << " ���·�����ȣ�" << dist[k] << " ���·����" << path[k] << endl;

		//s�Ǽ�k
		s[k] = true;		//�Ǽǿ��Է������k�㼴ʹ���Ǽǣ�����ѭ���е�if��������������j==k��ʱ��Ҳ�������

		//��k����ȥ�������е�s[i]==false�Ķ���i�����õ�����ֵ��ԭ����ֵ��С�������dist[i]��path[i]
		for (int j = 0; j < m_vertexNum; ++j)
		{
			if (s[j] == false && m_edge[k][j]!=INT_MAX && dist[k] + m_edge[k][j] < dist[j])	//��һ����������ɾ������Ϊ���һ�������Ѿ��ҵ�����С�ߣ�����������һ��������
			{
				dist[j] = dist[k] + m_edge[k][j];
				char buffer[BUFFERSIZE];
				sprintf_s(buffer, "#%d", j);
				path[j] = path[k] + buffer;
			}
		}
	}
}









